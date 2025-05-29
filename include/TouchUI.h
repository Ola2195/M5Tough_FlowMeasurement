#ifndef TOUCHUI_H
#define TOUCHUI_H

#include <Arduino.h>
#include <map>
#include "TouchButton.h"

class TouchUI {
  public:
    void addButton(const String& id, const TouchButton& button);
    void drawButtons();
    String getJustPressed();

    void update();

  private:
    std::map<String, TouchButton> buttons;
};

#endif // TOUCHUI_H