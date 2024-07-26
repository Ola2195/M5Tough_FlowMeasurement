#ifndef M5TOUGHDISPLAY_H
#define M5TOUGHDISPLAY_H

/*
 * @brief     Class to manage the M5Tough display functionality.
 * @details   This class handles drawing on the display, including showing measurements and reset buttons.
 */
class M5ToughDisplay {
  public:
    typedef enum {
      NONE,           // No button pressed
      RESET_BUTTON    // Reset button pressed
    } PressedStatus_t;

    /*
     * @brief   Constructor for M5ToughDisplay.
     */
    M5ToughDisplay(void);

    /*
     * @brief   Initializes the display.
     */
    void startDrawing(void);

    /*
     * @brief   Draws the reset button on the display.
     */
    void drawResetButton(void);

    /*
     * @brief   Checks which button is pressed on the display.
     * @retval  Status of the pressed button.
     */
    PressedStatus_t isPressed(void);

    /*
     * @brief   Prepares the display for initial content display.
     */
    void firstDisplaying(void);

    /*
     * @brief   Displays detailed information about a sensor.
     * @param   sensorId    ID of the sensor.
     * @param   timeCount   Time count in milliseconds.
     * @param   pulseCount  Total pulse count.
     */
    void displayMoreDetails(int sensorId, int timeCount, int pulseCount);

    /*
     * @brief   Displays frequency measurements on the screen.
     * @param   frequency     Instantaneous frequency.
     * @param   avgFrequency  Average frequency.
     */
    void displayMeasurements(float frequency, float avgFrequency);

    /*
     * @brief   Draws a dividing line on the display.
     */
    void displayDividingLine(void);

    /*
     * @brief   Clears the display screen.
     */
    void clearScreen(void);

  private:
    int margin;               // Margin for positioning elements
    int resetButtonHeight;    // Height of the reset button
    int resetButtonWidth;     // Width of the reset button
    int resetButtonPositionX; // X position of the reset button
    int resetButtonPositionY; // Y position of the reset button

    /*
     * @brief   Checks if the reset button is pressed.
     * @param   x   X coordinate of the touch.
     * @param   y   Y coordinate of the touch.
     * @retval  True if the reset button is pressed, false otherwise.
     */
    bool isPressedResetButton(int x, int y);
};

#endif // M5TOUGHDISPLAY_H