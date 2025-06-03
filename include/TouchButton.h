#ifndef TOUCHBUTTON_H
#define TOUCHBUTTON_H

#include <Arduino.h>

/**
 * Klasa reprezentujaca przycisk dotykowy
 * Odpowiada za rysowanie, wykrywanie klikniec i udostepnianie pozycji
 */
class TouchButton {
  public:
    /**
     * Konstruktor przycisku dotykowego
     * @param label       Tekst etykiety przycisku
     * @param x           Wspolrzedna X lewego gornego rogu
     * @param y           Wspolrzedna Y lewego gornego rogu
     * @param width       Szerokosc przycisku
     * @param height      Wysokosc przycisku
     * @param color       Kolor tla przycisku (domyslnie TFT_WHITE)
     * @param textColor   Kolor tekstu (domyslnie TFT_BLACK)
     */
    TouchButton(const String& label,
                int x, int y, int width, int height,
                uint16_t color = TFT_WHITE, uint16_t textColor = TFT_BLACK);

    /**
     * Rysuje przycisk na ekranie
     */
    void draw();

    /**
     * Sprawdza, czy przycisk jest aktualnie wcisniety
     * @param touchX  Pozycja dotyku w osi X
     * @param touchY  Pozycja dotyku w osi Y
     * @return true jesli dotyk znajduje sie w obszarze przycisku
     */
    bool isPressed(int touchX, int touchY) const;

    /**
     * Sprawdza, czy przycisk zostal wcisniety jednokrotnie.
     * @param touchX  Pozycja dotyku w osi X
     * @param touchY  Pozycja dotyku w osi Y
     * @return true jesli klikniecie nastapilo teraz (a nie bylo aktywne wczesniej)
     */
    bool wasJustPressed(int touchX, int touchY);

    /**
     * Zwraca etykiete przycisku
     */
    String getLabel() const;
    
    /**
     * Zwraca wspolrzedna X przycisku
     */
    int getX() const;

    /**
     * Zwraca wspolrzedna Y przycisku
     */
    int getY() const;

    /**
     * Zwraca szerokosc przycisku
     */
    int getWidth() const;

    /**
     * Zwraca wysokosc przycisku
     */
    int getHeight() const;

  private:
    String _label;
    int _x, _y, _width, _height;
    uint16_t _color, _textColor;

    bool _wasPreviouslyPressed; ///< Flaga wykrywania klikniecia jednokrotnego
};

#endif // TOUCHBUTTON_H