#include "include/M5ToughDisplay.h"
#include <M5Unified.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

M5ToughDisplay::M5ToughDisplay(void)
  : margin(20),
    resetButton("RESET", margin, DISPLAY_HEIGHT- 40 - margin, DISPLAY_WIDTH - 2 * margin, 40) {
  ui.addButton("RESET", resetButton);
}

void M5ToughDisplay::startDrawing(void) {
  //auto cfg = M5.config();
  //cfg.internal_rtc = true;
  //M5.begin(cfg);
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
}

void M5ToughDisplay::drawButtons(void) {
  ui.drawButtons();
}


M5ToughDisplay::PressedStatus_t M5ToughDisplay::isPressed(void) {
  ui.update();
  String results = ui.getJustPressed();
  if (results=="RESET") {
    return RESET_BUTTON;
  } 
  return NONE;
}

void M5ToughDisplay::firstDisplaying(void) {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);
}

void M5ToughDisplay::displayMoreDetails(int sensorId, int timeCount, int pulseCount) {
  renderer.renderSensorDetails(sensorId, timeCount, pulseCount);
}

void M5ToughDisplay::displayMeasurements(float frequency, float avgFrequency) {
  renderer.renderMeasurements(frequency, avgFrequency);
}

void M5ToughDisplay::displayDividingLine(void) {
  renderer.drawDividingLine(renderer.getDisplayHeight() / 3 - 10);
}

void M5ToughDisplay::clearScreen(void) {
  renderer.clearRegion(0, resetButton.getY());
}