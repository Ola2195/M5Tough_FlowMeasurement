#include <M5Unified.h>
#include <Arduino.h>

#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGH   240

hw_timer_t *timer = NULL;
const int sensortPin = 36;  // Pin z przepływomierzem
portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;

const double calibration = 1.0;

volatile int timeCount = 0;
volatile int pulseCount = 0;
volatile float flowRate = 0;

volatile bool cleraScreen = false;

/*
 * Funkcja przerwania timera
 */
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&interruptMux);  // zabezpieczenie współdzielonych zmiennych
  timeCount++;
  if(timeCount == 60) {
    flowRate = pulseCount * calibration; 
    pulseCount = 0;
    timeCount = 0;
    cleraScreen = true;
  }
  portEXIT_CRITICAL_ISR(&interruptMux);
}

/*
 * Funkcja przerwania GPIO
 */
void IRAM_ATTR pulseCounter() {
  portENTER_CRITICAL_ISR(&interruptMux);  // zabezpieczenie współdzielonych zmiennych
  pulseCount++;
  portEXIT_CRITICAL_ISR(&interruptMux);
}

void setup() {
  M5.begin();
  // Konfiguracja timera
  timer = timerBegin(0, 80, true);  // timer 0, preskaler 80 (dla 1MHz)
  timerAttachInterrupt(timer, &onTimer, true);  // obsługa przerwania
  timerAlarmWrite(timer, 1000000, true); // 1 s = 1000000 us
  timerAlarmEnable(timer);

  // Konfiguracja GPIO
  pinMode(sensortPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensortPin), pulseCounter, FALLING);  
}

void loop() {
  if(cleraScreen) {
    M5.Lcd.clear(BLACK);
    cleraScreen = false;
  }

  char buffer[20];
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextSize(3);

  snprintf(buffer, sizeof(buffer), "Time: %i%i sec", timeCount/10, timeCount%10);
  M5.Lcd.println(buffer);
  
  snprintf(buffer, sizeof(buffer), "Flow: %i L\n\r", pulseCount);
  M5.Lcd.println(buffer);

  M5.Lcd.setTextSize(3);
  //M5.Lcd.println("Flow Rate");
  M5.Lcd.drawCentreString("Flow Rate", 160, 80, &fonts::Font0);
  
  M5.Lcd.setTextSize(10);
  snprintf(buffer, sizeof(buffer), "%.2f", flowRate);
  //M5.Lcd.println(buffer);
  M5.Lcd.drawCentreString(buffer, 160, 130, &fonts::Font0);

  M5.Lcd.setTextSize(3);
  //M5.Lcd.println("L/min");
  M5.Lcd.drawCentreString("L/min", 160, 200, &fonts::Font0);
}
