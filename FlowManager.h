#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H

#include <Arduino.h>
#include "FlowSensor.h"

/*
 * @brief     Class to manage multiple flow sensors and handle timing.
 * @details   This class sets up timers and manages the measurement and reset processes.
 */
class FlowManager {
  public:
    /*
     * @brief   Constructor for FlowManager.
     */
    FlowManager(void);

    /*
     * @brief   Destructor for FlowManager.
     */
    ~FlowManager(void);

    /*
     * @brief   Sets up the timer for periodic measurements.
     */
    void setupTimer(void);

    /*
     * @brief   Initializes the flow sensors.
     */
    void setupFlowSensors(void);

    /*
     * @brief   Processes the measurements from the flow sensors.
     */
    void measurementsProcessing(void);

    /*
     * @brief   Resets all flow sensors and internal state.
     */
    void reset(void);

    /*
     * @brief   Gets the pointer to a flow sensor by index.
     * @param   index   The index of the sensor.
     * @retval  Pointer to the FlowSensor object at the specified index.
     */
    FlowSensor* getSensor(size_t index) const;

    /*
     * @brief   Gets the number of flow sensors.
     * @retval  Number of flow sensors.
     */
    size_t getNumSensors(void) const;

    /*
     * @brief   Gets the current time count.
     * @retval  Current time count.
     */
    int getTimeCount(void) const;

    volatile bool measurementFlag;  // Flag indicating if measurements should be processed

  private:
    /*
     * @brief   Timer interrupt service routine.
     */
    static void IRAM_ATTR onTimer(void);

    portMUX_TYPE interruptManagerMux = portMUX_INITIALIZER_UNLOCKED;  // Critical section for timer interrupt protection

    hw_timer_t *timer;        // Timer object
    volatile int timeCount;   // Time count for measurement intervals

    static FlowManager* instance;  // Static instance pointer for interrupt handling

    FlowSensor** sensors;   // Array of flow sensor pointers
    size_t numSensors;      // Number of flow sensors

    volatile bool firstMeasurement;  // Flag indicating the first measurement sequence
};

