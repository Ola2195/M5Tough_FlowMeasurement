#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>
#include <M5Unified.h>

class TouchButton {
  public:
    TouchButton(const String& label,
                int x, int y, int width, int height,
                uint16_t color = TFT_WHITE, uint16_t textColor = TFT_BLACK);

    void draw();
    bool isPressed(int touchX, int touchY) const;
    bool wasJustPressed(int touchX, int touchY);

    String getLabel() const;
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;

  private:
    String _label;
    int _x, _y, _width, _height;
    uint16_t _color, _textColor;

    bool _wasPreviouslyPressed = false; 
};

#endif // TOUCHBUTTON_H