#include "DisplayRenderer.h"

DisplayRenderer::DisplayRenderer(int displayWidth, int displayHeight)
  : _displayWidth(displayWidth), _displayHeight(displayHeight) {
}

//displayMoreDetails
void DisplayRenderer::renderMeasurements(float frequency, float avgFrequency) {
  String line;
  int textSize;

  // Instant frequency
  textSize = 2;
  line = "INSTANT " + String(frequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("INSTANT %.2f Hz%*s\n\n", frequency, autoPadSpaces(line, textSize), " ");

  // Average frequency
  textSize = 3;
  line = String(avgFrequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.printf("%.2f Hz%*s\n\n", avgFrequency, autoPadSpaces(line, textSize), " ");
}

void DisplayRenderer::renderSensorDetails(int sensorId, int timeCount, int pulseCount) {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("Sensor %d:\n", sensorId + 1);
  M5.Lcd.printf("Time: %i ms\n", timeCount * 100);
  M5.Lcd.printf("Pulses: %i\n\n\n", pulseCount);
}

void DisplayRenderer::drawDividingLine() {
  M5.Lcd.drawFastHLine(0, _displayHeight / 3 - 10, _displayWidth, TFT_WHITE);
}

void DisplayRenderer::clearAbove(int yLimit) {
  M5.Lcd.fillRect(0, 0, _displayWidth, yLimit, BLACK);
}

int DisplayRenderer::autoPadSpaces(const String& text, int textSize) {
  int charWidth = 6 * textSize;
  int textPixelWidth = text.length() * charWidth;
  int remainingPixels = _displayWidth - textPixelWidth;
  if (remainingPixels <= 0)
    return 0;
  return remainingPixels / charWidth;
}