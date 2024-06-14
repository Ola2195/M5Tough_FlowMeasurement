# M5Tough_FlowMeasurement

M5Tough_FlowMeasurement is a project based on the M5Stack TOUGH ESP32 microcontroller designed to measure liquid flow using a flow sensor. The measured results are displayed in real-time on the device's screen.

## Description

This project utilizes a liquid flow sensor connected to the M5Stack TOUGH ESP32 microcontroller to monitor and display the flow rate in Hertz (Hz).
The code leverages interrupts and timers of the ESP32 for accurate pulse counting from the flow sensor, ensuring precise measurement results.
The timer is configured with a precision of 100 milliseconds (ms).
Measurements are averaged over the last 10 samples to smooth out fluctuations in the flow rate. Initially, the average is calculated progressively as more samples are collected to stabilize the readings.
The screen displays the flow rate both as an averaged value and as an instant measurement.
A reset button on the screen allows the user to reset all counters and measurements.

GPIO interrupt handling was tested up to 100 kHz; at 101 kHz, signal integrity issues were observed.

## Features

- Real-time monitoring of liquid flow rate
- Utilization of ESP32 interrupts and timers for precise pulse counting from the flow sensor
- Averaging of flow measurements over the last 10 samples to reduce noise
- Displaying flow rate in Hertz (Hz) on the M5Stack TOUGH screen
- Reset button for resetting all counters and measurements

## Hardware Requirements

- M5Stack TOUGH ESP32 microcontroller
- Flow sensor with pulse output
- Connecting wires

## Installation

1. Open the project in Arduino IDE.
2. Ensure you have the following libraries installed:
    - M5Unified
    - Arduino.h (ESP32 core)
3. Configure the appropriate board settings in the Arduino IDE for M5Stack TOUGH ESP32.
4. Upload the code to the M5Stack TOUGH ESP32 device.

## Usage

1. Connect the flow sensor to pin 2 on the M5Tough or change the GPIO pin number in line 8 in the M5Tough file.
```cpp
const int sensorPin = 2;  // Pin connected to the flow sensor
```
2. Power on the device.
3. The flow rate will be displayed on the M5Stack TOUGH screen in real-time. The displayed values include the averaged flow rate and the instantaneous measurement.
