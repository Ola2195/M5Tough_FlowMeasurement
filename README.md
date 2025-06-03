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

---

# M5Tough_FlowMeasurement

M5Tough_FlowMeasurement to projekt wykorzystujący mikrokontroler M5Stack TOUGH ESP32 do pomiaru przepływu cieczy za pomocą jednego lub więcej czujników przepływu. Projekt wyświetla pomiary w czasie rzeczywistym na ekranie urządzenia, prezentując zarówno chwilowy, jak i uśredniony przepływ.

## Opis

Projekt M5Tough_FlowMeasurement służy do monitorowania przepływu cieczy z użyciem czujników przepływu podłączonych do mikrokontrolera M5Stack TOUGH ESP32. Projekt wyświetla prędkości przepływu w hercach (Hz) na ekranie urządzenia, wspierając jednoczesne monitorowanie maksymalnie dwóch czujników.

Główne komponenty i funkcje:

- **Dokładne zliczanie impulsów**: Wykorzystanie przerwań i timerów ESP32 zapewnia precyzyjne zliczanie impulsów z czujników przepływu.
- **Uśrednione pomiary**: W celu redukcji szumów i wahań pomiary są uśredniane z ostatnich 10 próbek. W początkowej fazie średnia jest stopniowo wyliczana wraz z napływem nowych danych.
- **Wyświetlacz czasu rzeczywistego**: Ekran pokazuje zarówno uśrednione, jak i chwilowe wartości przepływu dla każdego czujnika.
- **Funkcja resetu**: Przycisk na ekranie umożliwia zresetowanie wszystkich liczników i pomiarów – przydatne podczas testów lub użytkowania.

### Szczegóły techniczne

- **Konfiguracja timera**: Timer ustawiony jest na rozdzielczość 100 milisekund (ms), zapewniając wysoką precyzję zliczania impulsów.
- **Obsługa przerwań GPIO**: Obsługa przerwań testowana była do 100 kHz. Przy 101 kHz zauważono problemy z integralnością sygnału, co wskazuje na granice działania systemu.
- **Obsługa wielu czujników**: System umożliwia jednoczesny pomiar z dwóch czujników, co sprawia, że nadaje się do różnych zastosowań wymagających monitorowania wielu przepływów.

## Funkcje

- **Monitorowanie w czasie rzeczywistym**: Obsługa do dwóch czujników jednocześnie.
- **Dokładne pomiary**: Wykorzystanie przerwań i timerów ESP32 dla precyzyjnych wyników.
- **Uśrednianie odczytów**: Średnia z 10 ostatnich pomiarów ogranicza zakłócenia i fluktuacje.
- **Wyświetlacz**: Wizualna prezentacja przepływu w Hz dla każdego czujnika na ekranie M5Stack TOUGH.
- **Przycisk resetu**: Reset wszystkich liczników za pomocą dotykowego przycisku na ekranie.

## Wymagania sprzętowe

Do uruchomienia projektu potrzebne będą:

- **M5Stack TOUGH ESP32** – główny mikrokontroler przetwarzający dane i wyświetlający wyniki.
- **Czujniki przepływu** – jeden lub więcej czujników z wyjściem impulsowym do pomiaru przepływu cieczy.
- **Przewody połączeniowe** – do podłączenia czujników do pinów GPIO w M5Stack TOUGH.

## Instalacja

1. **Otwórz projekt w Arduino IDE**:

   - Pobierz pliki projektu i otwórz główny szkic w Arduino IDE.

2. **Zainstaluj wymagane biblioteki**:

   - W Arduino IDE upewnij się, że masz zainstalowane:

     - `M5Unified` – obsługa urządzeń M5Stack.
     - `Arduino.h` (ESP32 core) – podstawowa biblioteka dla ESP32.

3. **Skonfiguruj ustawienia płytki**:

   - Wybierz odpowiednią płytkę (M5Stack TOUGH ESP32) i port COM w menu „Narzędzia”.

4. **Wgraj kod**:

   - Podłącz urządzenie M5Stack TOUGH ESP32 do komputera przez USB.
   - Kliknij „Wgraj” w Arduino IDE, aby przesłać kod do urządzenia.

## Użytkowanie

1. **Podłącz czujniki przepływu**:

   - Podłącz czujniki do odpowiednich pinów GPIO w M5Stack TOUGH.
   - W razie potrzeby zaktualizuj numery pinów w pliku `FlowManager.cpp`, zmieniając linie 4 i 5:

     ```cpp
     #define SENSOR_PIN_1    2   // Zmień na pin podłączony do czujnika 1
     #define SENSOR_PIN_2    36  // Zmień na pin podłączony do czujnika 2
     ```

2. **Włącz urządzenie**:

   - Włącz M5Stack TOUGH i upewnij się, że czujniki są poprawnie podłączone.

3. **Obserwuj pomiary przepływu**:

   - Na ekranie pojawią się odczyty przepływu dla każdego czujnika w czasie rzeczywistym – zarówno uśrednione, jak i chwilowe wartości.

4. **Zresetuj pomiary**:

   - Skorzystaj z przycisku reset na ekranie, aby wyczyścić pomiary i rozpocząć nowe.

## Przykładowy widok

![Przykładowy widok](Example.jpeg)

Na ilustracji widać prezentację pomiarów w czasie rzeczywistym – wartości uśrednione i chwilowe są czytelnie widoczne dla każdego podłączonego czujnika.

## M5Stack Core2 (AWS) Tough – Rozkład pinów

|   **GPIO**  | **Funkcje** |           **Używane przez**          |   **Dostępność**   |
| :---------: | :---------: | :----------------------------------: | :----------------: |
|  **GPIO 0** |  `ADC2_CH1` | M-Bus, **SPK_LRCK**, PDM_C (Core2)   | Częściowo dostępne |
|  **GPIO 1** |   `USB_TX`  |           M-Bus, **Serial**          |       Zajęte       |
|  **GPIO 2** |  `ADC2_CH2` |           M-Bus, **SPK_D**           |       Zajęte       |
|  **GPIO 3** |   `USB_RX`  |           M-Bus, **Serial**          |       Zajęte       |
|  **GPIO 4** |  `ADC2_CH0` |              **TF_CS**               | Częściowo dostępne |
|  **GPIO 5** |             |              **LCD_CS**              |       Zajęte       |
|  **GPIO 9** |             |                  ---                 |        Wolne       |
| **GPIO 10** |             |                  ---                 |        Wolne       |
| **GPIO 12** |  `ADC2_CH5` |             **SPK_BCLK**             | Częściowo dostępne |
| **GPIO 13** |  `ADC2_CH4` |              M-Bus, RXD2             | Częściowo dostępne |
| **GPIO 14** |  `ADC2_CH6` |              M-Bus, TXD2             | Częściowo dostępne |
| **GPIO 15** |  `ADC2_CH3` |             **LCD\_D/C**             |       Zajęte       |
| **GPIO 16** |   `PSRAM`   |                  ---                 |        Wolne       |
| **GPIO 17** |   `PSRAM`   |                  ---                 |        Wolne       |
| **GPIO 18** |             |             **SPI_SCLK**             |       Zajęte       |
| **GPIO 19** |             |                 M-Bus                |       Zajęte       |
| **GPIO 21** |             |             **I2C1_SDA**             |       Zajęte       |
| **GPIO 22** |             |             **I2C1_SCL**             |       Zajęte       |
| **GPIO 23** |             |             **SPI_MOSI**             |       Zajęte       |
| **GPIO 25** |    `DAC1`   |       M-Bus, **RGB LED** (AWS)       |       Zajęte       |
| **GPIO 26** |    `DAC2`   |                 M-Bus                | Częściowo dostępne |
| **GPIO 27** |  `ADC2_CH7` |                 M-Bus                | Częściowo dostępne |
| **GPIO 32** |  `ADC1_CH4` |      M-Bus, `PORT.A`, I2C0_SDA       |       Zajęte       |
| **GPIO 33** |  `ADC1_CH5` |      M-Bus, `PORT.A`, I2C0_SCL       |       Zajęte       |
| **GPIO 34** |  `ADC1_CH6` |       M-Bus, **PDM_D** (Core2)       |       Zajęte       |
| **GPIO 35** |  `ADC1_CH7` |                 M-Bus                | Częściowo dostępne |
| **GPIO 36** |  `ADC1_CH0` |                 M-Bus                | Częściowo dostępne |
| **GPIO 37** |  `ADC1_CH1` |                  ---                 |        Wolne       |
| **GPIO 38** |  `ADC1_CH2` |         M-Bus, **SPI_MISO**          |       Zajęte       |
| **GPIO 39** |  `ADC1_CH3` |              **TP_INT**              |       Zajęte       |