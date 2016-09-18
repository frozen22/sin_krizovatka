/* 
 * Soubor: main.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-19
 */

#include "simlib.h"
#include "Parameters.h"
#include "Crossroad.h"
#include "Debug.h"

/**
 * Simulace rizeni krizovatky.
 * 
 * @param phasing zpusob rizeni krizovatky
 * @return statistiky
 */
Crossroad::Stats simulate(Crossroad::Phasing phasing)
{
    if (Param::instance().seedNumber || Param::instance().seedTime)
    {
        RandomSeed(Param::instance().seed);
    }
    
    Init(0, Param::instance().timeEnd);

    Crossroad crossroad;
    crossroad.setPhasing(phasing);
    crossroad.activate();

    Run();

    crossroad.printStats();
    return crossroad.getTotalAvgStats();
}

int main(int argc, char** argv)
{
    if (!Param::instance().process(argc, argv))
    {
        return EXIT_FAILURE;
    }
    
    if (Param::instance().help)
    {
        Param::instance().printHelp();
        return EXIT_SUCCESS;
    }
    
    Param::instance().print();
    
    Crossroad::Stats statsFuzzy;
    Crossroad::Stats statsSequential;
    
    if (Param::instance().sequentialControl)
    {
        statsSequential = simulate(Crossroad::Phasing::Sequential);
    }

    if (Param::instance().fuzzyControl)
    {
        statsFuzzy = simulate(Crossroad::Phasing::Fuzzy);
    }
    
    if (Param::instance().sequentialControl && Param::instance().fuzzyControl)
    {
        Crossroad::printComparedStats({statsSequential, statsFuzzy});
    }
    
    if (Param::instance().waitForInput)
    {
        std::cerr << "Press any key and enter to exit.";
        int i;
        std::cin >> i;
    }

    return EXIT_SUCCESS;
}