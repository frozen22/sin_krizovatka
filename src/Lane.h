/* 
 * Soubor: Lane.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#ifndef LANE_H
#define LANE_H

#include "simlib.h"

class CrossroadSemaphore;
class VehicleGenerator;
class Vehicle;

/**
 * Trida proudu krizovatky
 */
class Lane : public Facility
{
    public:
    
        /**
         * Smer proudu
         */
        enum class Direction 
        {
            Left,
            Forward,
            Right
        };
        
        /**
         * Strana na ktere se proud nachazi.
         */
        enum class Side
        {
            East,
            North,
            West,
            South
        };
    
    private:
    
        Lane::Direction direction;
        Lane::Side side;
        
        CrossroadSemaphore* semaphore;
        VehicleGenerator* vehicleGenerator;
        
        Vehicle* firstWaitingVehicle;
        
    public:
        
        Lane(Lane::Direction direction, Lane::Side side, const char* name = 0);
        ~Lane();
        
        void activateGenerator();
        
        void waitForGreen(Vehicle* vehicle);
        void pushVehicle();
        
        CrossroadSemaphore* getSemaphore();
        VehicleGenerator* getVehicleGenerator();
        int getCarCount();
        double getWaitTime();
        
        Lane::Direction getDirection();
        Lane::Side getSide();
};

#endif /* LANE_H */

