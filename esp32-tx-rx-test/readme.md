
# 📡 Distributed Local IoT Emulation: Multi-Board ESP32 Telemetry over MQTT

[cite_start]This project demonstrates a decoupled, multi-board **Edge-to-Cloud/Gateway architecture** running entirely on a local machine[cite: 631]. [cite_start]Using two separate **Visual Studio Code** workspaces running the **Wokwi Simulation Engine**, an explicit data bridge is formed via a local **Mosquitto MQTT broker**[cite: 416, 417].

## 🏗️ System Architecture

* [cite_start]**Node 1 (Transmitter):** Reads an analog potentiometer dial on `GPIO 34` and publishes raw sensor telemetry[cite: 377, 644].
* [cite_start]**Broker (Linux Host):** A local Mosquitto service running in the background handles the message routing queue on Port 1883[cite: 420, 646].
* [cite_start]**Node 2 (Receiver):** Subscribes to the telemetry topic, parsed payloads dynamically drive a **5-LED visual bar graph** (`GPIO 18, 19, 21, 22, 23`), and shifts pitch frequencies on a **Passive Piezo Buzzer** (`GPIO 25`)[cite: 70, 73].

---

## 📸 Local Workspace Circuit Layouts

### 1. Transmitter Configuration (`diagram.json`)

[cite_start]Connect your hardware components to your primary transmitter microcontroller as follows[cite: 377]:

* `GND` ➡️ ESP32 `GND`
* `VCC` ➡️ ESP32 `3V3`
* `SIG` ➡️ ESP32 `GPIO 34`

### 2. Receiver Configuration (`diagram.json`)

[cite_start]Map the telemetry visualization array to your secondary receiver board[cite: 70]:

* **LEDs 1–5 (Anodes):** Connected sequentially to `GPIO 18, 19, 21, 22, 23`
* **LEDs 1–5 (Cathodes):** Tied together to a common ESP32 `GND`
* **Passive Buzzer:** Signal connected to `GPIO 25` / Ground to ESP32 `GND`
