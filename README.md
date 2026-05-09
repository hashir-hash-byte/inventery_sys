<div align="center">

<img src="https://img.shields.io/badge/MediStock-AI-4F8EF7?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCAyNCAyNCI+PHBhdGggZmlsbD0id2hpdGUiIGQ9Ik0xMiAyQzYuNDggMiAyIDYuNDggMiAxMnM0LjQ4IDEwIDEwIDEwIDEwLTQuNDggMTAtMTBTMTcuNTIgMiAxMiAyek0xMyAxN2gtMnYtNmgydjZ6bTAtOGgtMlY3aDJ2MnoiLz48L3N2Zz4=&logoColor=white" alt="MediStock AI" />

# 🏥 MediStock AI

### *IoT-Powered Pharmacy Inventory Management System*

**Real-time stock monitoring · Automatic supplier emails · P2P emergency pharmacy alerts**

<br/>

[![ESP32](https://img.shields.io/badge/ESP32-IoT_Device-E7352C?style=flat-square&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![HTML5](https://img.shields.io/badge/HTML5-Web_App-E34F26?style=flat-square&logo=html5&logoColor=white)](https://developer.mozilla.org/en-US/docs/Web/HTML)
[![JavaScript](https://img.shields.io/badge/JavaScript-ES6+-F7DF1E?style=flat-square&logo=javascript&logoColor=black)](https://developer.mozilla.org/en-US/docs/Web/JavaScript)
[![EmailJS](https://img.shields.io/badge/EmailJS-Auto_Email-4F8EF7?style=flat-square&logo=gmail&logoColor=white)](https://www.emailjs.com/)
[![Arduino](https://img.shields.io/badge/Arduino-Firmware-00878F?style=flat-square&logo=arduino&logoColor=white)](https://www.arduino.cc/)

<br/>

```
┌─────────────────────────────────────────────────────────┐
│   ESP32 Sensor  →  Web Dashboard  →  Auto Email         │
│   counts bottles    live updates     zero middleman      │
└─────────────────────────────────────────────────────────┘
```

</div>

---

## 📖 Table of Contents

- [Problem Statement](#-problem-statement)
- [Solution Overview](#-solution-overview)
- [System Architecture](#-system-architecture)
- [Features](#-features)
- [Hardware Setup](#-hardware-setup)
- [ESP32 Firmware](#-esp32-firmware)
- [Web App Setup](#-web-app-setup)
- [EmailJS Configuration](#-emailjs-configuration)
- [How It Works](#-how-it-works)
- [Tech Stack](#-tech-stack)
- [Screenshots](#-screenshots)
- [Team](#-team)

---

## ❗ Problem Statement

Traditional pharmacy inventory management is broken:

| Problem | Impact |
|---|---|
| Manual stock counting | Human errors, missed shortages |
| No real-time visibility | Medicines run out before reorder |
| Supplier contact is manual | Delay between shortage and restock |
| No peer pharmacy network | Patients turned away unnecessarily |
| Overstocking / understocking | Financial loss, expired medicines |

> **A patient walks in for Paracetamol. Shelf is empty. Staff didn't notice. Supplier wasn't called. Nearby pharmacy has stock but nobody knew.**
> 
> MediStock AI eliminates every one of these failure points.

---

## 💡 Solution Overview

An **IoT-based, AI-integrated pharmacy inventory system** that:

- 🔬 Uses an **ESP32 + Ultrasonic Sensor** to count medicine bottles in real time
- 📊 Displays a **live web dashboard** with stock status, alerts, and history
- 📧 **Automatically emails the supplier** when stock runs low — no human needed
- 🚨 **Automatically alerts the nearest pharmacy** via emergency email when stock hits zero
- 🔄 Eliminates the middleman completely between the system and suppliers

---

## 🏗 System Architecture

```
┌─────────────────────┐
│   Medicine Shelf    │
│  [Bottles on rack]  │
└────────┬────────────┘
         │
         ▼
┌─────────────────────┐
│  Ultrasonic Sensor  │  measures distance (cm)
│  (HC-SR04)          │  converts → bottle count
│  TRIG: GPIO 5       │
│  ECHO: GPIO 18      │
└────────┬────────────┘
         │
         ▼
┌─────────────────────┐
│     ESP32 MCU       │  WiFi enabled
│  AsyncWebServer     │  serves GET /status
│  polls every 500ms  │  returns JSON
└────────┬────────────┘
         │  HTTP over WiFi
         ▼
┌─────────────────────────────────────────────────────────┐
│              MediStock AI Web Application               │
│                                                         │
│  ┌──────────┐  ┌───────────┐  ┌─────────┐  ┌───────┐  │
│  │Dashboard │  │ Inventory │  │ Devices │  │Orders │  │
│  └──────────┘  └───────────┘  └─────────┘  └───────┘  │
└──────────────────────┬──────────────────────────────────┘
                       │
          ┌────────────┴─────────────┐
          │                          │
          ▼                          ▼
 alertLevel == "SUPPLY REQUEST"   alertLevel == "EMERGENCY"
 count: 1 or 2 bottles            count: 0 bottles
          │                          │
          ▼                          ▼
 ┌─────────────────┐       ┌──────────────────────┐
 │  Supplier Email │       │ Nearby Pharmacy Email │
 │  (EmailJS #1)   │       │  (EmailJS #2)         │
 │  Auto-sent ✓    │       │  Auto-sent ✓          │
 └─────────────────┘       └──────────────────────┘
```

---

## ✨ Features

### 📡 Real-Time IoT Monitoring
- ESP32 polls ultrasonic sensor every **500ms**
- Web app syncs with ESP32 every **500ms**
- Live bottle count shown with animated progress bar
- Sensor health and last sync time tracked

### 📊 Inventory Dashboard
- Total, Low Stock, and Out-of-Stock counters
- Color-coded status: 🟢 Safe · 🟠 Low · 🔴 Out
- Medicine alert list with supplier info
- Recent inventory update history

### 💊 Medicine Management
- Add, edit, delete medicines
- Fields: Name, Category, Quantity, Manufacturer, Expiry Date, Supplier, Batch Number
- Filter by stock status
- Search by name or category

### 📧 Dual Automatic Email System

| Trigger | Condition | Email Sent To | EmailJS Account |
|---|---|---|---|
| **Supply Request** | 1–2 bottles remaining | Supplier | Account 1 |
| **Emergency** | 0 bottles (EMPTY) | Nearby Pharmacy | Account 2 |

> ✅ Zero human action required. Email fires the moment sensor detects the threshold.

### 🏥 P2P Pharmacy Network
- Emergency alerts sent directly to nearest partner pharmacy
- Enables stock transfer or patient referral
- Separate EmailJS service keeps it isolated from supplier flow

### 📦 Order History
- Auto-tagged orders (AUTO-SENT / EMERGENCY)
- Records: medicine, email, date, time, sensor count at trigger
- Filter: Auto-sent vs All orders

---

## 🔧 Hardware Setup

### Components Required

| Component | Quantity | Purpose |
|---|---|---|
| ESP32 Dev Board | 1 | WiFi + Web Server |
| HC-SR04 Ultrasonic Sensor | 1 | Distance measurement |
| Jumper Wires | ~6 | Connections |
| Breadboard | 1 | Prototyping |
| USB Cable | 1 | Power + Programming |

### Wiring Diagram

```
ESP32 GPIO 5  ──────────────── HC-SR04 TRIG
ESP32 GPIO 18 ──────────────── HC-SR04 ECHO
ESP32 3.3V    ──────────────── HC-SR04 VCC
ESP32 GND     ──────────────── HC-SR04 GND
```

### Distance-to-Count Mapping

```
Distance (cm)    Bottle Count    Status
─────────────────────────────────────────
≤ 7 cm      →       5           FULL
≤ 9 cm      →       4           NORMAL
≤ 11 cm     →       3           NORMAL
≤ 13 cm     →       2           LOW → SUPPLY REQUEST
≤ 15 cm     →       1           LOW → SUPPLY REQUEST
  16+ cm    →       0           EMPTY → EMERGENCY
```

> 📐 ±1cm tolerance built into all readings. Bad readings (0 duration) are ignored automatically.

---

## 🔌 ESP32 Firmware

### Prerequisites

Install these libraries in Arduino IDE:

```
✓ ESPAsyncWebServer
✓ AsyncTCP
✓ ArduinoJson
✓ WiFi (built-in)
```

### Configuration

Open the firmware file and update your WiFi credentials:

```cpp
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

### API Endpoint

Once flashed and connected, the ESP32 serves:

```
GET http://{ESP32_IP}/status
```

**Sample Response:**

```json
{
  "medicine":    "Paracetamol",
  "count":       2,
  "total":       5,
  "stockStatus": "LOW",
  "alertLevel":  "SUPPLY REQUEST",
  "emergency":   false,
  "supplyNeeded": true
}
```

### Flash Steps

```bash
1. Open Arduino IDE
2. Select Board: "ESP32 Dev Module"
3. Select correct COM port
4. Upload the firmware
5. Open Serial Monitor (115200 baud)
6. Note the IP address printed on connection
```

---

## 🌐 Web App Setup

No installation needed. Pure HTML + JS — open directly in browser.

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/medistock-ai.git

# Open the web app
open medistock.html
# or just double-click the file
```

### Connect Your ESP32

```
1. Open MediStock AI in browser
2. Go to → Devices tab
3. Enter ESP32 IP address (from Serial Monitor)
4. Click ⚡ Connect Device
5. Dashboard updates live within 500ms
```

> ⚠️ **Important:** Browser must be on the **same WiFi network** as the ESP32.
> The app must be served via `http://` (not `https://`) to avoid mixed-content errors when fetching from ESP32.

---

## 📧 EmailJS Configuration

MediStock AI uses **two separate EmailJS accounts** for routing:

### Account 1 — Supplier Reorder (SUPPLY REQUEST)

| Field | Value |
|---|---|
| Service ID | `service_fm030mr` |
| Template ID | `template_oq4ksu6` |
| Trigger | alertLevel == "SUPPLY REQUEST" |
| Sends to | Supplier email |

**Template variables used:**
```
{{to_email}}           {{to_name}}
{{medicine_name}}      {{medicine_category}}
{{current_quantity}}   {{requested_quantity}}
{{supplier_name}}      {{batch_number}}
{{expiry_date}}        {{date}}
{{alert_level}}        {{from_name}}
```

---

### Account 2 — Emergency P2P Pharmacy Alert (EMERGENCY)

| Field | Value |
|---|---|
| Service ID | `service_ipvkrha` |
| Template ID | `template_a415lwt` |
| Public Key | `fWwy3XiA3vpxA_pdy` |
| Trigger | alertLevel == "EMERGENCY" (count = 0) |
| Sends to | Nearby pharmacy email |

**Recommended Emergency Template:**

```
Subject: 🚨 EMERGENCY Stock Alert from {{from_pharmacy}}

Dear Pharmacy Partner,

URGENT: Our pharmacy has run out of the following medicine.

Medicine:       {{medicine_name}}
Current Stock:  {{current_quantity}} units
Alert Level:    {{alert_level}}
Date/Time:      {{date}}

We request emergency stock transfer or patient referral.

Please contact us immediately.

From: {{from_pharmacy}}
System: MediStock AI — Emergency P2P Alert
```

---

## ⚙️ How It Works

```
Step 1 — Sense
  ESP32 fires ultrasonic pulse every 500ms
  Measures echo duration → calculates distance
  Converts distance to bottle count (0–5)

Step 2 — Serve
  ESP32 updates stockStatus and alertLevel
  Serves updated JSON at GET /status

Step 3 — Sync
  Web app fetches /status every 500ms
  Updates Paracetamol quantity in inventory
  Refreshes dashboard UI live

Step 4 — Alert
  If alertLevel changes OR count changes:
    → SUPPLY REQUEST: fires supplier email (Account 1)
    → EMERGENCY:      fires pharmacy email (Account 2)

Step 5 — Record
  Order logged with: medicine, email, date, time, trigger, sensor count
  Shown in Orders tab with AUTO-SENT or EMERGENCY badge
```

---

## 🛠 Tech Stack

| Layer | Technology |
|---|---|
| **Hardware** | ESP32, HC-SR04 Ultrasonic Sensor |
| **Firmware** | Arduino C++ / ESPAsyncWebServer / ArduinoJson |
| **Frontend** | HTML5, CSS3, Vanilla JavaScript (ES6+) |
| **Email** | EmailJS (dual account routing) |
| **Protocol** | HTTP REST (ESP32 serves JSON API) |
| **Connectivity** | WiFi (ESP32 ↔ Web App on same network) |

---

## 📸 Screenshots

### Dashboard — Live Sensor Feed
```
┌─────────────────────────────────────┐
│ ● ESP32 Live — Paracetamol          │
│                                     │
│  Bottle Count    Stock Status       │
│      2 / 5         LOW              │
│                                     │
│  Stock Level                        │
│  ████████░░░░░░░░  40%              │
│                                     │
│  Last sync: 14:32:07   ⚠ SUPPLY REQUEST │
└─────────────────────────────────────┘
```

### Auto Email Routing
```
count: 2  →  alertLevel: SUPPLY REQUEST
              └─▶ email: mahammadshahidmalar@gmail.com
                  "Please restock Paracetamol 500mg..."

count: 0  →  alertLevel: EMERGENCY
              └─▶ email: hashirbearys2024@gmail.com
                  "🚨 EMERGENCY: Paracetamol is EMPTY..."
```

### Orders Tab
```
┌─────────────────────────────────────┐
│  Paracetamol 500mg    [AUTO-SENT]   │
│  To: mahammadshahidmalar@gmail.com  │
│  10/05/2026 @ 14:32 | 100 units     │
│  Trigger: SUPPLY REQUEST | 2/5      │
│  ✓ Email sent to supplier           │
├─────────────────────────────────────┤
│  Paracetamol 500mg    [🚨 EMERGENCY]│
│  To: hashirbearys2024@gmail.com     │
│  10/05/2026 @ 15:01 | 100 units     │
│  Trigger: EMERGENCY | 0/5           │
│  ✓ Email sent to nearby pharmacy    │
└─────────────────────────────────────┘
```

---

## 👥 Team

**Yenepoya Pharmacy — MediStock AI Project**

Built to solve real inventory failures in pharmacy operations using IoT, cloud email automation, and a peer-to-peer emergency pharmacy network.

---

## 📄 License

This project is built for academic and operational use at Yenepoya Pharmacy.

---

<div align="center">

**MediStock AI** — *Because an empty shelf should never be a surprise.*

`ESP32` · `IoT` · `Pharmacy` · `Auto-Email` · `P2P` · `Real-Time`

⭐ Star this repo if it helped you!

</div>
