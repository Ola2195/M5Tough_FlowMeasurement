#ifndef VIEW_H
#define VIEW_H

#include "DisplayRenderer.h"
#include "FlowManager.h"
#include "TouchButton.h"
#include "TouchUI.h"

class BaseView {
  public:
    virtual void render() = 0;
    virtual void update() {};
    virtual ~BaseView() = default;
};

class MainMeasurementView : public BaseView {
  public:
    MainMeasurementView(FlowManager& manager);
    void render() override;
    void update() override;

  private:
    int margin;  

    FlowManager& _manager;

    TouchButton resetButton;
    TouchUI ui;
    DisplayRenderer _renderer;
};

#endif // VIEW_H
