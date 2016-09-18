/* 
 * Soubor: Crossroad.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "Crossroad.h"

#include "CrossroadSemaphore.h"
#include "Debug.h"
#include "Lane.h"
#include "Parameters.h"

using std::cout;
using std::endl;
    
/**
 * Konstrukce krizovatky.
 */
Crossroad::Crossroad()
{
    createLanes();
    createPhases();
    phasing = Phasing::Fuzzy;
}

/**
 * Destrukce krizovatky.
 */
Crossroad::~Crossroad()
{
    for (Lane* lane : lanes)
    {
        delete lane;
    }
}

/**
 * Vytvoreni proudu krizovatky.
 */
void Crossroad::createLanes()
{
//                |   |   |   |   |     
//                |   |   |   |   |     
//                |   |   |   |   |     
//                |   |   |   |   |     
//                | ← | ↓ | → |   |   
//                +---+---+---+---+
//                                  +-------------
//                                  | ↑            
//  ------------+                   +-------------
//              |                   | ←           
//  ------------+                   +-------------
//            → |                   | ↓            
//  ------------+                   +------------- 
//            ↓ |                   |             
//  ------------+                   +------------- 
//                +---+---+---+---+
//                |   | ← | ↑ | → |                            
//                |   |   |   |   |                            
//                |   |   |   |   |    
//                |   |   |   |   |   
//                |   |   |   |   |    
//                |   |   |   |   |  
    
    lanes.push_back(new Lane(Lane::Direction::Left,    Lane::Side::East, "East Left"));
    lanes.push_back(new Lane(Lane::Direction::Forward, Lane::Side::East, "East Forward"));
    lanes.push_back(new Lane(Lane::Direction::Right,   Lane::Side::East, "East Right"));
    
    lanes.push_back(new Lane(Lane::Direction::Left,    Lane::Side::North, "North Left"));
    lanes.push_back(new Lane(Lane::Direction::Forward, Lane::Side::North, "North Forward"));
    lanes.push_back(new Lane(Lane::Direction::Right,   Lane::Side::North, "North Right"));
    
    lanes.push_back(new Lane(Lane::Direction::Forward, Lane::Side::West, "West Forward"));
    lanes.push_back(new Lane(Lane::Direction::Right,   Lane::Side::West, "West Right"));
    
    lanes.push_back(new Lane(Lane::Direction::Left,    Lane::Side::South, "South Left"));
    lanes.push_back(new Lane(Lane::Direction::Forward, Lane::Side::South, "South Forward"));
    lanes.push_back(new Lane(Lane::Direction::Right,   Lane::Side::South, "South Right"));
}

/**
 * Vytvoreni fazi semaforu.
 */
void Crossroad::createPhases()
{
    // -- 1 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Red);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Green);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Red);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Green);
        crossroadPhases.push_back(crossroadPhase);
    }
    // -- 2 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Green);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Red);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Green);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Red);
        crossroadPhases.push_back(crossroadPhase);
    }
    // -- 3 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Green);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Red);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Red);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Green);
        crossroadPhases.push_back(crossroadPhase);
    }
    // -- 4 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Red);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Red);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Green);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Green);
        crossroadPhases.push_back(crossroadPhase);
    }
    // -- 5 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Green);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Green);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Green);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Red);
        crossroadPhases.push_back(crossroadPhase);
    }
    // -- 6 --------------------------------------------------------------------
    {
        CrossroadPhase crossroadPhase;
        // East
        crossroadPhase.setLaneSemaphoreColor(lanes[0], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[1], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[2], CrossroadPhase::Color::Green);
        // North
        crossroadPhase.setLaneSemaphoreColor(lanes[3], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[4], CrossroadPhase::Color::Green);
        crossroadPhase.setLaneSemaphoreColor(lanes[5], CrossroadPhase::Color::Green);
        // West
        crossroadPhase.setLaneSemaphoreColor(lanes[6], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[7], CrossroadPhase::Color::Red);
        // South
        crossroadPhase.setLaneSemaphoreColor(lanes[8], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[9], CrossroadPhase::Color::Red);
        crossroadPhase.setLaneSemaphoreColor(lanes[10], CrossroadPhase::Color::Red);
        crossroadPhases.push_back(crossroadPhase);
    }
}

/**
 * Nastaveni nove faze. Zmena hodnot semaforu na vsech proudech podle nove faze.
 * 
 * @param newPhaseIndex index nove faze
 */
void Crossroad::setPhase(int newPhaseIndex)
{
    currentPhaseIndex = newPhaseIndex;
    
    CrossroadPhase crossroadPhase = crossroadPhases[newPhaseIndex];
    for (auto lanePhase : crossroadPhase.getLaneSemaphoreColors())
    {
        lanePhase.first->getSemaphore()->setColor(lanePhase.second);
    }
}

/**
 * Vypocet nove faze. Podle phasing je vypocet proveden sekvence nebo pomoci
 * fuzzy logiky.
 * 
 * @return index nove faze.
 */
int Crossroad::getNewPhase()
{
    switch (phasing)
    {
        default:
        case Phasing::Fuzzy:      return getNewPhaseFuzzy();
        case Phasing::Sequential: return getNewPhaseSequential();
    }
}

/**
 * Vypocet nove faze sekvencnim zpusobem. 
 * 
 * @return index nove faze
 */
int Crossroad::getNewPhaseSequential()
{
    static unsigned int phaseIndex = 0;
    
    int newPhaseIndex = phaseIndex;
    setPhase(newPhaseIndex);
    
    if (++phaseIndex >= crossroadPhases.size())
    {
        phaseIndex = 0;
    }
    
    return newPhaseIndex;
}
/**
 * Vypocet nove faze pomoci fuzzy kontroleru. 
 * 
 * @return index nove faze
 */
int Crossroad::getNewPhaseFuzzy()
{
    int newPhaseIndex = fuzzyControl.makeDecision(crossroadPhases, currentPhaseIndex);
    
//    printNewPhase(newPhaseIndex);

    if (newPhaseIndex != FuzzyControl::EXTEND_PHASE)
    {
        setPhase(newPhaseIndex);
    }

    return newPhaseIndex;
}

/**
 * Inicializace zdroju krizovatky.
 */
void Crossroad::activate()
{
    for (Lane* lane : lanes)
    {
        lane->activateGenerator();
    }
    
    setPhase(0);
    
    (new NextCrossroadPhase(this))->Activate(Time + PHASE_TIME_BASE);
    if (Param::instance().printCrossroadStates)
    {
        OUT("Time|East|North|West|South|Average")
        (new Printer(this))->Activate();
    }
}

/**
 * Nastaveni zpusobu prepinany fazi.
 * 
 * @param phasing novy zpusob prepinani fazi
 */
void Crossroad::setPhasing(Crossroad::Phasing phasing)
{
    this->phasing = phasing;
}

/**
 * Tisk indexu nove faze nebo prodlouzeni aktualni faze.
 * 
 * @param newPhaseIndex index nove faze nebo FuzzyControl::EXTEND_PHASE
 */
void Crossroad::printNewPhase(int newPhaseIndex)
{
    if (newPhaseIndex == FuzzyControl::EXTEND_PHASE)
    {
        OUT(Time << "   extend current phase (" << currentPhaseIndex << ")")
    }
    else
    {
        OUT(Time << "   new phase   " << newPhaseIndex)
    }
}

/**
 * Tisk aktualniho zaplneni proudu na krizovatce.
 */
void Crossroad::printCrossroad()
{
    OUT("----------------------")
    for (Lane* lane : lanes)
    {
        OUT(lane->Name() << " - " << lane->QueueLen()) 
    }
}

/**
 * Tisk aktualniho zaplneni krizovatky (spolu s casem).
 */
void Crossroad::printAverageQueueSize()
{
    double averageQueueLen = 0.0;        
    for (Lane* lane : lanes)
    {
        averageQueueLen += lane->QueueLen();
    }
    averageQueueLen /= lanes.size();
    
    OUT(Time << "|" << averageQueueLen)
}

void Crossroad::printAverageLaneQueueSize()
{
    double averageQueueLenEast = (lanes[0]->QueueLen() + lanes[1]->QueueLen() + lanes[2]->QueueLen())/3.0;        
    double averageQueueLenNorth = (lanes[3]->QueueLen() + lanes[4]->QueueLen() + lanes[5]->QueueLen())/3.0;        
    double averageQueueLenWest = (lanes[6]->QueueLen() + lanes[7]->QueueLen())/2.0;        
    double averageQueueLenSouth = (lanes[8]->QueueLen() + lanes[9]->QueueLen() + lanes[10]->QueueLen())/3.0;    

    double averageQueueLen = 0.0;        
    for (Lane* lane : lanes)
    {
        averageQueueLen += lane->QueueLen();
    }
    averageQueueLen /= lanes.size();    
    
    OUT(Time << "|" 
        << averageQueueLenEast << "|"
        << averageQueueLenNorth << "|"
        << averageQueueLenWest << "|"
        << averageQueueLenSouth << "|"
        << averageQueueLen)
}


/**
 * Tisk tabulky s nekolika statistikami krizovatek.
 * 
 * @param stats pole statistik
 */
void Crossroad::printComparedStats(std::vector<Crossroad::Stats> stats)
{
    cout << "+-----------------+-------------------+-----------------------+" << endl; 
    cout << "| Control         |    Queue length   |      Waiting time     |" << endl; 
    cout << "| Comparison      |   avg   |   max   |    avg    |    max    |" << endl; 
    cout << "+-----------------+---------+---------+-----------+-----------+" << endl;
    
    for (Crossroad::Stats stat : stats)
    {
        const char* phasingStr = stat.phasing == Phasing::Fuzzy ? "Fuzzy     " : "Sequential";

        printf ("| %s      | %7.1f | %7.f | %9.1f | %9.1f |\n", 
            phasingStr, stat.avgQueueLen, stat.maxQueueLen, stat.avgWaitTime, stat.maxWaitTime);
    }
    
    cout << "+-----------------+---------+---------+-----------+-----------+" << endl;
}

/**
 * Vytvoreni poctu mezer, kde je treba doplnit k vstupnimu retezci, aby nabyl
 * pozadovane delky.
 * 
 * @param s vstupni retezec
 * @param desiredWidth pozadovana delka
 * @return retezec mezer
 */
std::string Crossroad::getFillSpaces(const char* s, int desiredWidth)
{
    int spaceCount = desiredWidth - std::string(s).size();
    std::string spaces;
    
    for (int i = 0; i < spaceCount; i++)
    {
        spaces += " ";
    }
    
    return spaces;
}

/**
 * Ziskani statistik proudu.
 * 
 * @param lane proud
 */
void Crossroad::printLaneStats(Lane* lane)
{
    double avgQueueLen = 0.0;
    double maxQueueLen = 0.0;
    
    double avgWaitTime = 0.0;
    double maxWaitTime = 0.0;
    
    if (lane->Q1->StatN.Number() > 0)
    {
        avgQueueLen = lane->Q1->StatN.MeanValue();
        maxQueueLen = lane->Q1->StatN.Max();
    }
    
    if (lane->Q1->StatDT.Number() > 0)
    {
        avgWaitTime = lane->Q1->StatDT.MeanValue();
        maxWaitTime = lane->Q1->StatDT.Max();
    }    
    
    std::string spaceFiller = getFillSpaces(lane->Name(), 16);
    cout << "| " << lane->Name() << spaceFiller << "| ";

        printf ("%7.1f | %7.f | %9.1f | %9.1f |\n", 
            avgQueueLen, maxQueueLen, avgWaitTime , maxWaitTime);
}

/**
 * Vypocet statistiky cele krizovatky (prumer ze vsech proudu).
 * 
 * @return statistika krizovatky
 */
Crossroad::Stats Crossroad::getTotalAvgStats()
{
    double avgQueueLen = 0.0;
    double maxQueueLen = 0.0;
    
    double avgWaitTime = 0.0;
    double maxWaitTime = 0.0;
    
    for (Lane* lane: lanes)
    {
        if (lane->Q1->StatN.Number() > 0)
        {
            avgQueueLen += lane->Q1->StatN.MeanValue();
            
            
            if (lane->Q1->StatN.Max() > maxQueueLen)
            {
                maxQueueLen = lane->Q1->StatN.Max();
            }
//            maxQueueLen += lane->Q1->StatN.Max();
        }

        if (lane->Q1->StatDT.Number() > 0)
        {
            avgWaitTime += lane->Q1->StatDT.MeanValue();
            
            if (lane->Q1->StatDT.Max() > maxWaitTime)
            {
                maxWaitTime = lane->Q1->StatDT.Max();
            }
//            maxWaitTime += lane->Q1->StatDT.Max();
        }    
    }

    avgQueueLen /= lanes.size();
    avgWaitTime /= lanes.size();
    
//    maxQueueLen /= lanes.size();
//    maxWaitTime /= lanes.size();
    
    return Crossroad::Stats(phasing, avgQueueLen, maxQueueLen, avgWaitTime, maxWaitTime);
}

/**
 * Tisk statistik cele krizovatky (prumer ze vsech proudu).
 * 
 * @param lanes prudy.
 */
void Crossroad::printTotalAvgStats(std::vector<Lane*> lanes)
{
    Crossroad::Stats s = getTotalAvgStats();
    
    printf ("| Total average   | %7.1f | %7.f | %9.1f | %9.1f |\n", 
        s.avgQueueLen, s.maxQueueLen, s.avgWaitTime, s.maxWaitTime);
}

/**
 * Tiska statistik.
 */
void Crossroad::printStats()
{
    std::string phasingType = phasing == Phasing::Sequential ? "Sequential" : "Fuzzy     ";
    
    cout << "+-----------------+-------------------+-----------------------+" << endl; 
    cout << "| Control:        |    Queue length   |      Waiting time     |" << endl; 
    cout << "| " << phasingType << "      |   avg   |   max   |    avg    |    max    |" << endl; 
    cout << "+-----------------+---------+---------+-----------+-----------+" << endl;
    
    for (Lane* lane: lanes)
    {
        printLaneStats(lane);
    }
    
    cout << "+-----------------+---------+---------+-----------+-----------+" << endl;
    
    printTotalAvgStats(lanes);
    
    cout << "+-----------------+---------+---------+-----------+-----------+" << endl << endl;
}

// -----------------------------------------------------------------------------
// -  NextCrossroadPhase
// -----------------------------------------------------------------------------

/**
 * Konstrukce generatoru vypoctu novych fazi.
 * 
 * @param crossroad krizovatka
 */
Crossroad::NextCrossroadPhase::NextCrossroadPhase(Crossroad* crossroad)
    : crossroad(crossroad)
{
}

/**
 * Definice chovani generatoru.
 */
void Crossroad::NextCrossroadPhase::Behavior()
{
    if (crossroad->getNewPhase() == FuzzyControl::EXTEND_PHASE)
    {
        // Prodlouzeni aktualni faze 
        Activate(Time + PHASE_TIME_EXTEND);
    }
    else
    {
        Activate(Time + PHASE_TIME_BASE);
    }
}

// -----------------------------------------------------------------------------
// -  Printer
// -----------------------------------------------------------------------------

Crossroad::Printer::Printer(Crossroad* crossroad)
    : crossroad(crossroad)
{
    interval = 20;
}

void Crossroad::Printer::Behavior()
{
    crossroad->printAverageLaneQueueSize();
    Activate(Time + interval);
}
