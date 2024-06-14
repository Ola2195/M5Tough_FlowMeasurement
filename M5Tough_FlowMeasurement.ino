#include <Arduino.h>
#include <M5Unified.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGH 240

#define SENSOR_PIN    2  // Pin z przepływomierzem
#define SUMPLES_SIZE  10  // Liczba próbek do uśredniania

hw_timer_t *timer = NULL;
const int sensortPin = SENSOR_PIN;
portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;

volatile bool measurementFlag = false;
volatile int timeCount = 0;
volatile int pulseCount = 0;
volatile int lastPulseCount = 0;
volatile float frequency = 0.0;

// Parametry filtra
float samples[SUMPLES_SIZE] = { 0 };
volatile int sampleIndex = 0;
volatile float avgFrequency = 0.0;
volatile bool firstMeasurement = true;
volatile bool firstSequence = true;

/*
 * Funkcja przerwania timera
 */
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&interruptMux);  // zabezpieczenie współdzielonych zmiennych
  timeCount++;
  if (timeCount == 10) {
    lastPulseCount = pulseCount;
    pulseCount = 0;
    timeCount = 0;
    measurementFlag = true;
  }
  portEXIT_CRITICAL_ISR(&interruptMux);
}

/*
 * Funkcja przerwania GPIO
 */
void IRAM_ATTR pulseCounter() {
  portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
  pulseCount++;
  portEXIT_CRITICAL_ISR(&interruptMux);
}

/*
 * Funkcja resetu, wywoływana przez naciśnięcie przycisku resetu
 */
void reset() {
  // Wyłącz przerwania na czas resetu
  timerAlarmDisable(timer);
  detachInterrupt(digitalPinToInterrupt(sensortPin));

  if (timeCount != 0)
    M5.Lcd.fillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGH - 40 - 20, BLACK);

  memset(samples, 0, sizeof(samples));
  firstSequence = true;
  firstMeasurement = true;

  sampleIndex = 0;
  frequency = 0.0;

  portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
  timeCount = 0;
  pulseCount = 0;
  measurementFlag = false;
  portEXIT_CRITICAL_ISR(&interruptMux);

  // Włącz przerwania po zakończeniu resetu
  timerAlarmEnable(timer);
  attachInterrupt(digitalPinToInterrupt(sensortPin), pulseCounter, FALLING);
}

/*
 * Konfiguracja początkowa
 */
void setup() {
  M5.begin();
  // Konfiguracja timera
  timer = timerBegin(0, 80, true);              // timer 0, preskaler 80 (dla 1MHz)
  timerAttachInterrupt(timer, &onTimer, true);  // obsługa przerwania
  timerAlarmWrite(timer, 100000, true);         // 100 ms = 100000 us
  timerAlarmEnable(timer);

  // Konfiguracja GPIO
  pinMode(sensortPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensortPin), pulseCounter, FALLING);

  // Rysowanie przycisku resetu na ekranie
  M5.Lcd.fillRect(20, DISPLAY_HEIGH - 40 - 20, DISPLAY_WIDTH - 40, 40, TFT_WHITE);
  M5.Lcd.setTextColor(TFT_BLACK);
  M5.Lcd.setCursor((DISPLAY_WIDTH) / 2 - 50, DISPLAY_HEIGH - 40 - 10);
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("RESET");
}

/*
 * Główna pętla
 */
void loop() {
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);

  if (measurementFlag) {
    portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
    measurementFlag = false;
    frequency = lastPulseCount / 1;
    portEXIT_CRITICAL_ISR(&interruptMux);

    if (!firstMeasurement) {
      // Aktualizacja próbek
      samples[sampleIndex] = frequency;
      if (sampleIndex + 1 == SUMPLES_SIZE)
        firstSequence = false;
      sampleIndex = (sampleIndex + 1) % SUMPLES_SIZE;

      // Obliczanie średniej
      int range = 0;
      avgFrequency = 0;
      if (firstSequence)
        range = sampleIndex;
      else
        range = SUMPLES_SIZE;
      for (int i = 0; i < range; i++) {
        avgFrequency += samples[i];
      }
      avgFrequency /= range;
    }
    firstMeasurement = false;
  }

  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);

  char buffer[40];

  snprintf(buffer, sizeof(buffer), "Time: %i ms", timeCount * 100);
  M5.Lcd.println(buffer);

  snprintf(buffer, sizeof(buffer), "Pulses: %i\n", pulseCount);
  M5.Lcd.println(buffer);

  M5.Lcd.setTextSize(3);
  snprintf(buffer, sizeof(buffer), "A 1s  %.2f Hz", avgFrequency);
  M5.Lcd.println(buffer);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("\nAVERAGE OF THE LAST 10");

  M5.Lcd.setTextSize(3);
  snprintf(buffer, sizeof(buffer), "I 1s  %.2f Hz", frequency);
  M5.Lcd.println(buffer);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("\nINSTANT MEASUREMENT");

  // Sprawdzenie dotknięcia ekranu
  M5.update();
  if (M5.Touch.getCount() > 0) {
    auto detail = M5.Touch.getDetail();
    int x = detail.x;
    int y = detail.y;
    if (x >= 20 && x <= DISPLAY_WIDTH - 20 && y >= DISPLAY_HEIGH - 40 - 20 && y <= DISPLAY_HEIGH - 20) {
      reset();
    }
  }
}
