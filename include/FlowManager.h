#ifndef FLOWMANAGER_H
#define FLOWMANAGER_H

#include <Arduino.h>
#include "FlowSensor.h"

/**
 * Klasa do zarzadzania wieloma czujnikami przeplywu i obslugi czasu.
 * Odpowiada za inicjalizacje czujnikow, konfiguracje timera,
 * przetwarzanie pomiarow oraz resetowanie stanu ukladu
 */
class FlowManager {
  public:
    FlowManager(void);
    ~FlowManager(void);

    /**
     * Ustawia timer do okresowych pomiarow
     */
    void setupTimer(void);

    /**
     * Inicjalizuje czujniki przeplywu
     */
    void setupFlowSensors(void);

    /**
     * Przetwarza dane z czujnikow przeplywu
     */
    void measurementsProcessing(void);

    /**
     * Resetuje wszystkie czujniki przeplywu i stan wewnetrzny
     */
    void reset(void);

    /**
     * Zwraca wskaznik do czujnika przeplywu na podstawie indeksu
     * @param   index   Indeks czujnika
     * @retval  Wskaznik do obiektu FlowSensor
     */
    FlowSensor* getSensor(size_t index) const;

    /**
     * Zwraca liczbe czujnikow przeplywu
     */
    size_t getNumSensors(void) const;

    /**
     * Zwraca aktualna wartosc licznika czasu
     */
    int getTimeCount(void) const;

    volatile bool measurementFlag;  ///< Flaga oznaczajaca czy pomiary maja byc przetwarzane

  private:
    /**
     * Funkcja obslugi przerwania timera.
     */
    static void IRAM_ATTR onTimer(void);

    portMUX_TYPE interruptManagerMux = portMUX_INITIALIZER_UNLOCKED;  ///< Sekcja krytyczna do ochrony przerwan timera

    hw_timer_t *timer;        ///< Obiekt timera
    volatile int timeCount;   ///< Licznik czasu dla pomiarow

    static FlowManager* instance;     ///< Statyczny wskaznik instancji do obslugi przerwan

    FlowSensor** sensors;     ///< Tablica wskaznikow na czujniki przeplywu
    size_t numSensors;        ///< Liczba czujnikow

    volatile bool firstMeasurement;  ///< Flaga oznaczajaca pierwszy pomiar
};

#endif // FLOWMANAGER_H