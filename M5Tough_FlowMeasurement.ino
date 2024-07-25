#include <Arduino.h>
#include <M5Unified.h>

#define DISPLAY_WIDTH 320
#define DISPLAY_HEIGH 240

#define NUM_SENSORS   2   // Liczba przepływomierzy
#define SUMPLES_SIZE  10  // Liczba próbek do uśredniania

#define SENSOR_PIN_1    2   // Pin z przepływomierzem
#define SENSOR_PIN_2    36  // Pin z przepływomierzem


// Definicje timera i zmiennych synchronizacyjnych
hw_timer_t *timer = NULL;
portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;
volatile bool measurementFlag = false;
volatile int timeCount = 0;

// Struktura przechowująca dane przepływomierza
struct FlowSensor {
  int pin;
  volatile int pulseCount;
  volatile int lastPulseCount;
  volatile float frequency;

  float samples[SUMPLES_SIZE];
  volatile int sampleIndex;
  volatile float avgFrequency;
  volatile bool firstMeasurement;
  volatile bool firstSequence;
};

// Tablica przepływomierzy
FlowSensor sensors[NUM_SENSORS] = {
  { SENSOR_PIN_1, 0, 0, 0.0, {0}, 0, 0.0, true, true },
  { SENSOR_PIN_2, 0, 0, 0.0, {0}, 0, 0.0, true, true }
};


/*
 * Funkcja przerwania timera
 */
void IRAM_ATTR onTimer() {
  portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
  timeCount++;
  if (timeCount == 10) {
    for (int i = 0; i < NUM_SENSORS; i++) {
      sensors[i].lastPulseCount = sensors[i].pulseCount;
      sensors[i].pulseCount = 0;
    }
    timeCount = 0;
    measurementFlag = true;
  }
  portEXIT_CRITICAL_ISR(&interruptMux);
}

/*
 * Funkcje przerwań GPIO
 */
void IRAM_ATTR pulseCounter0() {
  portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
  sensors[0].pulseCount++;
  portEXIT_CRITICAL_ISR(&interruptMux);
}

void IRAM_ATTR pulseCounter1() {
  portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
  sensors[1].pulseCount++;
  portEXIT_CRITICAL_ISR(&interruptMux);
}

/*
 * Funkcja resetu, wywoływana przez naciśnięcie przycisku resetu
 */
void reset() {
  // Wyłącz przerwania na czas resetu
  timerAlarmDisable(timer);
  for (int i = 0; i < NUM_SENSORS; i++) {
    detachInterrupt(digitalPinToInterrupt(sensors[i].pin));
  }

  if (timeCount != 0) {
    M5.Lcd.fillRect(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGH - 40 - 20, BLACK);
  }

  for (int i = 0; i < NUM_SENSORS; i++) {
    FlowSensor &sensor = sensors[i]; // Odwołanie do aktualnego przepływomierza
    memset(sensor.samples, 0, sizeof(sensor.samples));
    sensor.firstSequence = true;
    sensor.firstMeasurement = true;
    sensor.avgFrequency = 0;
    sensor.sampleIndex = 0;
    sensor.frequency = 0.0;

    portENTER_CRITICAL_ISR(&interruptMux); // Zabezpieczenie współdzielonych zmiennych
    timeCount = 0;
    sensor.pulseCount = 0;
    sensor.lastPulseCount = 0;
    measurementFlag = false;
    portEXIT_CRITICAL_ISR(&interruptMux);
  }

  // Włącz przerwania po zakończeniu resetu
  timerAlarmEnable(timer);
  attachInterrupt(digitalPinToInterrupt(sensors[0].pin), pulseCounter0, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensors[1].pin), pulseCounter1, FALLING);
}

/*
 * Konfiguracja początkowa
 */
void setup() {
  M5.begin();

  Serial.begin(115200); // Inicjalizacja portu szeregowego z prędkością 115200 baud

  // Konfiguracja timera
  timer = timerBegin(0, 80, true);              // timer 0, preskaler 80 (dla 1MHz)
  timerAttachInterrupt(timer, &onTimer, true);  // obsługa przerwania
  timerAlarmWrite(timer, 100000, true);         // 100 ms = 100000 us
  timerAlarmEnable(timer);

  // Konfiguracja GPIO dla każdego przepływomierza
  for (int i = 0; i < NUM_SENSORS; i++) {
    pinMode(sensors[i].pin, INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(sensors[0].pin), pulseCounter0, FALLING);
  attachInterrupt(digitalPinToInterrupt(sensors[1].pin), pulseCounter1, FALLING);

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
    portEXIT_CRITICAL_ISR(&interruptMux);
    
    for (int i = 0; i < NUM_SENSORS; i++) {
      FlowSensor &sensor = sensors[i];        // Odwołanie do aktualnego przepływomierza
      portENTER_CRITICAL_ISR(&interruptMux);  // Zabezpieczenie współdzielonych zmiennych
      sensor.frequency = sensor.lastPulseCount / 1;
      portEXIT_CRITICAL_ISR(&interruptMux);
      int index = sensor.sampleIndex;

      if (!sensor.firstMeasurement) {
        // Aktualizacja próbek
        sensor.samples[index] = sensor.frequency;
        if (index + 1 == SUMPLES_SIZE) {
          sensor.firstSequence = false;
        }
        sensor.sampleIndex = (index + 1) % SUMPLES_SIZE;

        // Obliczanie średniej
        int range = 0;
        sensor.avgFrequency = 0;
        if (sensor.firstSequence)
          range = sensor.sampleIndex;
        else
          range = SUMPLES_SIZE;
        for (int j = 0; j < range; j++) {
          sensor.avgFrequency += sensor.samples[j];
        }
        sensor.avgFrequency /= range;
      }
      sensor.firstMeasurement = false;
    }
  }

  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.setCursor(0, 0);

  char buffer[40];

  for (int i = 0; i < NUM_SENSORS; i++) {
    FlowSensor &sensor = sensors[i];  // Odwołanie do aktualnego przepływomierza

    // snprintf(buffer, sizeof(buffer), "Sensor %d:", i + 1);
    // M5.Lcd.println(buffer);

    // snprintf(buffer, sizeof(buffer), "Time: %i ms", timeCount * 100);
    // M5.Lcd.println(buffer);

    // snprintf(buffer, sizeof(buffer), "Pulses: %i\n", sensor.pulseCount);
    // M5.Lcd.println(buffer);

    M5.Lcd.setTextSize(2);
    snprintf(buffer, sizeof(buffer), "INSTANT %.2f Hz\n", sensor.frequency);
    M5.Lcd.println(buffer);

    M5.Lcd.setTextSize(3);
    snprintf(buffer, sizeof(buffer), "%.2f Hz\n", sensor.avgFrequency);
    M5.Lcd.println(buffer);
  }

  M5.Lcd.drawFastHLine(0, DISPLAY_HEIGH/3-10, DISPLAY_WIDTH, TFT_WHITE);

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
