#include "include/DisplayRenderer.h"

DisplayRenderer::DisplayRenderer(int displayWidth, int displayHeight)
  : _displayWidth(displayWidth), _displayHeight(displayHeight) {
}

void DisplayRenderer::renderMeasurements(float frequency, float avgFrequency, float rateLPM) {
  String line;
  int textSize;

  // Instant frequency
  textSize = 2;
  line = "INSTANT " + String(frequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("INSTANT %.2f Hz%*s\n", frequency, autoPadSpaces(line, textSize), " ");

  // Average frequency
  textSize = 2;
  line = "AVG " + String(avgFrequency, textSize) + " Hz";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.printf("AVG %.2f Hz%*s\n\n", avgFrequency, autoPadSpaces(line, textSize), " ");

  // Liters per minute
  textSize = 3;
  line = String(rateLPM, textSize) + " L/min";
  M5.Lcd.setTextSize(textSize);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("%.2f L/min%*s\n\n", rateLPM, autoPadSpaces(line, textSize), " ");
}

void DisplayRenderer::renderSensorDetails(int sensorId, int timeCount, int pulseCount) {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.printf("Sensor %d:\n", sensorId + 1);
  M5.Lcd.printf("Time: %i ms\n", timeCount * 100);
  M5.Lcd.printf("Pulses: %i\n\n\n", pulseCount);
}

void DisplayRenderer::renderSensorDetails(int sensorId, float frequency, float avgFrequency, int totalPulse, float totalLiters, float rateLPM) {
  M5.Lcd.setTextColor(WHITE, BLACK);
  
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Sensor %d:\n\n", sensorId + 1);

  int textSize = 2;
  M5.Lcd.setTextSize(textSize);
  
  String lineInstant = "Instant: " + String(frequency, textSize) + " Hz";
  String lineAverage = "Average: " + String(avgFrequency, textSize) + " Hz";
  String linePulsese = "Total Pulse: " + String(totalPulse, textSize);
  String lineLiters = "Total Liters: " + String(totalLiters, textSize) + " L";
  String lineLPM = "Total Liters: " + String(rateLPM, textSize) + " L";
  
  M5.Lcd.printf("Instant: %.2f Hz%*s\n\n", frequency, autoPadSpaces(lineInstant, textSize), " ");
  M5.Lcd.printf("Average: %.2f Hz%*s\n\n", avgFrequency, autoPadSpaces(lineAverage, textSize), " ");
  M5.Lcd.printf("Total Pulse: %d%*s\n\n", totalPulse, autoPadSpaces(linePulsese, textSize), " ");
  M5.Lcd.printf("Total Liters: %.2f L%*s\n\n", totalLiters, autoPadSpaces(lineLiters, textSize), " ");
  M5.Lcd.printf("%.2f L/min%*s\n\n", rateLPM, autoPadSpaces(lineLPM, textSize), " ");
}

void DisplayRenderer::drawDividingLine(int y) {
  if (y < 0 || y >= _displayHeight) return;
  M5.Lcd.drawFastHLine(0, y, _displayWidth, TFT_WHITE);
}

void DisplayRenderer::clearRegion(int yStart, int yEnd) {
  if (yEnd <= yStart) return;
  M5.Lcd.fillRect(0, yStart, _displayWidth, yEnd - yStart, BLACK);
}

int DisplayRenderer::getDisplayWidth() const {
  return _displayWidth;
}

int DisplayRenderer::getDisplayHeight() const {
  return _displayHeight;
}

int DisplayRenderer::autoPadSpaces(const String& text, int textSize) {
  int charWidth = 6 * textSize;
  int textPixelWidth = text.length() * charWidth;
  int remainingPixels = _displayWidth - textPixelWidth;
  if (remainingPixels <= 0)
    return 0;
  return remainingPixels / charWidth;
}