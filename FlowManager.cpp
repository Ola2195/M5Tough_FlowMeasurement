#include "FlowManager.h"

#define NUM_SENSORS 2    // Number of flow sensors
#define SENSOR_PIN_1 2   // Pin for the first sensor
#define SENSOR_PIN_2 36  // Pin for the second sensor

// Initialize the static instance pointer
FlowManager* FlowManager::instance = nullptr;

FlowManager::FlowManager(void)
  : measurementFlag(false), timer(nullptr), timeCount(0), numSensors(NUM_SENSORS),
    firstMeasurement(true) {
  instance = this;  // Set the static instance pointer to this instance
  sensors = new FlowSensor*[numSensors];
  sensors[0] = new FlowSensor(SENSOR_PIN_1);
  sensors[1] = new FlowSensor(SENSOR_PIN_2);
}

FlowManager::~FlowManager(void) {
  // Clean up dynamically allocated memory
  for (size_t i = 0; i < numSensors; ++i) {
    delete sensors[i];
  }
  delete[] sensors;
}

void FlowManager::setupTimer(void) {
  //timer = timerBegin(0, 80, true);                          // Timer 0, prescaler 80 (for 1MHz)
  timer = timerBegin(1000000);
  //timerAttachInterrupt(timer, FlowManager::onTimer, true);  // Attach interrupt
  timerAttachInterrupt(timer, FlowManager::onTimer);
  //timerAlarmWrite(timer, 100000, true);                     // 100 ms = 100000 us
  //timerAlarmEnable(timer);
  timerAlarm(timer, 1000000, true, 0);
}

void FlowManager::setupFlowSensors(void) {
  for (size_t i = 0; i < numSensors; ++i) {
    sensors[i]->setupFlowSensor();
  }
}

void FlowManager::measurementsProcessing(void) {
  portENTER_CRITICAL_ISR(&interruptManagerMux);
  measurementFlag = false;
  portEXIT_CRITICAL_ISR(&interruptManagerMux);

  for (size_t i = 0; i < numSensors; ++i) {
    if (!firstMeasurement) {
      sensors[i]->updateSamples();
      sensors[i]->calculateFrequency();
      sensors[i]->setAvgFrequency();
    }
    firstMeasurement = false;
  }
}

void FlowManager::reset(void) {
  //timerAlarmDisable(timer);  // Disable timer interrupts during reset

  for (size_t i = 0; i < numSensors; ++i) {
    sensors[i]->detachSensorInterrupt();  // Detach sensor interrupts
  }

  for (size_t i = 0; i < numSensors; ++i) {
    sensors[i]->reset();  // Reset each sensor
  }

  timeCount = 0;
  measurementFlag = false;
  firstMeasurement = true; 

  for (size_t i = 0; i < numSensors; ++i) {
    sensors[i]->attachSensorInterrupt();  // Reattach sensor interrupts
  }

  //timerAlarmEnable(timer);  // Enable timer interrupts after reset
  timerAlarm(timer, 1000000, true, 0);
}

FlowSensor* FlowManager::getSensor(size_t index) const {
  if (index < numSensors) {
    return sensors[index];
  }
  return nullptr;
}

size_t FlowManager::getNumSensors(void) const {
  return numSensors;
}

int FlowManager::getTimeCount(void) const {
  return timeCount;
}

void IRAM_ATTR FlowManager::onTimer(void) {
  portENTER_CRITICAL_ISR(&instance->interruptManagerMux);
  if (instance) {  // Check if the instance pointer is valid
    instance->timeCount++;
    if (instance->timeCount >= 10) {  // Process every 1 second
      for (size_t i = 0; i < instance->numSensors; ++i) {
        instance->sensors[i]->updatePulseCount();
      }
      instance->timeCount = 0;
      instance->measurementFlag = true;
    }
  }
  portEXIT_CRITICAL_ISR(&instance->interruptManagerMux);
}