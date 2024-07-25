# M5Tough_FlowMeasurement

M5Tough_FlowMeasurement is a project based on the M5Stack TOUGH ESP32 microcontroller designed to measure liquid flow one or more flow sensors. The measured results are displayed in real-time on the device's screen.

## Description

This project utilizes liquid flow sensors connected to the M5Stack TOUGH ESP32 microcontroller to monitor and display the flow rate in Hertz (Hz) for one or more sensors. The view is currently prepared for two measurements.
The code leverages interrupts and timers of the ESP32 for accurate pulse counting from the flow sensors, ensuring precise measurement results.
The timer is configured with a precision of 100 milliseconds (ms).
Measurements are averaged over the last 10 samples to smooth out fluctuations in the flow rate. Initially, the average is calculated progressively as more samples are collected to stabilize the readings.
The screen displays the flow rate both as an averaged value and as an instant measurement for each connected sensor.
A reset button on the screen allows the user to reset all counters and measurements.

GPIO interrupt handling was tested up to 100 kHz; at 101 kHz, signal integrity issues were observed.

## Features

- Real-time monitoring of liquid flow rate for up to two sensors
- Utilization of ESP32 interrupts and timers for precise pulse counting from the flow sensors
- Averaging of flow measurements over the last 10 samples to reduce noise
- Displaying flow rate in Hertz (Hz) on the M5Stack TOUGH screen for each sensor
- Reset button for resetting all counters and measurements

## Hardware Requirements

- M5Stack TOUGH ESP32 microcontroller
- One or more flow sensors sensor with pulse output
- Connecting wires

## Installation

1. Open the project in Arduino IDE.
2. Ensure you have the following libraries installed:
    - M5Unified
    - Arduino.h (ESP32 core)
3. Configure the appropriate board settings in the Arduino IDE for M5Stack TOUGH ESP32.
4. Upload the code to the M5Stack TOUGH ESP32 device.

## Usage

1. Connect the flow sensors to the designated GPIO pins on the M5Tough and change the GPIO pin number in lines 10 and 11 in the M5Tough file.
```cpp
#define SENSOR_PIN_1    2
#define SENSOR_PIN_2    36
```
2. Power on the device.
3. The flow rate for each sensor will be displayed on the M5Stack TOUGH screen in real-time. The displayed values include the averaged flow rate and the instantaneous measurement for each sensor.
4. Use the on-screen reset button to clear all measurements and start fresh as needed.

![Example View](Example.jpeg)

## M5Stack Core2 (AWS) Tough - Pinout

| **GPIO**           | **Functions**                                                                | **Used by**                              |
|:------------------:|:----------------------------------------------------------------------------:|:----------------------------------------:|
| **GPIO 0**         | `ADC2_CH1`                                                                   | M-Bus, **SPK_LRCK**, PDM_C (Core2)       |
| **GPIO 1**         | `USB_TX`                                                                     | M-Bus, **Serial**                        |
| **GPIO 2**         | `ADC2_CH2`                                                                   | M-Bus, **SPK_D**                         |
| **GPIO 3**         | `USB_RX`                                                                     | M-Bus, **Serial**                        |
| **GPIO 4**         | `ADC2_CH0`                                                                   | **TF_CS**                                |
| **GPIO 5**         |                                                                            | **LCD_CS**                               |
| **GPIO 9**         |                                                                            | ---                                      |
| **GPIO 10**        |                                                                            | ---                                      |
| **GPIO 12**        | `ADC2_CH5`                                                                   | **SPK_BCLK**                             |
| **GPIO 13**        | `ADC2_CH4`                                                                   | M-Bus, RXD2                              |
| **GPIO 14**        | `ADC2_CH6`                                                                   | M-Bus, TXD2                              |
| **GPIO 15**        | `ADC2_CH3`                                                                   | **LCD_D/C**                              |
| **GPIO 16**        | `PSRAM`                                                                      | ---                                      |
| **GPIO 17**        | `PSRAM`                                                                      | ---                                      |
| **GPIO 18**        |                                                                            | **SPI_SCLK**                             |
| **GPIO 19**        |                                                                            | M-Bus                                    |
| **GPIO 21**        |                                                                            | **I2C1_SDA**                             |
| **GPIO 22**        |                                                                            | **I2C1_SCL**                             |
| **GPIO 23**        |                                                                            | **SPI_MOSI**                             |
| **GPIO 25**        | `DAC1`                                                                       | M-Bus, **RGB LED** (AWS)                 |
| **GPIO 26**        | `DAC2`                                                                       | M-Bus                                    |
| **GPIO 27**        | `ADC2_CH7`                                                                   | M-Bus                                    |
| **GPIO 32**        | `ADC1_CH4`                                                                   | M-Bus, `PORT.A`, I2C0_SDA                |
| **GPIO 33**        | `ADC1_CH5`                                                                   | M-Bus, `PORT.A`, I2C0_SCL                |
| **GPIO 34**        | `ADC1_CH6`                                                                   | M-Bus, **PDM_D** (Core2)                 |
| **GPIO 35**        | `ADC1_CH7`                                                                   | M-Bus                                    |
| **GPIO 36**        | `ADC1_CH0`                                                                   | M-Bus                                    |
| **GPIO 37**        | `ADC1_CH1`                                                                   | ---                                      |
| **GPIO 38**        | `ADC1_CH2`                                                                   | M-Bus, **SPI_MISO**                      |
| **GPIO 39**        | `ADC1_CH3`                                                                   | **TP_INT**                               |

### Available Pins

#### Free Pins
- **GPIO 9**
- **GPIO 10**
- **GPIO 16**
- **GPIO 17**
- **GPIO 37** - `ADC1_CH1`

#### Partially Available Pins
- **GPIO 0** - `ADC2_CH1`: used by **M-Bus** and **SPK_LRCK**.
- **GPIO 4** - `ADC2_CH0`: used by **TF_CS**.
- **GPIO 12** - `ADC2_CH5`: used by **SPK_BCLK**.
- **GPIO 13** - `ADC2_CH4`: RXD2 in **M-Bus**.
- **GPIO 14** - `ADC2_CH6`: TXD2 in **M-Bus**.
- **GPIO 26** - `DAC2`: `M-Bus`.
- **GPIO 27** - `ADC2_CH7`: `M-Bus`.
- **GPIO 35** - `ADC1_CH7`: `M-Bus`.
- **GPIO 36** - `ADC1_CH0`: `M-Bus`.

#### Occupied Pins
- **GPIO 1** - `USB_TX`: **Serial**.
- **GPIO 2** - `ADC2_CH2`: **SPK_D**.
- **GPIO 3** - `USB_RX`: **Serial**.
- **GPIO 5**: **LCD_CS**.
- **GPIO 15** - `ADC2_CH3`: **LCD_D/C**.
- **GPIO 18**: **SPI_SCLK**.
- **GPIO 19**: `M-Bus`.
- **GPIO 21**: **I2C1_SDA**.
- **GPIO 22**: **I2C1_SCL**.
- **GPIO 23**: **SPI_MOSI**.
- **GPIO 25** - `DAC1`: **RGB LED** (AWS).
- **GPIO 32** - `ADC1_CH4`: `PORT.A`, I2C0_SDA.
- **GPIO 33** - `ADC1_CH5`: `PORT.A`, I2C0_SCL.
- **GPIO 34** - `ADC1_CH6`: **PDM_D** (Core2).
- **GPIO 38** - `ADC1_CH2`: **SPI_MISO**.
- **GPIO 39** - `ADC1_CH3`: **TP_INT**.
