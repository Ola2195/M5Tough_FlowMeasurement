#ifndef VIEW_H
#define VIEW_H

#include "FlowManager.h"

#include "DisplayRenderer.h"
#include "TouchButton.h"
#include "TouchUI.h"

/*
 * Klasa bazowa dla wszystkich widokow ekranowych.
 * Umozliwia definiowanie interfejsow uzytkownika.
 */
class BaseView {
  public:
    virtual void setup() {};    // Inicjalizuje widok i jego komponenty
    virtual void render() {};   // Rysuje zawartosc widoku
    virtual void update() {};   // Obsluguje aktualizacje i wejscia uzytkownika

    virtual ~BaseView() = default;  // Wirtualny destruktor
};

/*
 * Klasa widoku glownego wyswietlajaca dane pomiarowe.
 * Opowiada za wyswietlanie czestotliwosci z czujnikow,
 * obsluge przycisku RESET oraz komunikacje z FlowManagerem.
 */
class MainMeasurementView : public BaseView {
  public:
    /*
     * Konstruktor widoku glownego.
     * @param   manager  Referencja do menadzera przeplywu (FlowManager).
     */
    MainMeasurementView(FlowManager& manager);

    /*
     * Inicjalizuje interfejs widoku glownego.
     * Czysci ekran, dodaje przycisk RESET i rysuje przyciski interfejsu dotykowego.
     */
    void setup() override;

    /*
     * Rysuje interfejs pomiarowy.
     */
    void render() override;

    /*
     * Obsluguje dotyk i przycisk RESET w interfejsie.
     */
    void update() override;

  private:
    int _margin;                ///< Margines wokol przycisku RESET

    FlowManager& _manager;      ///< Referencja do menadzera pomiarow
    DisplayRenderer _renderer;  ///< Klasa renderujaca dane na ekran
    TouchButton _resetButton;   ///< Przycisk RESET
    TouchUI _ui;                ///< Interfejs obslugi dotyku
};

#endif // VIEW_H
