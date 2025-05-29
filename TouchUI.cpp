#include "TouchUI.h"
#include <M5Unified.h>

void TouchUI::addButton(const String& id, const TouchButton& button) {
  buttons.emplace(id, button);
}

void TouchUI::drawButtons() {
  for (auto& pair : buttons) {
    pair.second.draw();
  }
}

String TouchUI::getJustPressed() {
  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail();
    for (auto& pair : buttons) {
      if (pair.second.wasJustPressed(detail.x, detail.y)) {
        return pair.first;
      }
    }
  } else {
    for (auto& pair : buttons) {
      pair.second.wasJustPressed(-1, -1);
    }
  }
  return "";
}

void TouchUI::update() {
  M5.update();
}