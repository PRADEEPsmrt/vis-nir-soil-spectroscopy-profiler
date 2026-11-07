# vis-nir-soil-spectroscopy-profiler

Vis-NIR Soil Spectroscopy & Automated Soil Profiler (AgriProbe)
​An automated, in-situ mechatronic soil profiler designed to capture depth-stratified soil penetration resistance and visible-to-near-infrared (Vis-NIR) diffuse reflectance for rapid, non-destructive soil quality and nutrient estimation.
​🚀 Overview
​Traditional soil testing relies on manual core sampling and slow laboratory analysis, which destroys depth information. Manual penetrometers are prone to operator variability and easily damaged by stones. AgriProbe automates the vertical insertion of a multi-sensor probe at a controlled speed (2\text{ mm/s}), acquiring real-time physical and optical data to locate hardpans and estimate soil properties.  
​🔍 Key Features
​Controlled-Speed Penetration: Driven by a NEMA 17 stepper motor and T8 lead screw carriage at a precise 2\text{ mm/s}.  
​Simultaneous Multi-Parameter Sensing: Combines an HX711 load cell amplifier (for axial penetration resistance) with an AS7341 11-channel multi-spectral sensor (for Vis-NIR diffuse reflectance).  
​Real-Time Safety Interlock: Features a Core 0 safety loop on the ESP32 that halts and retracts the probe in under 50\text{ ms} upon encountering a 45 N obstacle.  
​Live Telemetry & Dashboard: Streams live JSON packets via USB Web Serial and BLE to a custom Netlify dashboard and mobile interface.  
​⚙️ System Architecture & Hardware
​Microcontroller: ESP32 Dual-Core MCU (FreeRTOS partitioning for real-time safety vs. telemetry).  
​Actuation: NEMA 17 Stepper Motor, A4988 driver, T8 lead screw, and twin 8 mm guide rods with LM8UU linear bearings.  
​Sensing: AS7341 11-channel spectral sensor (415\text{ nm} to 940\text{ nm}) and 5 kg cantilever load cell.  
​Connectivity & Storage: Wi-Fi/BLE telemetry and local Micro-SD flash buffering for network drops.  