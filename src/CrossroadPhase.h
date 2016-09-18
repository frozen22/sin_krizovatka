/* 
 * Soubor: CrossroadPhase.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-29
 */


#ifndef CROSSROADPHASE_H
#define CROSSROADPHASE_H

#include <map>

class Lane;

/**
 * Trida fazi semaforu na krizovatce
 */
class CrossroadPhase
{
    public:
        
        /**
         * Vycet hodnot semaforu
         */
        enum class Color
        {
            Green,
            Red
        };
    
    private:
        
        // Nastaveni semaforu na danych proudech
        std::map<Lane*, CrossroadPhase::Color> laneSemaphoreColors;
        
    public:

        void setLaneSemaphoreColor(Lane* lane, CrossroadPhase::Color color);
        std::map<Lane*, CrossroadPhase::Color>& getLaneSemaphoreColors();
        
        int getCarCount();
        int getCarCountForward();
        double getCarWaitingTime();

};

#endif /* CROSSROADPHASE_H */

