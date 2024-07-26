#include <Arduino.h>

#include "FlowManager.h"
#include "M5ToughDisplay.h"

FlowManager manager;
M5ToughDisplay display;

/*
 * Initial setup
 */
void setup() {
  Serial.begin(115200);  // Initialize serial port with a baud rate of 115200

  display.startDrawing();      // Start the display
  manager.setupTimer();        // Set up the timer
  manager.setupFlowSensors();  // Initialize the flow sensors
  display.drawResetButton();   // Draw the reset button on the display
}

/*
 * Main loop
 */
void loop() {
  if (manager.measurementFlag) {
    manager.measurementsProcessing();  // Process measurements if the flag is set
  }

  display.firstDisplaying();  // Set initial display settings
  for (size_t i = 0; i < manager.getNumSensors(); ++i) {
    FlowSensor* sensor = manager.getSensor(i);
    if (sensor) {
      // Display sensor measurements
      display.displayMeasurements(sensor->getInstantFrequency(), sensor->getAvgFrequency());
    }
  }

  display.displayDividingLine();  // Draw a dividing line on the display

  if (display.isPressed() == M5ToughDisplay::RESET_BUTTON) {
    manager.reset();        // Reset the flow manager
    display.clearScreen();  // Clear the display screen
  }
}
