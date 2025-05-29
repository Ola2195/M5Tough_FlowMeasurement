#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <Arduino.h>
#include <M5Unified.h>

class DisplayRenderer {
  public:
    DisplayRenderer(int displayWidth = 320, int displayHeight = 240);

    void renderMeasurements(float frequency, float avgFrequency);
    void renderSensorDetails(int sensorId, int timeCount, int pulseCount);

    void drawDividingLine(int y);

    void clearRegion(int yStart, int yEnd);

    int getDisplayWidth() const;
    int getDisplayHeight() const;

  private:
    int _displayWidth;
    int _displayHeight;

    int autoPadSpaces(const String& text, int textSize);
};

#endif // DISPLAYRENDERER_H