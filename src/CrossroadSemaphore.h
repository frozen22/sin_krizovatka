/* 
 * Soubor: CrossroadSemaphore.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#ifndef CROSSROADSEMAPHORE_H
#define CROSSROADSEMAPHORE_H

#include "CrossroadPhase.h"

class Lane;

/**
 * Trida semaforu. Nelze pouzit nazev Semaphore, protoze ten uz je v simlibu.
 */
class CrossroadSemaphore
{
    private:
        
        Lane* lane;
        bool green;
    
    public:

        CrossroadSemaphore(Lane* lane);
        
        void setColor(CrossroadPhase::Color color);
        void setGreen();
        void setRed();
        
        bool isGreen();
        bool isRed();
        
};

#endif /* CROSSROADSEMAPHORE_H */
