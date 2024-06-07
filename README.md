# M5Tough_FlowMeasurement

M5Tough_FlowMeasurement is a project based on the M5Stack TOUGH ESP32 microcontroller that allows for measuring liquid flow using a flow sensor. The measurement results are displayed on the device's screen in real-time.

## Description

This project uses a liquid flow sensor to monitor and display the flow rate in liters per minute (L/min). The results are updated every second and presented on the M5Tough's display. The code utilizes the ESP32 microcontroller's internal timers and interrupts to ensure accurate and reliable measurements.

## Features

- Real-time liquid flow measurement
- Utilizing ESP32 interrupts and timers for precise pulse counting from the flow sensor
- Automatic conversion of pulses to flow units (L/min)
- Displaying results on the M5Tough screen

## Hardware Requirements

- M5Stack TOUGH ESP32
- Flow sensor with pulse output
- Connecting wires

## Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/yourusername/M5Tough_FlowMeasurement.git
    ```
2. Open the project in Arduino IDE.
3. Ensure you have the following libraries installed:
    - M5Unified
    - Arduino.h (ESP32 core)
4. Configure the appropriate board settings in the Arduino IDE for M5Stack TOUGH ESP32.
5. Upload the code to the M5Stack TOUGH ESP32 device.

## Usage

1. Connect the flow sensor to pin 36 on the M5Tough or change the GPIO pin number in line 8 in the M5Tough file.
```cpp
const int sensorPin = 36;  // Pin connected to the flow sensor
```
2. Power on the device.
3. The flow rate will be displayed on the M5Tough screen in real-time.
