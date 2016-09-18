/* 
 * Soubor: VehicleGenerator.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#ifndef VEHICLEGENERATOR_H
#define VEHICLEGENERATOR_H

#include "simlib.h"

class Lane;

/**
 * Trida generatoru vozidel
 */
class VehicleGenerator : public Event
{
    private:
        
        Lane* lane;
        
    public:

        VehicleGenerator(Lane* lane);
 
        void Behavior() override;
        
    private:
        
        double getTimeScenario1();
        double getTimeScenario2();

};

#endif /* VEHICLEGENERATOR_H */

