#include <Arduino.h>
#include <M5Unified.h>

#include "include/FlowManager.h"
#include "include/View.h"

FlowManager manager;
MainMeasurementView* mainView;
//SensorDetailView* secoundSensorView;

/*
 * Initial setup
 */
void setup() {
  M5.begin();
  Serial.begin(115200);  // Initialize serial port with a baud rate of 115200

  manager.setupTimer();        // Set up the timer
  manager.setupFlowSensors();  // Initialize the flow sensors

  mainView = new MainMeasurementView(manager);
  mainView->setup();
  //secoundSensorView = new SensorDetailView(manager.getSensor(1), 1);
}

/*
 * Main loop
 */
void loop() {
  if (manager.measurementFlag) {
    manager.measurementsProcessing();  // Process measurements if the flag is set
  }

  //secoundSensorView->render();
  //secoundSensorView->update();
  mainView->render();
  mainView->update();
}