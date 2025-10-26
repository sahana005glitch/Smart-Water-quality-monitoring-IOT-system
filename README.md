# 💧 Smart Water Quality Monitoring IoT System

This project monitors the quality of water in real time using sensors and an IoT-enabled microcontroller (such as Arduino or NodeMCU). It measures key parameters like **TDS** then sends the data to the cloud or displays it locally.

---

## 🚀 Features
- Real-time water quality monitoring  
- Measurement of TDS
- Cloud data logging (via Wi-Fi or serial)  
- Visual feedback through LEDs or an LCD display  
- Easy calibration and threshold configuration  

---

## 🧰 Hardware Components
| Component | Description |
|------------|-------------|
| **Microcontroller** | Arduino UNO / NodeMCU / ESP32 |
| **TDS Sensor** | Measures total dissolved solids in water |
| **Wi-Fi Module (if using Arduino UNO)** | For IoT connectivity |
| **Jumper wires & Breadboard** | For connections |
| **Power Supply (5V/3.3V)** | To power the system |

---

## ⚙️ Circuit Connections
- Connect the **TDS sensor** to analog pin `A0`
- Connect **GND** and **VCC** appropriately (based on your sensor voltage)
- If using **NodeMCU or ESP32**, connect Wi-Fi as per the code configuration

---

## 🧩 Software Setup
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Open `WaterQualityMonitoring.ino`
3. Select the correct **board** and **port**
4. Install required libraries (if used in the sketch):
   - `ESP8266WiFi` or `WiFi.h`
   - `OneWire.h` and `DallasTemperature.h` (for DS18B20)
5. Click **Upload** to flash the code

---

## 🌐 Cloud Integration 
If using an IoT platform like **ThingSpeak** add your Wi-Fi credentials and API keys in the code where indicated.

Example:
```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
````

---

## 📊 Expected Output

* Serial Monitor displays:

  ```
  TDS: 320 ppm
  pH: 7.2
  Temperature: 25°C
  ```
* Dashboard (if connected) shows live readings

---

## 🧠 Future Enhancements

* Add turbidity or dissolved oxygen sensors
* Enable SMS/email alerts for unsafe water quality
* Create a mobile app dashboard

---

## 🧾 Author

**Sahana M**
**Zaiba Fathima**
Smart Water Quality Monitoring IoT System
GitHub: [@sahana005glitch](https://github.com/sahana005glitch)

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

```

---

Would you like me to tailor this README specifically to your **board (e.g., NodeMCU / Arduino UNO)** and the exact sensors your `.ino` file uses?  
That way, the pin mapping and setup steps will match your hardware exactly.
```
