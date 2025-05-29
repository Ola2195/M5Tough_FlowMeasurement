#include "M5ToughDisplay.h"
#include <M5Unified.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

M5ToughDisplay::M5ToughDisplay(void)
  : margin(20),
    resetButton("RESET", margin, DISPLAY_HEIGHT- 40 - margin, DISPLAY_WIDTH - 2 * margin, 40) {}

void M5ToughDisplay::startDrawing(void) {
  //auto cfg = M5.config();
  //cfg.internal_rtc = true;
  //M5.begin(cfg);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
}

void M5ToughDisplay::drawResetButton(void) {
  resetButton.draw();
}


M5ToughDisplay::PressedStatus_t M5ToughDisplay::isPressed(void) {
  M5.update();
  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail();
    if (resetButton.wasJustPressed(detail.x, detail.y)) {
      return RESET_BUTTON;
    }
  } else {
    resetButton.wasJustPressed(-1, -1);
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
  String line;
  int textSize;

  textSize = 2;
  line = "INSTANT " + String(frequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.printf("INSTANT %.2f Hz%*s\n\n", frequency, autoPadSpaces(line, textSize), " ");

  textSize = 3;
  line = String(avgFrequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.printf("%.2f Hz%*s\n\n", avgFrequency, autoPadSpaces(line, textSize), " ");
}

void M5ToughDisplay::displayDividingLine(void) {
  M5.Lcd.drawFastHLine(0, DISPLAY_HEIGHT / 3 - 10, DISPLAY_WIDTH, TFT_WHITE);
}

int M5ToughDisplay::autoPadSpaces(const String& text, int textSize) {
  int charWidth = 6 * textSize;
  int textPixelWidth = text.length() * charWidth;
  int remainingPixels = DISPLAY_WIDTH - textPixelWidth;
  if (remainingPixels <= 0)
    return 0;
  return remainingPixels / charWidth;
}

void M5ToughDisplay::clearScreen(void) {
  M5.Lcd.fillRect(0, 0, DISPLAY_WIDTH, resetButton.getY(), BLACK);
}