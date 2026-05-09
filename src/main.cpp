#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>

#define TRIG_PIN 5
#define ECHO_PIN 18

const char* ssid     = "Hashir’s iphone";
const char* password = "hashir1676";

AsyncWebServer server(80);

int bottleCount = 5;
String stockStatus = "FULL";
String alertLevel = "OK";
unsigned long lastCheck = 0;

long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  return duration * 0.034 / 2;
}

int distanceToCount(long dist) {
  // +/- 1cm tolerance built in
  if (dist <= 7)  return 5;   // 6cm = full
  if (dist <= 9)  return 4;   // 8cm
  if (dist <= 11) return 3;   // 10cm
  if (dist <= 13) return 2;   // 12cm
  if (dist <= 15) return 1;   // 14cm
  return 0;                   // 16cm+ = empty
}

void updateStatus(int count) {
  if (count == 5) {
    stockStatus = "FULL";
    alertLevel  = "OK";
  } else if (count >= 3) {
    stockStatus = "NORMAL";
    alertLevel  = "OK";
  } else if (count >= 1) {
    stockStatus = "LOW";
    alertLevel  = "SUPPLY REQUEST";
  } else {
    stockStatus = "EMPTY";
    alertLevel  = "EMERGENCY";
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Origin", "*");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Methods", "GET, OPTIONS");
  DefaultHeaders::Instance().addHeader("Access-Control-Allow-Headers", "*");

  server.on("/status", HTTP_OPTIONS, [](AsyncWebServerRequest *req){ req->send(200); });

  server.on("/status", HTTP_GET, [](AsyncWebServerRequest *req) {
    StaticJsonDocument<200> doc;
    doc["medicine"]    = "Paracetamol";
    doc["count"]       = bottleCount;
    doc["total"]       = 5;
    doc["stockStatus"] = stockStatus;
    doc["alertLevel"]  = alertLevel;
    doc["emergency"]   = (alertLevel == "EMERGENCY");
    doc["supplyNeeded"]= (alertLevel == "SUPPLY REQUEST");
    String out; serializeJson(doc, out);
    req->send(200, "application/json", out);
  });

  server.begin();
  Serial.println("Server started!");
}

void loop() {
  if (millis() - lastCheck < 500) return;
  lastCheck = millis();

  long dist = getDistance();
  if (dist == 0) return; // ignore bad readings

  Serial.print("Distance: "); Serial.print(dist); Serial.println(" cm");

  int newCount = distanceToCount(dist);

  if (newCount != bottleCount) {
    bottleCount = newCount;
    updateStatus(bottleCount);
    Serial.print(">> Count: "); Serial.print(bottleCount);
    Serial.print(" | Status: "); Serial.print(stockStatus);
    Serial.print(" | Alert: "); Serial.println(alertLevel);
  }
}
