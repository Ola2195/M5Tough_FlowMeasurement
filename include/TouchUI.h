#ifndef TOUCHUI_H
#define TOUCHUI_H

#include "TouchButton.h"

#include <Arduino.h>
#include <map>

/*
 * Klasa obslugujaca kolekcje elementow dotykowych.
 * Umozliwia dodawanie i rysowanie przyciskow oraz
 * detekcje wcisniec na podstawie pozycji dotyku.
 */
class TouchUI {
  public:
    /*
     * Dodaje przycisk do interfejsu.
     * @param   id      Identyfikator przycisku.
     * @param   button  Obiekt przycisku TouchButton.
     */
    void addButton(const String& id, const TouchButton& button);

    /*
     * Rysuje wszystkie przyciski na ekranie.
     */
    void drawButtons();

    /*
     * Zwraca identyfikator przycisku, ktory zostal wlasnie nacisniety.
     * @retval  ID przycisku lub pusty string, jesli zaden nie zostal aktywowany.
     */
    String getJustPressed();

    /*
     * Aktualizuje stan interfejsu (czysci dane dotyku).
     */
    void update();

  private:
    std::map<String, TouchButton> buttons;  ///< Mapa przyciskow wedlug ID
};

#endif // TOUCHUI_H