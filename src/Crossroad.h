/* 
 * Soubor: Crossroad.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#ifndef CROSSROAD_H
#define CROSSROAD_H

#include <vector>
#include "CrossroadPhase.h"
#include "FuzzyControl.h"
#include "simlib.h"

class Lane;

/**
 * Trida krizovatky
 */
class Crossroad
{
    public:
        
        /**
         * Zpusob prepinani fazi
         */
        enum class Phasing
        {
            Sequential, // Sekvencni/postupne prepinani
            Fuzzy       // Adaptivni prepinani pomoci Fuzzy logiky
        };
        
        /**
         * Statistiky pro celou krizovatku (vsechny proudy).
         */
        struct Stats
        {
            // Zpusob rizeni semaforu
            Crossroad::Phasing phasing = Crossroad::Phasing::Sequential; 
            
            double avgQueueLen = 0; // Prumerna delka front
            double maxQueueLen = 0; // Maximalni delka fronty

            double avgWaitTime = 0; // Prumerna doba cekani vozidla na cervene
            double maxWaitTime = 0; // Maximalni doba cekani vozidla na cervene
            
            Stats() { }
            Stats(Crossroad::Phasing phasing, double avgQueueLen,
                  double maxQueueLen, double avgWaitTime, double maxWaitTime) 
                : phasing(phasing), avgQueueLen(avgQueueLen)
                , maxQueueLen(maxQueueLen), avgWaitTime(avgWaitTime)
                , maxWaitTime(maxWaitTime)
            {
            }
        };
        
    private:

        /**
         * Trida pro periodicky tisk stavu krizovatky.
         */
        class Printer : public Event
        {
            private:
                Crossroad* crossroad;
                double interval;
            public:
                Printer(Crossroad* crossroad);
                void Behavior() override;
        };
        
        /**
         * Trida, ktera vyvolava zmenu faze.
         */
        class NextCrossroadPhase : public Event
        {
            private:
                Crossroad* crossroad;
            public:
                NextCrossroadPhase(Crossroad* crossroad);
                void Behavior() override;
        };
        
        friend class NextCrossroadPhase;

        // Zakladni interval mezi zmenou fazi
        static constexpr double PHASE_TIME_BASE = 30;
        // Doba prodlouzeni faze
        static constexpr double PHASE_TIME_EXTEND = 5;
        
        std::vector<Lane*> lanes; // Vsechny porudy krizovatky
        std::vector<CrossroadPhase> crossroadPhases; // Faze
        
        int currentPhaseIndex; // Index (crossroadPhases) aktualni faze
        FuzzyControl fuzzyControl; // Fuzzy kontroler
        Phasing phasing; // Zpusob rizeni

    public:

        Crossroad();
        ~Crossroad();

        void setPhasing(Crossroad::Phasing phasing);
        void activate();
        
        void printStats();
        void printCrossroad();
        void printAverageQueueSize();
        void printAverageLaneQueueSize();
        
        Crossroad::Stats getTotalAvgStats();
        static void printComparedStats(std::vector<Crossroad::Stats> stats);
        
    private:

        void createLanes();
        void createPhases();
        
        void setPhase(int newPhaseIndex);
        
        int getNewPhase();
        int getNewPhaseSequential();
        int getNewPhaseFuzzy();
        
        void printNewPhase(int newPhaseIndex);
        
        std::string getFillSpaces(const char* s, int desiredWidth);
        void printLaneStats(Lane* lane);
        void printTotalAvgStats(std::vector<Lane*> lanes);

};

#endif /* CROSSROAD_H */
