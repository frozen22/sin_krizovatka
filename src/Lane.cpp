/* 
 * Soubor: Lane.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "Lane.h"

#include "CrossroadSemaphore.h"
#include "VehicleGenerator.h"
#include "Vehicle.h"
#include "Debug.h"

// Pri "std::string name" se spatne uklada jmeno, ulozi se jen prvni
// ctyri znaky, proto je parametr typu "const char*".

/**
 * Konstrukce proudu.
 * 
 * @param direction smer
 * @param name nazev
 */
Lane::Lane(Lane::Direction direction, Lane::Side side, const char* name)
    : Facility(name)
    , direction(direction)
    , side(side)
{
    semaphore = new CrossroadSemaphore(this);
    vehicleGenerator = new VehicleGenerator(this);
    firstWaitingVehicle = nullptr;
}

/**
 * Destrukce proudu
 */
Lane::~Lane()
{
    delete semaphore;
    delete vehicleGenerator;
}

/**
 * Ziskani semaforu proudu.
 * 
 * @return semafor
 */
CrossroadSemaphore* Lane::getSemaphore()
{
    return semaphore;
}

/**
 * Ziskani generatoru vozidel proudu.
 * 
 * @return generator vozidel
 */
VehicleGenerator* Lane::getVehicleGenerator()
{
    return vehicleGenerator;
}

/**
 * Aktivace generatoru vozidel.
 */
void Lane::activateGenerator()
{
    if (vehicleGenerator)
    {
        vehicleGenerator->Activate();
    }
}

/**
 * Ulozeni vozidla, ktere ceka na zelenou. 
 * 
 * @param vehicle vozidlo
 */
void Lane::waitForGreen(Vehicle* vehicle)
{
    firstWaitingVehicle = vehicle;
    firstWaitingVehicle->Passivate();
}

/**
 * Aktivace vozidla cekajiciho na zelenou.
 */
void Lane::pushVehicle()
{
    if (firstWaitingVehicle != nullptr)
    {
        firstWaitingVehicle->Activate();
        firstWaitingVehicle = nullptr;
    }
}

/**
 * Ziskani poctu vozidel (delky fronty) na danem proudu.
 * 
 * @return pocet vozidel (delka fronty)
 */
int Lane::getCarCount()
{
    return QueueLen();
}

/** 
 * Zjisteni delky cekani vozidla na krizovatce (od doby prijeti do proudu).
 * 
 * @return delka cekani prvniho vozidla ve fronte (0.0 pokud je fronta prazdna)
 */
double Lane::getWaitTime()
{
    if (!Q1->Empty())
    {
        Vehicle* vehicle = static_cast<Vehicle*>(Q1->GetFirst());
        // Q1->GetFirst() zaroven odstranuje Entitu z fronty, je treba ji vratit
        Q1->InsFirst(vehicle);
        return Time - vehicle->getQueueEnterTime();
    }
    else
    {
        return 0.0;
    }
}

/**
 * Ziskani smeru proudu.
 * 
 * @return smer proudu
 */
Lane::Direction Lane::getDirection()
{
    return direction;
}

/**
 * Ziskani strany proudu.
 * 
 * @return strana proudu
 */
Lane::Side Lane::getSide()
{
    return side;
}
