#ifndef FLOWSENSOR_H
#define FLOWSENSOR_H

#include <Arduino.h>
#include "Config.h"

/**
 * Klasa reprezentujaca czujnik przeplywu
 * Zarzadza liczeniem impulsow i obliczaniem czestotliwosci
 */
class FlowSensor {
  public:
    /**
     * Konstruktor czujnika przeplywu
     * @param   pin   Numer pinu podlaczonego do czujnika przeplywu
     */
    FlowSensor(int pin);

    /**
     * Inicjalizuje czujnik przeplywu
     */
    void setupFlowSensor(void);

    /**
     * Podlacza przerwanie do liczenia impulsow z czujnika
     */
    void attachSensorInterrupt(void);

    /**
     * Odlacza przerwanie, przestaje liczyc impulsy
     */
    void detachSensorInterrupt(void);

    /**
     * Aktualizuje licznik impulsow (wywolywane z przerwania)
     */
    void updatePulseCount(void);

    /**
     * Oblicza czestotliwosc na podstawie liczby impulsow
     */
    void calculateFrequency(void);

    /**
     * Dodaje aktualna czestotliwosc do tablicy probek
     */
    void updateSamples(void);

    /**
     * Oblicza srednia czestotliwosc na podstawie probek
     */
    void setAvgFrequency(void);

    /**
     * Resetuje czujnik przeplywu (czyści liczniki i probki)
     */
    void reset(void);

    /**
     * Zwraca chwilowa czestotliwosc w Hz
     */
    float getInstantFrequency(void) const;

    /**
     * Zwraca srednia czestotliwosc w Hz
     */
    float getAvgFrequency(void) const;

    /**
     * Zwraca laczna liczbe impulsow
     */
    int getPulseCount(void) const;
 
    /**
     * Zwraca calkowita liczbe impulsow od uruchomienia lub ostatniego resetu.
     */
    int getTotalPulseCount(void) const;

    /*
     * Zwraca objetosc w litrach od ostatniego resetu
     */
    float getTotalLiters(void) const;

    /*
     * Zwraca szybkosc przeplywu w l/min
     */
    float getFlowRateLPM(void) const;

  private:
    int pin_;                     ///< Pin podlaczony do czujnika przeplywu
    volatile int pulseCount;      ///< Licznik impulsow
    volatile int lastPulseCount;  ///< Ostatnia liczba impulsow (do obliczen)
    volatile int totalPulseCount; ///< Liczenia calkowitej objetosci
    volatile float frequency;     ///< Chwilowa czestotliwosc

    float samples[SAMPLE_SIZE];   ///< Tablica probek do sredniowania
    volatile int sampleIndex;     ///< Indeks do tablicy probek
    volatile float avgFrequency;  ///< Srednia czestotliwosc
    volatile bool firstSequence;  ///< Flaga oznaczajaca pierwszy pomiar

    portMUX_TYPE interruptMux = portMUX_INITIALIZER_UNLOCKED;   ///< Sekcja krytyczna do ochrony przerwan

    static FlowSensor* instance;    ///< Statyczny wskaznik instancji (do przerwan)

    /**
     * Funkcja obslugi przerwania liczaca impulsy.
     */
    static void IRAM_ATTR pulseCounter(void);
};

#endif // FLOWSENSOR_H
