# ☁️ Bidirectional Cloud IoT Simulation: ESP32 + Blynk App Control

This project documents how to implement two-way cloud command-and-control over an emulated embedded environment. Utilizing **Visual Studio Code**, **PlatformIO**, and **Wokwi**, an ESP32 is managed via a smartphone or web dashboard using the **Blynk IoT Platform**.

This configuration prioritizes professional engineering workflows, utilizing **dynamic compiler build flags** to inject sensitive system variables without hardcoding secrets into the source tree.

---

## 📌 The Architecture Behind the Connection

Local emulators typically operate inside an isolated network sandbox. Standard inbound traffic is restricted by local network environments and system firewalls. **Blynk manages communication across this barrier through a Persistent WebSockets/TCP Architecture:**

1. **The Outbound Handshake:** When the code calls `Blynk.begin()`, the virtual ESP32 pushes an *outbound* connection request through the simulation network layer to Blynk's public cloud servers. Local firewalls permit outbound traffic by default.
2. **The Held-Open Tunnel:** Rather than closing the connection after a message transits, the Blynk library creates a persistent socket. It evaluates and keeps this connection open continuously via the `Blynk.run()` function.
3. **The Control Event:** When a switch widget is toggled on your mobile application, the cloud drops the control command packet down that pre-existing outbound tunnel. The host machine parses this packet as a safe, requested response, passing it to your virtual hardware layout instantly.

---

## 📱 Blynk Dashboard Widget Configuration

To map your digital firmware states to your smartphone application layout, configure your mobile Blynk console layout to match this setup exactly:

| UI Label Name | Virtual Pin | Data Type | Widget Type | Hardware Action |
| :--- | :--- | :--- | :--- | :--- |
| **Red** | `V0` | Integer (0/1) | Push Button / Switch | Toggles Red LED (`GPIO 25`) |
| **Green** | `V1` | Integer (0/1) | Push Button / Switch | Toggles Green LED (`GPIO 26`) |
| **Blue** | `V2` | Integer (0/1) | Push Button / Switch | Toggles Blue LED (`GPIO 27`) |

*Make sure your mobile design panel reflects this hierarchy:*

* **Template Name:** `ESP32 Control`
* **Widgets:** 3 standalone styled buttons or switches assigned individually to datastreams `V0`, `V1`, and `V2`.

---

## 🔒 Environment Variable Configuration (Local Setup)

To keep sensitive cloud authentication tokens secure and prevent them from being leaked to your public GitHub repository, variables are stored in an external configuration profile and handled via compiler runtime directives.

### Step 1: Initialize Your Secret Key Template

1. Locate the file named `temp.private.ini` in this project directory.
2. Duplicate the file and rename the new copy exactly to `private.ini`.

> ⚠️ **Important:** The project's `.gitignore` file is already pre-configured to detect and block `private.ini` from ever being pushed to GitHub.

### Step 2: Input Your Tokens

Open your fresh `private.ini` file and substitute the placeholder strings with your live cloud panel attributes:

```ini
[extra_secrets]
build_flags =
    -D BLYNK_TEMPLATE_ID='"YOUR_TEMPLATE_ID_HERE"'
    -D BLYNK_TEMPLATE_NAME='YOUR_TEMPLATE_NAME_HERE""'
    -D BLYNK_AUTH_TOKEN='"YOUR_AUTH_TOKEN_HERE"'

```

*Note: The combined single and double-quote syntax (`'"string"'`) is required by the preprocessor to accurately register the values as true literal C-strings.*

During compilation, PlatformIO automatically reaches out to `platformio.ini`, imports your `private.ini` file variables via the `${extra_secrets.build_flags}` token handler, and passes them straight to your code dynamically.

---

## 🎛️ Hardware Configuration (`diagram.json`)

Map your virtual physical parts on the simulator canvas using these standard digital mapping lines:

* **Red LED (Anode):** Connected to ESP32 `GPIO 25`
* **Green LED (Anode):** Connected to ESP32 `GPIO 26`
* **Blue LED (Anode):** Connected to ESP32 `GPIO 27`
* **Common Ground Plane:** Tie all negative LED Cathode leads directly into an available ESP32 `GND` node pin.

---

## 🚀 Running the Workspace Simulation

1. Open this specific project subfolder in VS Code (**File -> Open Folder**).
2. Ensure your local `private.ini` file is fully configured and matches your Blynk cloud credentials.
3. Compile the firmware files using the **PlatformIO: Build** checkmark icon in the blue status bar of your editor window.
4. Launch the local simulation module: Press `F1`, choose **`Wokwi: Start Simulator`**, and hit Enter.

Toggle the switches on your phone app or browser dashboard. The system will process commands with zero latency, printing status flags to the serial console while changing states across your virtual LEDs!
