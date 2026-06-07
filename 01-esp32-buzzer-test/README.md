# 🛠️ Local IoT Hardware Simulation: ESP32 + Potentiometer + Buzzer

Tired of waiting in browser queues on the Wokwi cloud tier? This project documents how to shift your entire embedded prototyping workflow completely **local** using **Visual Studio Code**, **PlatformIO**, and the **Wokwi Extension**.

By running the simulation engine locally, compilation handles straight from your machine's CPU—meaning **zero server queues and instant runtime initialization**.

---

## 📌 Project Overview

This sandbox project serves as an introductory telemetry-to-audio circuit:

1. **Input:** An analog **Potentiometer** dial values are read by an **ESP32**.
2. **Processing:** The values are mapped into variable frequencies.
3. **Output:** A **Piezo Buzzer** translates those frequencies into audible sound.

💡 **Key Takeaway Learned:** A common trap when using a *passive* piezo buzzer in simulations is trying to drive it using `digitalWrite(HIGH)`. Passive buzzers require an oscillating frequency wave to vibrate internal components. This project implements Arduino's native `tone()` and `noTone()` functions, which generate the proper square-wave signals to push audio directly through your physical computer speakers.

---

## 🛠️ Step-by-Step Setup Guide

Follow these exact steps to get this environment running locally on your computer.

### Step 1: Install & Configure the Toolchains

1. open **Visual Studio Code**.
2. Head to the Extensions Marketplace and install:
   * **PlatformIO IDE** (Handles C++ compilation and firmware structures)
   * **Wokwi Simulator** (Handles visual hardware virtualization)
3. **Activate Wokwi License:** Press `F1` in VS Code, type `Wokwi: Start Simulator`, and follow the one-time browser login prompt to activate your free local license token.

### Step 2 (if on linux): Fix the Python `venv` Environment Dependency

If you are using Linux Mint / Ubuntu / Debian, PlatformIO might crash upon initialization if your system Python is missing the virtual environment core binaries.

Fix this cleanly by opening your system terminal and running:

```bash
sudo apt update
sudo apt install python3-venv
```

*(Alternatively, you can go to VS Code Settings, search for `platformio-ide.useBuiltinPython`, check the box, and restart VS Code).*

### Step 3: Clone and Prepare the Subfolder Workspace

1. Clone this repository to your local machine.
2. In VS Code, navigate to **File -> Open Folder** and open **strictly** the subfolder containing this project (`01-esp32-local-simulation`).

> ⚠️ **Important:** PlatformIO requires its configuration files (`platformio.ini`) to live directly in the root of your active VS Code workspace tab to initialize properly.

---

## 🚀 Running the Simulation

Once the folder is open in VS Code:

1. **Compile the Firmware:** Click the **PlatformIO: Build** checkmark icon in the bottom blue status bar of VS Code (or press `Ctrl+Alt+B`). This compiles the source files and generates the hidden binary image paths inside `.pio/build/`.
2. **Launch Wokwi:** Press `F1` on your keyboard, select **`Wokwi: Start Simulator`**, and hit Enter.
3. **Interact and Listen:** * The interactive visual hardware layout will appear on your screen.

* Hover your mouse over the virtual **Potentiometer** dial, click, and slide it.
* Watch the values change rapidly inside the **Serial Monitor** tab at the bottom.
* You will hear the pitch shifting higher or lower directly through your desktop speakers!

---

## 🎛️ Hardware Configuration Breakdown

### 1. The Circuit (`diagram.json`)

The virtual hardware is connected inside the simulator environment using the following mapping layout:

* **Potentiometer Pinout:**
* `GND` ➡️ ESP32 `GND`
* `VCC` ➡️ ESP32 `3V3`
* `SIG` (Signal) ➡️ ESP32 `GPIO 34` (Analog input pin)

* **Piezo Buzzer Pinout:**
* `GND` ➡️ ESP32 `GND`
* `SIG` (Signal) ➡️ ESP32 `GPIO 25`

### 2. Simulator Entry Link (`wokwi.toml`)

To point the local Wokwi engine directly to PlatformIO's compiled output binaries, the `wokwi.toml` file maps the firmware pathway structure exactly like this:

```toml
[wokwi]
version = 1
firmware = '.pio/build/esp32dev/firmware.bin'
elf = '.pio/build/esp32dev/firmware.elf'

```

---

🔄 *Next up on my roadmap: Simulating multi-board configurations locally over networked loops! Stay tuned.*
