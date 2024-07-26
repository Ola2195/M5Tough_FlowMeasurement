# M5Tough_FlowMeasurement

M5Tough_FlowMeasurement is a project that utilizes the M5Stack TOUGH ESP32 microcontroller to measure liquid flow using one or more flow sensors. The project displays real-time measurements on the device's screen, providing both instantaneous and averaged flow rates for sensors.

## Description

The M5Tough_FlowMeasurement project is designed for monitoring liquid flow using flow sensors connected to the M5Stack TOUGH ESP32 microcontroller. The project displays flow rates in Hertz (Hz) on the device's screen, supporting real-time monitoring for up to two sensors.

Key components and functionality include:

- **Accurate Pulse Counting**: Utilizing the ESP32's interrupts and timers, the project ensures precise pulse counting from flow sensors, providing accurate flow measurements.
- **Averaged Measurements**: To mitigate fluctuations and noise in the flow readings, measurements are averaged over the last 10 samples. During the initial measurement phase, the average is progressively calculated as more samples are collected, stabilizing the readings.
- **Real-Time Display**: The screen displays both the averaged flow rate and instantaneous measurements for each connected sensor.
- **Reset Functionality**: A reset button on the screen allows users to reset all counters and measurements, offering flexibility during testing or operation.

### Technical Details

- **Timer Configuration**: The timer is configured with a precision of 100 milliseconds (ms), ensuring high-resolution pulse counting.
- **GPIO Interrupt Handling**: Interrupt handling was tested up to 100 kHz. At 101 kHz, signal integrity issues were observed, indicating the system's operational limits.
- **Multiple Sensor Support**: The system is prepared to handle measurements for two sensors simultaneously, making it suitable for various applications where multi-sensor monitoring is required.

## Features

- **Real-Time Monitoring**: Monitor liquid flow rates for up to two sensors in real time.
- **Precise Measurements**: Utilization of ESP32's interrupts and timers for accurate pulse counting.
- **Averaged Readings**: Averaging of flow measurements over the last 10 samples to reduce noise and fluctuations.
- **Display**: Visual representation of flow rates in Hertz (Hz) on the M5Stack TOUGH screen for each sensor.
- **Reset Button**: On-screen button for resetting all counters and measurements, allowing for quick reinitialization.

## Hardware Requirements

To set up and run this project, you will need the following hardware components:

- **M5Stack TOUGH ESP32 microcontroller**: The main controller responsible for processing sensor data and displaying results.
- **Flow Sensors**: One or more flow sensors with pulse output capability. These sensors will be used to measure the liquid flow rate.
- **Connecting Wires**: Wires for connecting the flow sensors to the GPIO pins on the M5Stack TOUGH.

## Installation

Follow these steps to install and set up the M5Tough_FlowMeasurement project on your M5Stack TOUGH ESP32 microcontroller:

1. **Open the Project in Arduino IDE**:
   - Download the project files and open the main sketch in the Arduino IDE.

2. **Install Required Libraries**:
   - Ensure that you have the following libraries installed in the Arduino IDE:
     - `M5Unified`: Provides support for M5Stack devices.
     - `Arduino.h` (ESP32 core): Core library for ESP32 development.

3. **Configure Board Settings**:
   - Set the appropriate board settings in the Arduino IDE for M5Stack TOUGH ESP32. Select the correct board type and COM port from the Tools menu.

4. **Upload the Code**:
   - Connect your M5Stack TOUGH ESP32 to the computer via USB.
   - Upload the code to the device by clicking the "Upload" button in the Arduino IDE.

## Usage

To use the M5Tough_FlowMeasurement project, follow these instructions:

1. **Connect the Flow Sensors**:
   - Connect the flow sensors to the designated GPIO pins on the M5Stack TOUGH.
   - Update the GPIO pin numbers in the `FlowManager.cpp` sketch if necessary. Change the values on lines 4 and 5 to match your wiring configuration:
     ```cpp
     #define SENSOR_PIN_1    2   // Update to the GPIO pin connected to Sensor 1
     #define SENSOR_PIN_2    36  // Update to the GPIO pin connected to Sensor 2
     ```

2. **Power On the Device**:
   - Turn on the M5Stack TOUGH device. Ensure that it is properly powered and connected to the flow sensors.

3. **View Real-Time Flow Measurements**:
   - The device will display flow rates for each sensor on the screen in real time.
   - The displayed values include both the averaged flow rate and the instantaneous measurement for each sensor.

4. **Reset Measurements**:
   - Use the on-screen reset button to clear all measurements and start fresh. This can be useful during setup or testing phases.

## Example View

![Example View](Example.jpeg)

In this image, you can see how the real-time measurements are presented, with both instantaneous and averaged values clearly visible for each connected sensor.

## M5Stack Core2 (AWS) Tough - Pinout

| **GPIO**           | **Functions**                        | **Used by**                              | **Availability**       |
|:------------------:|:------------------------------------:|:----------------------------------------:|:----------------------:|
| **GPIO 0**         | `ADC2_CH1`                           | M-Bus, **SPK_LRCK**, PDM_C (Core2)       | Partially Available    |
| **GPIO 1**         | `USB_TX`                             | M-Bus, **Serial**                        | Occupied               |
| **GPIO 2**         | `ADC2_CH2`                           | M-Bus, **SPK_D**                         | Occupied               |
| **GPIO 3**         | `USB_RX`                             | M-Bus, **Serial**                        | Occupied               |
| **GPIO 4**         | `ADC2_CH0`                           | **TF_CS**                                | Partially Available    |
| **GPIO 5**         |                                      | **LCD_CS**                               | Occupied               |
| **GPIO 9**         |                                      | ---                                      | Free                   |
| **GPIO 10**        |                                      | ---                                      | Free                   |
| **GPIO 12**        | `ADC2_CH5`                           | **SPK_BCLK**                             | Partially Available    |
| **GPIO 13**        | `ADC2_CH4`                           | M-Bus, RXD2                              | Partially Available    |
| **GPIO 14**        | `ADC2_CH6`                           | M-Bus, TXD2                              | Partially Available    |
| **GPIO 15**        | `ADC2_CH3`                           | **LCD_D/C**                              | Occupied               |
| **GPIO 16**        | `PSRAM`                              | ---                                      | Free                   |
| **GPIO 17**        | `PSRAM`                              | ---                                      | Free                   |
| **GPIO 18**        |                                      | **SPI_SCLK**                             | Occupied               |
| **GPIO 19**        |                                      | M-Bus                                    | Occupied               |
| **GPIO 21**        |                                      | **I2C1_SDA**                             | Occupied               |
| **GPIO 22**        |                                      | **I2C1_SCL**                             | Occupied               |
| **GPIO 23**        |                                      | **SPI_MOSI**                             | Occupied               |
| **GPIO 25**        | `DAC1`                               | M-Bus, **RGB LED** (AWS)                 | Occupied               |
| **GPIO 26**        | `DAC2`                               | M-Bus                                    | Partially Available    |
| **GPIO 27**        | `ADC2_CH7`                           | M-Bus                                    | Partially Available    |
| **GPIO 32**        | `ADC1_CH4`                           | M-Bus, `PORT.A`, I2C0_SDA                | Occupied               |
| **GPIO 33**        | `ADC1_CH5`                           | M-Bus, `PORT.A`, I2C0_SCL                | Occupied               |
| **GPIO 34**        | `ADC1_CH6`                           | M-Bus, **PDM_D** (Core2)                 | Occupied               |
| **GPIO 35**        | `ADC1_CH7`                           | M-Bus                                    | Partially Available    |
| **GPIO 36**        | `ADC1_CH0`                           | M-Bus                                    | Partially Available    |
| **GPIO 37**        | `ADC1_CH1`                           | ---                                      | Free                   |
| **GPIO 38**        | `ADC1_CH2`                           | M-Bus, **SPI_MISO**                      | Occupied               |
| **GPIO 39**        | `ADC1_CH3`                           | **TP_INT**                               | Occupied               |