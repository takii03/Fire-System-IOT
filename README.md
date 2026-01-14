# Fire-System-IOT
IoT-Based Fire Detection and Extinguishing System using ESP32 DevKit V1 

# About
This project implements a low-cost, IoT-enabled prototype for early fire detection and automatic extinguishing using the ESP32 DevKit V1 as the main controller. The system integrates a flame sensor, MQ2 smoke sensor, DHT11 (temperature & humidity), water level sensor, two servo motors, relaycontrolled water pump, LEDs, and an active buzzer. Sensor readings and control are available via the Blynk mobile app for real-time remote monitoring.

 #Components List
● ESP32 DevKit V1 — Main microcontroller with Wi-Fi for IoT connectivity.
● Flame sensor — Digital flame detection (IR-based).
● MQ2 smoke/gas sensor —Analog sensor for smoke and gas concentration,
● DHT11 — Temperature and humidity sensor,
● Water level sensor — Simple probe-based sensor to detect tank water level,
● Relay module (5V) — Controls the high-current 5V water pump, 
● Water pump — Small DC pump powered from 5V through relay,
● Servo motors (x2) — For aiming the nozzle,
● Active buzzer — Audible alarm .
● LEDs (2) — Visual indicators: LEDs (each with 200Ω resistor).
● Breadboard power supply — 5V and 3.3V rails for sensors and actuators.
● Jumper wires, resistors (200Ω for LEDs), mounting hardware 

# Software Implementation
● Platform: Platformio for ESP32
● Libraries used: WiFi.h, BlynkSimpleEsp32.h, DHT.h, ESP32Servo.h
● Logic: Continuous loop reads sensors, updates Blynk virtual pins, evaluates fireDetected boolean,
actuates outputs (buzzer, LEDs, relay, servos) and ensures water-level safety. 
