
Circuit Connection & Pinout Guide
Proper wiring and grounding are critical to prevent electrical noise from the stepper motor from corrupting the high-resolution load cell readings.
🔌 Pin Mapping (ESP32)
Component
Component Pin
ESP32 GPIO Pin
Notes
A4988 Driver
STEP
GPIO 27
Microstepping pulse train from Core 0
A4988 Driver
DIR
GPIO 26
Direction control (High = Down, Low = Up)
HX711 ADC
DOUT (Data)
GPIO 16
24-bit differential data stream (Read on Core 1)
HX711 ADC
SCK (Clock)
GPIO 4
Clock signal for HX711
AS7341 Sensor
SDA
GPIO 21 (Default I2C)
Multi-channel spectral data bus
AS7341 Sensor
SCL
GPIO 22 (Default I2C)
I2C clock line

⚡ Power & Grounding Guidelines
Star Ground Topology: Connect the 12V motor ground, ESP32 digital ground, and HX711 analog ground to a single central star-ground point to eliminate ground-loop noise on the strain gauge.
Spike Suppression: Solder the 100\,\mu\text{F} capacitor directly across VMOT and GND right at the A4988 driver pins to suppress inductive voltage spikes during motor stepping.
