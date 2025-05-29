#ifndef FLOWSENSOR_H
#define FLOWSENSOR_H

#include <Arduino.h>

#define SAMPLE_SIZE  10   // Number of samples for averaging

/*
 * @brief     Class representing a flow sensor.
 * @details   This class manages flow sensor functionality including pulse counting and frequency calculation.
 */
class FlowSensor {
  public:
    /*
     * @brief   Constructor for FlowSensor.
     * @param   pin   The pin number connected to the flow sensor.
     */
    FlowSensor(int pin);

    /*
     * @brief   Initializes the flow sensor.
     */
    void setupFlowSensor(void);

    /*
     * @brief   Attaches the interrupt to count sensor pulses.
     */
    void attachSensorInterrupt(void);

    /*
     * @brief   Detaches the interrupt to stop counting sensor pulses.
     */
    void detachSensorInterrupt(void);

    /*
     * @brief   Updates the pulse count from the interrupt.
     */
    void updatePulseCount(void);

    /*
     * @brief   Calculates the frequency based on pulse count.
     */
    void calculateFrequency(void);

    /*
     * @brief   Updates the samples array with the current frequency.
     */
    void updateSamples(void);

    /*
     * @brief   Calculates the average frequency from the samples.
     */
    void setAvgFrequency(void);

    /*
     * @brief   Resets the flow sensor, clearing counts and samples.
     */
    void reset(void);

    /*
     * @brief   Gets the current instant frequency.
     * @retval  Current frequency in Hz.
     */
    float getInstantFrequency(void) const;

    /*
     * @brief   Gets the average frequency.
     * @retval  Average frequency in Hz.
     */
    float getAvgFrequency(void) const;

    /*
     * @brief   Gets the total pulse count.
     * @retval  Total pulse count.
     */
    int getPulseCount(void) const;

  private:
    int pin_;                     // Pin connected to the flow sensor
    volatile int pulseCount;      // Number of pulses counted
    volatile int lastPulseCount;  // Last pulse count for frequency calculation
    volatile float frequency;     // Instantaneous frequency

    float samples[SAMPLE_SIZE];   // Array of samples for averaging
    volatile int sampleIndex;     // Index for the samples array
    volatile float avgFrequency;  // Average frequency from samples
    volatile bool firstSequence;  // Flag indicating the first measurement sequence

    portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;   // Critical section for interrupt protection

    static FlowSensor* instance;    // Static instance pointer for interrupt handling

    /*
     * @brief   Interrupt service routine for counting pulses.
     */
    static void IRAM_ATTR pulseCounter(void);

};

