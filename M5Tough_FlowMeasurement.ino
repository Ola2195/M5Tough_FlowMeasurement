#include <Arduino.h>
#include <M5Unified.h>

#include "include/FlowManager.h"
#include "include/M5ToughDisplay.h"

FlowManager manager;
M5ToughDisplay display;

/*
 * Initial setup
 */
void setup() {
  Serial.begin(115200);  // Initialize serial port with a baud rate of 115200

  manager.setupTimer();        // Set up the timer
  manager.setupFlowSensors();  // Initialize the flow sensors

  display.startDrawing();      // Start the display
  display.drawButtons();   // Draw the reset button on the display
}

/*
 * Main loop
 */
void loop() {
  //m5::rtc_date_t date;
  //m5::rtc_time_t time;
  //M5.Rtc.getDate(&date);
  //M5.Rtc.getTime(&time);

  if (manager.measurementFlag) {
    manager.measurementsProcessing();  // Process measurements if the flag is set
  }

  display.firstDisplaying();  // Set initial display settings

  //M5.Lcd.printf("%04d-%02d-%02d %02d:%02d:%02d\n\n",
  //              date.year, date.month, date.date,
  //              time.hours, time.minutes, time.seconds);

  for (size_t i = 0; i < manager.getNumSensors(); ++i) {
    FlowSensor* sensor = manager.getSensor(i);
    if (sensor) {
      // Display sensor measurements
      display.displayMeasurements(sensor->getInstantFrequency(), sensor->getAvgFrequency());
    }
  }

  display.displayDividingLine();

  if (display.isPressed() == M5ToughDisplay::RESET_BUTTON) {
    manager.reset();        // Reset the flow manager
    display.clearScreen();  // Clear the display screen
  }
}