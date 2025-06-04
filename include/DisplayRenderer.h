#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <Arduino.h>
#include <M5Unified.h>

/*
 * Klasa odpowiedzialna za rysowanie tresci na ekranie
 */
class DisplayRenderer {
  public:
    /*
     * Konstruktor
     * @param   displayWidth   Szerokosc wyswietlacza (domyslnie 320)
     * @param   displayHeight  Wysokosc wyswietlacza (domyslnie 240)
     */
    DisplayRenderer(int displayWidth = 320, int displayHeight = 240);

    /*
     * Wyswietla czestotliwosci (chwilowa i srednia) na ekranie
     * @param   frequency      Czestotliwosc chwilowa (Hz)
     * @param   avgFrequency   Srednia czestotliwosc (Hz)
     * @param   rateLPM        Przeplyw przeliczony na litry na minute [L/min]
     */
    void renderMeasurements(float frequency, float avgFrequency, float rateLPM);

    /*
     * Wyswietla szczegolowe dane czujnika przeplywu.
     * @param   sensorId     Numer czujnika (indeks)
     * @param   timeCount    Liczba odczytow czasu (w setkach ms)
     * @param   pulseCount   Liczba impulsow z czujnika
     */
    void renderSensorDetails(int sensorId, int timeCount, int pulseCount);

    /*
     * Wyswietla szczegolowe dane czujnika przeplywu.
     * @param   sensorId     Numer czujnika (indeks)
     * @param   timeCount    Liczba odczytow czasu (w setkach ms)
     * @param   totalPulse   Calkowita liczba impulsow od uruchomienia/resetu
     * @param   totalLiters  Calkowita objetosc przeplywu przeliczona na litry
     * @param   rateLPM      Przeplyw przeliczony na litry na minute [L/min]
     */
    void renderSensorDetails(int sensorId, float frequency, float avgFrequency, int totalPulse, float totalLiters, float rateLPM);

    /*
     * Rysuje pozioma linie oddzielajaca w danym miejscu
     * @param   y   Pozycja pionowa linii (w pikselach)
     */
    void drawDividingLine(int y);

    /*
     * Czysci prostokatny obszar ekranu miedzy podanymi wspolrzednymi
     * @param   yStart   Gorna granica obszaru
     * @param   yEnd     Dolna granica obszaru
     */
    void clearRegion(int yStart, int yEnd);

    /*
     * Zwraca szerokosc wyswietlacza
     */
    int getDisplayWidth() const;

    /*
     * Zwraca wysokosc wyswietlacza
     */
    int getDisplayHeight() const;

  private:
    int _displayWidth;
    int _displayHeight;

    /*
     * Oblicza ilosc spacji potrzebnych do wyrownania tekstu na srodku
     * @param   text      Tekst do wyrownania
     * @param   textSize  Rozmiar tekstu (skala)
     * @retval  Liczba spacji do dopelnienia
     */
    int autoPadSpaces(const String& text, int textSize);
};

#endif // DISPLAYRENDERER_H