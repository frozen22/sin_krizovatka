/* 
 * Soubor: Vehicle.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "Vehicle.h"

#include "Lane.h"
#include "Parameters.h"
#include "CrossroadSemaphore.h"

/**
 * Konstrukce vozidla.
 * 
 * @param lane proud na kterem se vozidlo nachazi
 */
Vehicle::Vehicle(Lane* lane)
    : lane(lane)
{
}

/**
 * Definice chovani vozidla.
 */
void Vehicle::Behavior()
{
    queueEnterTime = Time;
    
    Seize(*lane); 

    if (lane->getSemaphore()->isRed()) // Cervena
    {
        // Prvni vozidlo u krizovatky, ktere ceka na zelenou
        lane->waitForGreen(this);
        // Semafor ma zelenou, projizdim krizovatkou
        Wait(TIME_TO_CROSS_FIRST);
    }
    else // Zelena
    {
        // Vozidlo prijelo ke krizovatce a neni cervena
        Wait(TIME_TO_CROSS_NEXT);
    }
    
    Release(*lane);
}

/**
 * Ziskani casu zarazeni vozidla do proudu.
 * 
 * @return cas zarazeni vozidla do proudu
 */
double Vehicle::getQueueEnterTime()
{
    return queueEnterTime;
}
