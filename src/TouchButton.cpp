#include "include/TouchButton.h"

#include <M5Unified.h>

TouchButton::TouchButton(const String& label, int x, int y, int width, int height, uint16_t color, uint16_t textColor)
  : _label(label), _x(x), _y(y), _width(width), _height(height), _color(color), _textColor(textColor),
    _wasPreviouslyPressed(false) {}

void TouchButton::draw() {
  M5.Lcd.fillRect(_x, _y, _width, _height, _color);
  M5.Lcd.setTextColor(_textColor);
  M5.Lcd.setTextSize(3);
  int textX = _x + (_width - _label.length() * 18) / 2;
  int textY = _y + (_height - 24) / 2;
  M5.Lcd.setCursor(textX, textY);
  M5.Lcd.print(_label);
}

bool TouchButton::isPressed(int touchX, int touchY) const {
  return (touchX >= _x && touchX <= _x + _width && touchY >= _y && touchY <= _y + _height);
}

bool TouchButton::wasJustPressed(int touchX, int touchY) {
  bool currentlyPressed = isPressed(touchX, touchY);
  bool justPressed = currentlyPressed && !_wasPreviouslyPressed;
  _wasPreviouslyPressed = currentlyPressed;
  return justPressed;
}

String TouchButton::getLabel() const {
  return _label;
}

int TouchButton::getX() const {
  return _x;
}

int TouchButton::getY() const {
  return _y;
}

int TouchButton::getWidth() const {
  return _width;
}

int TouchButton::getHeight() const {
  return _height;
}
