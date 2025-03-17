# 🔋 Smart Instrumented Battery Module Design

[![Arduino](https://img.shields.io/badge/Arduino-Uno-blue)](https://www.arduino.cc/)[![Sensors](https://img.shields.io/badge/Sensors-Multi%20Parameter-green)](https://en.wikipedia.org/wiki/Sensor)[![I2C](https://img.shields.io/badge/I2C-Protocol-purple)](https://en.wikipedia.org/wiki/I%C2%B2C)[![Battery](https://img.shields.io/badge/Battery-Lithium%20Ion-orange)](https://en.wikipedia.org/wiki/Lithium-ion_battery)[![Proteus](https://img.shields.io/badge/Proteus-Simulation-red)](https://www.labcenter.com/)[![License](https://img.shields.io/badge/license-MIT-green)](LICENSE)

![Battery Module](/docs/sim2.JPG)


## 🚀 Overview
The Smart Instrumented Battery Module (SIBM) is an advanced Battery Management System (BMS) designed to monitor voltage, current, temperature, and energy in lithium-ion battery packs using Arduino and sensor fusion.

## 🎯 Objectives
- Develop a BMS for real-time monitoring of battery parameters.
- Integrate sensors (thermocouples, Hall-effect, thermistors, voltage) for multi-parameter analysis.
- Validate system accuracy by testing it with two cylindrical cells.

**🔹 Core Skills:**  
- Embedded Systems  
- Sensor Integration  
- Battery Management  
- Data Visualization  

## 🏗️ Key Components
### 1️⃣ **Arduino Uno**
Controls sensor data acquisition and relay operations.

### 2️⃣ **Sensors**
- Thermocouples: Measure temperature differences.
- Hall-effect: Monitor current.
- Thermistors: Track ambient temperature.
- Voltage Sensors: Measure electrical potential.

### 3️⃣ **LCD Display**
Shows real-time battery parameters via I2C protocol.

## 📜 Features
- **Multi-Parameter Monitoring**: Tracks voltage, current, temperature, and energy.
- **Flexible Design**: Supports series/parallel configurations for two 21700 cells.
- **Safety Control**: Uses a relay to manage charging/discharging.

## 🛠️ Implementation
- **Platform**: Arduino Uno with I2C protocol.
- **Key Files**:  
  - `SIBM.ino`: Main Arduino code for sensor integration and display.
  - `circuit_diagram.png`: Schematic of the hardware setup.

## 📂 Featured Code
### 🔹 Voltage Reading
```cpp
float adc_voltage = (analogRead(A0) * 5.0) / 1024.0;
float in_voltage = adc_voltage / (7500.0 / (30000.0 + 7500.0));
```
##🔹 Temperature Monitoring
```
float average = 0;
for (int j = 0; j < 5; j++) {
  average += analogRead(A2);
  delay(10);
}
average = (1023 / (average / 5)) - 1;
average = 10000 / average;
float temp = log(average / 10000) / 3950 + 1.0 / (25 + 273.15);
temp = (1.0 / temp) - 273.15;
```
## ✅ Verification
- **Test 1**: Confirmed accurate voltage and current readings on LCD.
- **Test 2**: Validated temperature discrepancy and pack temperature display.

## 📌 Methodology
- **Design**: Integrate sensors and Arduino for data acquisition.
- **Implementation**: Program Arduino to process sensor data and control relay.
- **Testing**: Verify system with two lithium-ion cells in various configurations.

## 📄 Future Enhancements
- Integrate machine learning for predictive battery health monitoring.
- Support larger battery arrays with wireless sensor networks.

## 🛠️ Installation
To set up the project environment:

1. Ensure Arduino IDE is installed.
2. Install required libraries (`Wire`, `LiquidCrystal_I2C`, `max6675`):
   - Use Arduino Library Manager or download from GitHub.
3. Upload the `SIBM.ino` code to your Arduino Uno via USB.

## 📥 Cloning the Repository
To clone the project from GitHub:
Open a terminal and navigate to your directory:
```
cd /path/to/your/directory
```
Clone the repository (replace with the actual URL):
```
git clone https://github.com/ahtishamsudheer/SmartInstrumentedBatteryModule.git
```
Navigate into the project directory:
```
cd SmartInstrumentedBatteryModule
```
### 📁 Project Files

📂 Smart-Instrumented-Battery-Module
├── 📜 README.md # Project Overview
├── 📜 Project Report # Project Overview
├── 📂 src # Source Code
│   ├── sibmd.ino # Main Arduino code
├── 📂 docs # Documentation
│   ├── sim2.png # Circuit schematic
├── 📂 simulation # Simulation Results
│   ├── Proteus_Simulation
├── LICENSE # License file
├── .gitignore # Git ignore file


## 📜 References
- Valoen, L. O., & Nærland, T. (2003). [Battery Management Systems for Large Lithium-Ion Battery Packs](https://ieeexplore.ieee.org/document/1226476).
- Steinhart, H., & Hart, S. R. (1968). [Calibration Curves for Thermistors](https://www.sciencedirect.com/science/article/abs/pii/0011747168900327).

## 🏆 Conclusion
The SIBM offers a robust solution for battery monitoring, with potential for intelligent BMS advancements using machine learning.

---

🚀 **Developed by:** ahtishamsudheer@gmail.com

🌟 If you find this project useful, give it a ⭐ on GitHub!
