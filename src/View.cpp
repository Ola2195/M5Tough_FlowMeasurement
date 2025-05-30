#include "include/View.h"

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

MainMeasurementView::MainMeasurementView(FlowManager& manager)
  : _manager(manager), margin(20),
    resetButton("RESET", margin, DISPLAY_HEIGHT- 40 - margin, DISPLAY_WIDTH - 2 * margin, 40) {
  M5.begin();
  M5.Lcd.fillScreen(BLACK);

  ui.addButton("RESET", resetButton);
  ui.drawButtons();
}

void MainMeasurementView::render() {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setTextSize(2);

  for (size_t i = 0; i < _manager.getNumSensors(); ++i) {
    FlowSensor* sensor = _manager.getSensor(i);
    if (sensor) {
      _renderer.renderMeasurements(sensor->getInstantFrequency(), sensor->getAvgFrequency());
    }
  }

  _renderer.drawDividingLine(_renderer.getDisplayHeight() / 3 - 10);;
}

void MainMeasurementView::update() {
  ui.update();
  if (ui.getJustPressed() == "RESET") {
    _manager.reset();        // Reset the flow manager
    _renderer.clearRegion(0, resetButton.getY());
  } 
}