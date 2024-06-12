#include <Arduino.h>
#include <M5Unified.h>

#define DISPLAY_WIDTH   320
#define DISPLAY_HEIGH   240

#define SENSOR_PIN    2     // Pin z przepływomierzem

hw_timer_t *timer = NULL;
const int sensortPin = SENSOR_PIN;
portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;

volatile int timeCount = 0;
volatile int pulseCount = 0;
volatile float frequency = 0.0;

volatile float clearScreen = false;

/*
 * Funkcja przerwania timera
 */
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&interruptMux);  // zabezpieczenie współdzielonych zmiennych
  timeCount++;
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

void reset() {
  if(timeCount!=0)
    M5.Lcd.fillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGH-40-20, BLACK);
  timeCount = 0;
  pulseCount = 0;
  frequency = 0.0;
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
  
  // Rysowanie przycisku resetu na ekranie
  M5.Lcd.fillRect(20, DISPLAY_HEIGH-40-20, DISPLAY_WIDTH-40, 40, TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setCursor((DISPLAY_WIDTH)/2-50, DISPLAY_HEIGH-40-10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("RESET");
}

void loop() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);

  char buffer[20];
  
  snprintf(buffer, sizeof(buffer), "Time: %i sec", timeCount);
  M5.Lcd.println(buffer);
  
  snprintf(buffer, sizeof(buffer), "Pulses: %i\n", pulseCount);
  M5.Lcd.println(buffer);

  portENTER_CRITICAL(&interruptMux);
  if (timeCount > 0) {
    frequency = pulseCount / (float)timeCount;
  }
  portEXIT_CRITICAL(&interruptMux);

  M5.Lcd.setTextSize(5);
  snprintf(buffer, sizeof(buffer), "%.2f Hz", frequency);
  M5.Lcd.println(buffer);

  // Sprawdzenie dotknięcia ekranu
  M5.update();
  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail();
    int x = detail.x;
    int y = detail.y;
    if (x >= 20 && x <= DISPLAY_WIDTH-20 && y >= DISPLAY_HEIGH-40-20 && y <= DISPLAY_HEIGH-20) {
      reset();
    }
  }
}
