/* 
 * Soubor: CrossroadSemaphore.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "CrossroadSemaphore.h"

#include "Lane.h"

/**
 * Konstrukce semaforu pro dany proud.
 * 
 * @param proud krizovatky
 */
CrossroadSemaphore::CrossroadSemaphore(Lane* lane)
    : lane(lane)
{
}

/**
 * Nastaveni barvy semaforu.
 * 
 * @param color nova barva semaforu
 */
void CrossroadSemaphore::setColor(CrossroadPhase::Color color)
{
    switch (color)
    {
        case CrossroadPhase::Color::Red:   setRed();   break;
        case CrossroadPhase::Color::Green: setGreen(); break;
    }
}

/**
 * Nastaveni semaforu na zelenou barvu.
 */
void CrossroadSemaphore::setGreen()
{
    green = true;
    lane->pushVehicle(); // Rozjeti kolony cekajicich vozidel
}

/**
 * Nastaveni semaforu na cervenou barvu.
 */
void CrossroadSemaphore::setRed()
{
    green = false;
}

/**
 * Test zda je na semaforu zelena barva.
 * 
 * @return true - na semaforu je zelena barva
 */
bool CrossroadSemaphore::isGreen()
{
    return green;
}

/**
 * Test zda je na semaforu cervena barva.
 * 
 * @return true - na semaforu je cervena barva
 */
bool CrossroadSemaphore::isRed()
{
    return !green;
}
