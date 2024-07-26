#include "FlowSensor.h"

// Initialize the static instance pointer
FlowSensor* FlowSensor::instance = nullptr;

FlowSensor::FlowSensor(int pin)
  : pin_(pin), pulseCount(0), lastPulseCount(0),
    frequency(0.0), sampleIndex(0), avgFrequency(0),
    firstSequence(true) {
  instance = this;  // Set the static instance pointer to this instance
  memset(samples, 0, sizeof(samples));
}

void FlowSensor::setupFlowSensor(void) {
  pinMode(pin_, INPUT_PULLUP);  // Configure pin as input with pull-up resistor
  attachSensorInterrupt();      // Attach interrupt for sensor pulses
}

void FlowSensor::attachSensorInterrupt(void) {
  attachInterrupt(digitalPinToInterrupt(pin_), FlowSensor::pulseCounter, FALLING);
}

void FlowSensor::detachSensorInterrupt(void) {
  detachInterrupt(digitalPinToInterrupt(pin_));
}

void FlowSensor::updatePulseCount(void) {
  portENTER_CRITICAL_ISR(&interruptMux);  // Enter critical section to protect shared variables
  lastPulseCount = pulseCount;
  pulseCount = 0;
  portEXIT_CRITICAL_ISR(&interruptMux);
}

void FlowSensor::calculateFrequency(void) {
  portENTER_CRITICAL_ISR(&interruptMux);  // Enter critical section to protect shared variables
  frequency = lastPulseCount;             // Frequency calculation: pulses per second
  portEXIT_CRITICAL_ISR(&interruptMux);
}

void FlowSensor::updateSamples(void) {
  samples[sampleIndex] = frequency;
  sampleIndex = (sampleIndex + 1) % SAMPLE_SIZE;  // Update sample index circularly
  if (sampleIndex == 0) {
    firstSequence = false;  // First sequence completed
  }
}

void FlowSensor::setAvgFrequency(void) {
  int range = firstSequence ? sampleIndex : SAMPLE_SIZE;  // Use the current sample count if in the first sequence
  avgFrequency = 0;

  for (int i = 0; i < range; ++i) {
    avgFrequency += samples[i];
  }
  avgFrequency /= range;
}

void FlowSensor::reset(void) {
  pulseCount = 0;
  lastPulseCount = 0;
  frequency = 0.0;
  memset(samples, 0, sizeof(samples));
  sampleIndex = 0;
  avgFrequency = 0;
  firstSequence = true;
}

float FlowSensor::getInstantFrequency(void) const {
  return frequency;
}

float FlowSensor::getAvgFrequency(void) const {
  return avgFrequency;
}

int FlowSensor::getPulseCount(void) const {
  return pulseCount;
}

void IRAM_ATTR FlowSensor::pulseCounter() {
  if (instance) {                                     // Check if the instance pointer is valid
    portENTER_CRITICAL_ISR(&instance->interruptMux);  // Enter critical section to protect shared variables
    instance->pulseCount++;
    portEXIT_CRITICAL_ISR(&instance->interruptMux);
  }
}