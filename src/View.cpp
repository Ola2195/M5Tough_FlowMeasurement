#include "include/View.h"

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGHT 240

MainMeasurementView::MainMeasurementView(FlowManager& manager)
  : _manager(manager), _margin(20),
    _resetButton("RESET", _margin, DISPLAY_HEIGHT- 40 - _margin, DISPLAY_WIDTH - 2 * _margin, 40) {}

void MainMeasurementView::setup() {
  M5.Lcd.fillScreen(BLACK);
  _ui.addButton("RESET", _resetButton);
  _ui.drawButtons();
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

  _renderer.drawDividingLine(_renderer.getDisplayHeight() / 3 - 10);
}

void MainMeasurementView::update() {
  _ui.update();
  if (_ui.getJustPressed() == "RESET") {
    _manager.reset();
    _renderer.clearRegion(0, _resetButton.getY());
  } 
}