#include <Arduino.h>
#include <M5Unified.h>

#include "include/FlowManager.h"
#include "include/View.h"
#include "include/DisplayRenderer.h"

FlowManager manager;
MainMeasurementView* mainView;

/*
 * Initial setup
 */
void setup() {
  Serial.begin(115200);  // Initialize serial port with a baud rate of 115200

  manager.setupTimer();        // Set up the timer
  manager.setupFlowSensors();  // Initialize the flow sensors

  mainView = new MainMeasurementView(manager);
}

/*
 * Main loop
 */
void loop() {
  if (manager.measurementFlag) {
    manager.measurementsProcessing();  // Process measurements if the flag is set
  }

  mainView->render();
  mainView->update();
}