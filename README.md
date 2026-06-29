# ESP32 Robotics Laboratories

This repository contains code, schematics, and documentation for ESP32-based robotics and embedded systems laboratories.

## Repository Contents

* **[LED_Brightness_Control/](file:///c:/Users/USER/Desktop/ROBOTICS/LED_Brightness_Control/)**:
  * **[LED_Brightness_Control.ino](file:///c:/Users/USER/Desktop/ROBOTICS/LED_Brightness_Control/LED_Brightness_Control.ino)**: Arduino sketch for Laboratory 1.

---

## Laboratory 1: LED Brightness Control Using a Push button/wire

### Objective
Create an ESP32 program that controls the brightness of an LED using a physical push button switch.

### Problem Statement / Sequence
1. When ESP32 starts, the LED is OFF.
2. Press the switch to start the sequence.
3. The LED should turn on at 25% brightness.
4. Every 3 seconds, the brightness increases by 25%, until 100% (25% -> 50% -> 75% -> 100%).
5. After 100%, the LED should remain ON.
6. Pressing the button again should reset the sequence (LED OFF, wait for press).

### Wiring Details
* **LED**: Connected to pin **D2** (via a 470-ohm current-limiting resistor to ground).
* **Push Button**: Connected to pin **D4** (using an external 1K-ohm pull-down resistor to ground, and connected to 3.3V).

### How to Run
1. Install the Arduino IDE.
2. Install the ESP32 board manager in the IDE.
3. Wire the circuit on your breadboard as specified.
4. Open `LED_Brightness_Control.ino` in Arduino IDE, select your ESP32 board and port, then compile and upload the code.
