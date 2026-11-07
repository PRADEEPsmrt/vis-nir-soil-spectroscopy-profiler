# Circuit Wiring & Pinout Guide

## ⚠️ Important Ground Rule
To eliminate motor-induced noise on microvolt load cell readings, use a **centralized star ground** joining the 12V motor ground, ESP32 digital ground, and HX711 analog ground at a single point. A $100\,\mu\text{F}$ capacitor must be soldered directly across VMOT and GND at the A4988 driver.

## Pin Connections

### 1. NEMA 17 Stepper & A4988 Driver
* **STEP Pin** $\rightarrow$ ESP32 GPIO 27
* **DIR Pin** $\rightarrow$ ESP32 GPIO 26
* **VMOT / GND** $\rightarrow$ 12V DC Bus (with $100\,\mu\text{F}$ suppression capacitor)
* **SLEEP / RESET** $\rightarrow$ Jumpered together on the driver module

### 2. 5 kg Load Cell & HX711 ADC
* **DT (Data)** $\rightarrow$ ESP32 GPIO 16
* **SCK (Clock)** $\rightarrow$ ESP32 GPIO 4
* **VCC / GND** $\rightarrow$ 3.3V / Star Ground

### 3. AS7341 Multi-Spectral Sensor
* **SDA** $\rightarrow$ ESP32 Default SDA (GPIO 21)
* **SCL** $\rightarrow$ ESP32 Default SCL (GPIO 22)
* **VCC / GND** $\rightarrow$ 3.3V / Ground
