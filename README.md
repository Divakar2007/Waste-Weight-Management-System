# Industrial IoT Weight Monitoring & Logging System (ESP32 + SCADA Dashboard)

## 📌 Project Overview

This project is an **Industrial IoT-based Weight Monitoring and Logging System** built using the **ESP32 microcontroller**.
It features a real-time **SCADA-style web dashboard** and cloud-based data logging using **Google Sheets**.

The system allows an operator to:

* Enter a weight value
* Classify it as **Inbound** or **Outbound**
* Log the data instantly
* View recent logs in a professional industrial dashboard
* Store records securely in Google Sheets

This simulates a simplified industrial weighbridge or material tracking system.

---

## 🎯 Key Features

* ⚡ Real-time SCADA-style dashboard hosted on ESP32
* 📊 Last 10–15 transaction logs displayed live
* 📈 Running totals for inbound and outbound
* ☁ Cloud logging via Google Apps Script
* 🌐 WiFi-based communication
* 🎛 Operator-controlled logging workflow
* 🔁 Auto-refreshing industrial UI

---

## 🏗 System Architecture

Operator Input (Serial / Scale Input)
⬇
ESP32 Processing & State Control
⬇
SCADA Web Dashboard (Local Server)
⬇
Google Apps Script (HTTP POST)
⬇
Google Sheets (Inbound & Outbound Logs)

---

## 🧠 Working Principle

1. Operator enters weight.
2. System prompts for selection:

   * `1` → Inbound
   * `2` → Outbound
3. Upon selection:

   * Weight is logged locally.
   * SCADA dashboard updates instantly.
   * Data is sent to Google Sheets with timestamp.
4. System resets and waits for next entry.

---

## 🛠 Technologies Used

* **ESP32**
* **Arduino IDE**
* **Embedded C++**
* **HTML + CSS (SCADA Dashboard)**
* **Google Apps Script**
* **Google Sheets**
* **HTTP Communication Protocol**

---

## 📦 Hardware Requirements

* ESP32 Development Board
* USB Cable
* WiFi Network
* (Optional future upgrade: Load Cell + HX711)

---

## 📦 Software Requirements

* Arduino IDE
* ESP32 Board Package
* Google Account (for Apps Script & Sheets)

---

## ⚙ Setup Instructions

### 1️⃣ Google Sheets Setup

1. Create a Google Sheet.
2. Create two tabs:

   * `Inbound`
   * `Outbound`
3. Go to **Extensions → Apps Script**.
4. Paste the Apps Script code.
5. Deploy as:

   * Execute as: **Me**
   * Access: **Anyone**
6. Copy the Web App URL.

---

### 2️⃣ ESP32 Setup

1. Open Arduino IDE.
2. Paste the ESP32 code.
3. Replace:

   * WiFi SSID
   * WiFi Password
   * Google Web App URL
4. Upload to ESP32.
5. Open Serial Monitor (115200 baud).

---

### 3️⃣ Access Dashboard

After upload, Serial Monitor will show:

```
ESP32 IP: 192.168.x.xxx
```

Open browser and enter:

```
http://192.168.x.xxx
```

You will see the SCADA dashboard.

---

## 📊 Dashboard Features

* Industrial dark theme
* Large digital weight display
* System status indicator
* Separate inbound & outbound panels
* Total weight counters
* Last 15 transaction logs
* Auto-refresh every 2 seconds

---

## 📁 Data Storage

* Last 15 logs stored locally in ESP32 RAM
* Permanent records stored in Google Sheets
* Timestamp automatically generated

---

## 🏭 Industrial Applications

* Waste management tracking
* Weighbridge automation
* Warehouse logistics
* Factory inbound/outbound control
* Scrap yard management

---

## 🚀 Future Improvements

* Load cell integration (HX711)
* RFID vehicle identification
* User authentication system
* Offline data buffering
* MQTT industrial communication
* Alarm system for overload detection
* Persistent storage using SPIFFS/LittleFS

---

## 🧩 Advantages

* Low-cost IoT solution
* Real-time cloud logging
* Industrial-style visualization
* Scalable architecture
* Easy integration with automation systems

---

## 📜 License

This project is intended for educational and research purposes.
Feel free to modify and extend as needed.

---

## 👨‍💻 Author

Developed as an Industrial IoT Embedded Systems Project using ESP32 and Cloud Integration.

---

**End of README**
