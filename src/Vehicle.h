/* 
 * Soubor: Vehicle.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#ifndef VEHICLE_H
#define VEHICLE_H

#include "simlib.h"

class Lane;

/**
 * Trida pro simulaci vozidla.
 */
class Vehicle : public Process
{
    private:

        Lane* lane;
        double queueEnterTime;

    public:
        
        Vehicle(Lane* lane);

        void Behavior() override;
        
        double getQueueEnterTime();

};

#endif /* VEHICLE_H */
