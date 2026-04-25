#  ESP32 IoT Fuzzing Lab (BLE + MQTT)

A comprehensive IoT security project demonstrating **protocol fuzzing on ESP32** using both:

*  **Bluetooth Low Energy (BLE)**
*  **MQTT (Message Queuing Telemetry Transport)**

This project simulates real-world attacks by sending **malformed and random payloads** to an ESP32 device and analyzing its behavior.

---

##  Overview

This repository combines two major IoT communication protocols:

| Protocol | Role          | Attack Type             |
| -------- | ------------- | ----------------------- |
| MQTT     | Network-based | Broker-mediated fuzzing |
| BLE      | Device-based  | Direct GATT fuzzing     |

---

##  Architecture

### MQTT Workflow

```
Python MQTT Fuzzer (Kali)
            ↓
     Mosquitto Broker
            ↓
        ESP32 Client
            ↓
   Payload Processing & Detection
```

 Correct Execution Order:

```
1. Start Broker
2. Start ESP32
3. Run Python Fuzzer
```

Note:
ESP32 will retry connection if broker is not available.

---

###  BLE Workflow

```
ESP32 (BLE Server)
        ↓
 BLE Scan (Discover Device)
        ↓
 BLE Client Connect
        ↓
 BLE Fuzzer (GATT Writes)
        ↓
 Payload Analysis
```

 Correct Execution Order:

```
1. Start ESP32 BLE Server
2. Scan for device
3. Connect & Fuzz
```

 Important:
BLE is **connection-based**, unlike MQTT.

---

##  Project Structure

```
esp32-iot-fuzzing-lab/
│
├── ble_fuzzer.py          # BLE fuzzing script
├── ble_scan.py            # BLE device scanner
├── ble-server.ino         # ESP32 BLE server
│
├── esp32-mqtt-fuzzing-lab/
│   ├── esp32_mqtt.ino     # ESP32 MQTT client
│   └── mqtt-fuzzing.py    # MQTT fuzzing script
│
└── README.md
```

---

#  MQTT Fuzzing Setup

##  Requirements:

* Mosquitto Broker
* Python (paho-mqtt)
* ESP32
* WiFi Network
* Arduino IDE

---

##  Installation

###  Install Mosquitto

```bash
sudo apt update
sudo apt install mosquitto mosquitto-clients -y
```

Start broker:

```bash
sudo systemctl start mosquitto
```

---

###  Install Python Dependencies

```bash
pip3 install paho-mqtt
```

---

###  Configure IP Address

Find your system IP:

```bash
ip a
```

Update IP in:

* `mqtt-fuzzing.py`
* `esp32_mqtt.ino`

---

###  Upload ESP32 Code

* Open Arduino IDE
* Select **ESP32 Dev Module**
* Upload `esp32_mqtt.ino`
* Open Serial Monitor (115200)

---

###  Run MQTT Fuzzer

```bash
python3 mqtt-fuzzing.py
```

---

##  MQTT Output

###  Kali

```
[+] Sent: random_payload
[+] Sent: AAAAAAAA...
```

###  ESP32

```
Message received: Hello
Large payload detected! Simulating crash...
```


##  MQTT Insight

* Detects malformed payloads
* Simulates crash/reboot
* Demonstrates lack of input validation

---

#  BLE Fuzzing Setup

##  Requirements

* ESP32
* Arduino IDE
* Python (bleak)
* Bluetooth Adapter

---

##  Installation

###  Install Dependencies

```bash
sudo apt update
sudo apt install bluetooth bluez
pip install bleak
```

Start Bluetooth:

```bash
sudo systemctl start bluetooth
```

Verify:

```bash
hciconfig
```

---

###  Upload BLE Server Code

* Open Arduino IDE
* Upload `ble-server.ino`

Expected:

```
BLE Server Started...
```


###  Scan Device

```bash
python3 ble_scan.py
```

Find:

```
ESP32_BLE_FUZZ
```

Copy MAC address.

---

###  Run BLE Fuzzer

Edit MAC in:

```
ble_fuzzer.py
```

Run:

```bash
python3 ble_fuzzer.py
```

---

##  BLE Output

###  Kali

```
Connected to ESP32
[1] Sent: random payload
```

###  ESP32

```
Received BLE Data (len=140)
WARNING: Large malformed payload detected!
Potential overflow attempt!
```


##  BLE Detection Logic

| Payload Size | Behavior         |
| ------------ | ---------------- |
| < 50 bytes   | Normal           |
| > 50 bytes   | Warning          |
| > 120 bytes  | Overflow attempt |

---

#  Key Features

* ✔ Dual protocol fuzzing (BLE + MQTT)
* ✔ Real-time detection on ESP32
* ✔ Random payload generation
* ✔ Lightweight & easy to run
* ✔ Perfect for academic demonstrations

---

#  Concepts Covered

* IoT Security Testing
* BLE GATT Protocol
* MQTT Protocol
* Fuzz Testing
* Buffer Overflow Simulation

---

# Explanation

> "This project demonstrates IoT protocol fuzzing using both MQTT and BLE. MQTT fuzzing is broker-based, while BLE fuzzing directly targets device characteristics. The ESP32 analyzes malformed payloads and detects abnormal behavior, showcasing real-world IoT vulnerabilities."

---

#  Common Issues

##  MQTT Not Connecting

 Ensure:

```
sudo systemctl start mosquitto
```

---

##  BLE Not Working

```
BleakBluetoothNotAvailableError
```

 Fix:

* Use USB Bluetooth dongle (for VM)
* Attach to VM

---

##  Permission Errors

```bash
sudo python3 ble_fuzzer.py
```

---

#  Future Improvements

* GUI Dashboard
* Multi-device fuzzing
* Attack logging
* Wireshark integration
* Automated vulnerability reports

---

#  Conclusion

This project provides a **complete hands-on IoT fuzzing lab** covering both:

* Network-level attacks (MQTT)
* Device-level attacks (BLE)

Making it a **strong cybersecurity + embedded systems project**.

---

##  Author

Avinash
