/* 
 * Soubor: CrossroadPhase.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-29
 */

#include "CrossroadPhase.h"

#include "Lane.h"

/**
 * Nastaveni semaforu na danem proudu.
 * 
 * @param lane proudu
 * @param color barva semaforu
 */
void CrossroadPhase::setLaneSemaphoreColor(Lane* lane, CrossroadPhase::Color color)
{
    laneSemaphoreColors[lane] = color;
}

/**
 * Ziskani barev semaforu na vsech proudech.
 * 
 * @return barvy semaforu 
 */
std::map<Lane*, CrossroadPhase::Color>& CrossroadPhase::getLaneSemaphoreColors()
{
    return laneSemaphoreColors;
}

/**
 * Vypocet poctu vozidel na proudech kde je zelena.
 * 
 * @return pocet vozidel
 */
int CrossroadPhase::getCarCount()
{
    int carCount = 0;

    for (auto lanePhase : laneSemaphoreColors)
    {
        if (lanePhase.second == CrossroadPhase::Color::Green)
        {
            carCount += lanePhase.first->getCarCount();
        }
    }
    
    return carCount;
}
/**
 * Vypocet poctu vozidel na proudech, ktere vedou rovne a kde je zelena.
 * 
 * @return pocet vozidel
 */
int CrossroadPhase::getCarCountForward()
{
    int carCountForward = 0;

    for (auto lanePhase : laneSemaphoreColors)
    {
        if (lanePhase.second == CrossroadPhase::Color::Green)
        {
            if (lanePhase.first->getDirection() == Lane::Direction::Forward)
            {
                carCountForward += lanePhase.first->getCarCount();
            }
        }
    }
    
    return carCountForward;
}

/**
 * Vypocet nejvetsi doby cekani vozidel na proudech kde je zelena.
 * 
 * @return doba cekani
 */
double CrossroadPhase::getCarWaitingTime()
{
    double highestWaitTime = 0.0;
    
    for (auto lanePhase : laneSemaphoreColors)
    {
        if (lanePhase.second == CrossroadPhase::Color::Green)
        {
            if (lanePhase.first->getWaitTime() > highestWaitTime)
            {
                highestWaitTime = lanePhase.first->getWaitTime();
            }
        }
    }
    
    return highestWaitTime;
}
