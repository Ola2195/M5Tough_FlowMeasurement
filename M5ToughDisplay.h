#ifndef M5TOUGHDISPLAY_H
#define M5TOUGHDISPLAY_H

#include <Arduino.h>
#include "TouchButton.h"

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

    TouchButton resetButton;

    /*
     * @brief   Checks if the reset button is pressed.
     * @param   x   X coordinate of the touch.
     * @param   y   Y coordinate of the touch.
     * @retval  True if the reset button is pressed, false otherwise.
     */
    bool isPressedResetButton(int x, int y);

    /**
     * @brief   Calculates how many extra spaces are needed to fully overwrite a previous line of text.
     * @param   text      The current line of text to be displayed.
     * @param   textSize  The text size used (as in setTextSize).
     * @retval  Number of additional spaces to pad at the end of the string.
     *
     * The function estimates text width based on character count and text size.
     */
    int autoPadSpaces(const String& text, int textSize);
};

#endif // M5TOUGHDISPLAY_H