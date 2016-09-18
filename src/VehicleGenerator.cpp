/* 
 * Soubor: VehicleGenerator.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "VehicleGenerator.h"

#include "Vehicle.h"
#include "Lane.h"
#include "Parameters.h"

/**
 * Konstrukce generovani vozidel.
 * 
 * @param lane proud na ktery budou vozidla generovana
 */
VehicleGenerator::VehicleGenerator(Lane* lane)
    : lane(lane)
{
}

/**
 * Definice generatoru vozidel.
 */
void VehicleGenerator::Behavior()
{
    // Vytvoreni vozidla
    (new Vehicle(lane))->Activate();

    double interval;
    switch (Param::instance().experiment)
    {
        default:
        case 1: interval = getTimeScenario1(); break;
        case 2: interval = getTimeScenario2(); break;
    }
    // Nastaveni dalsiho generovani vozidla
    Activate(Time + interval);
}

/**
 * Generovani nahodneho intervalu do dalsi generace vozidla.
 * 
 * Vozidla na proudech rovne a vpravo jsou generovana Normalni 
 * pravdepodobnostnim rozdeleni s mi=15 sigma=6. Proudy v levo mi=30 sigma=10.
 * V case 1800-5400: je na severni ceste 2x vetsi provoz
 * V case 5400-9000: je na jizni ceste 2x vetsi provoz
 * 
 * @return interval
 */
double VehicleGenerator::getTimeScenario1()
{
    double mi;
    double sigma;
    
    switch (lane->getDirection())
    {
        default:
        case Lane::Direction::Left:
            mi = 30;
            sigma = 10;
            break;
        case Lane::Direction::Forward:
        case Lane::Direction::Right:
            mi = 15;
            sigma = 6;
            break;
    }
    
    if (lane->getSide() == Lane::Side::North && Time > (0.5 HODINA) && Time < (1.5 HODINA))
    {
        mi /= 2;
    }
    else if (lane->getSide() == Lane::Side::South && Time > (1.5 HODINA) && Time < (2.5 HODINA))
    {
        mi /= 2;
    }
    
    
    double interval;
    
    // Normalni rozdeleni muze vygenerovat i zaporne hodnoty 
    // a ty je treba filtrovat
    do
    {
        interval = Normal(mi,sigma);
    } while (interval <= 0.0);
    
    return interval;
}

/**
 * Generovani nahodneho intervalu do dalsi generace vozidla.
 * 
 * Vozidla na proudech rovne a vpravo jsou generovana Normalni 
 * pravdepodobnostnim rozdeleni s mi=12 sigma=4. Proudy v levo mi=30 sigma=10.
 * 
 * @return interval
 */
double VehicleGenerator::getTimeScenario2()
{
    double mi;
    double sigma;
    
    switch (lane->getDirection())
    {
        default:
        case Lane::Direction::Left:
            mi = 30;
            sigma = 10;
            break;
        case Lane::Direction::Forward:
        case Lane::Direction::Right:
            mi = 12;
            sigma = 4;
            break;
    }
    
    double interval;
    
    // Normalni rozdeleni muze vygenerovat i zaporne hodnoty 
    // a ty je treba filtrovat
    do
    {
        interval = Normal(mi,sigma);
    } while (interval <= 0.0);
    
    return interval;
}
