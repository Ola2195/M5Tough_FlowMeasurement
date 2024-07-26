#include "M5ToughDisplay.h"
#include <M5Unified.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

M5ToughDisplay::M5ToughDisplay(void)
  : margin(20), resetButtonHeight(40) {
  resetButtonWidth = DISPLAY_WIDTH - 2 * margin;
  resetButtonPositionX = margin;
  resetButtonPositionY = DISPLAY_HEIGHT - resetButtonHeight - margin;
}

void M5ToughDisplay::startDrawing(void) {
  M5.begin();
}

void M5ToughDisplay::drawResetButton(void) {
  M5.Lcd.fillRect(resetButtonPositionX, resetButtonPositionY, resetButtonWidth, resetButtonHeight, TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setCursor(resetButtonWidth / 2 - resetButtonPositionX, resetButtonPositionY + 10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("RESET");
}

M5ToughDisplay::PressedStatus_t M5ToughDisplay::isPressed(void) {
  M5.update();
  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail();
    if (isPressedResetButton(detail.x, detail.y)) {
      return RESET_BUTTON;
    }
  }
  return NONE;
}

void M5ToughDisplay::firstDisplaying(void) {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);
}

void M5ToughDisplay::displayMoreDetails(int sensorId, int timeCount, int pulseCount) {
  M5.Lcd.printf("Sensor %d:\n", sensorId + 1);
  M5.Lcd.printf("Time: %i ms\n", timeCount * 100);
  M5.Lcd.printf("Pulses: %i\n\n\n", pulseCount);
}

void M5ToughDisplay::displayMeasurements(float frequency, float avgFrequency) {
  M5.Lcd.setTextSize(2);
  M5.Lcd.printf("INSTANT %.2f Hz\n\n", frequency);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("%.2f Hz\n\n", avgFrequency);
}

void M5ToughDisplay::displayDividingLine(void) {
  M5.Lcd.drawFastHLine(0, DISPLAY_HEIGHT / 3 - 10, DISPLAY_WIDTH, TFT_WHITE);
}

void M5ToughDisplay::clearScreen(void) {
  M5.Lcd.fillRect(0, 0, DISPLAY_WIDTH, resetButtonPositionY, BLACK);
}

bool M5ToughDisplay::isPressedResetButton(int x, int y) {
  return (x >= resetButtonPositionX && x <= resetButtonWidth + resetButtonPositionX && y >= resetButtonPositionY && y <= resetButtonPositionY + resetButtonHeight);
}