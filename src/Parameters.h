/* 
 * Soubor: Parameters.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-20
 */

#ifndef PARAMETERS_H
#define	PARAMETERS_H

#include <string>

// Casy prijeti do krizovatky (projeti semaforu). Prvni vozidlo ma delsi 
// cas, aby se znevyhodnilo rychle prepinani semaforu a preferovaly se delsi 
// intervaly prepinani.
const int TIME_TO_CROSS_FIRST = 7; // sekundy
const int TIME_TO_CROSS_NEXT  = 4; // sekundy

// Zakladni casovou jednotkou je sekunda
#define MINUTA *60
#define HODINA *3600
#define DEN    *86400
#define TYDEN  *604800

class Param
{
    public:
        
        bool fuzzyControl;
        bool sequentialControl;
        bool seedTime;
        bool seedNumber;
        long seed;
        double timeEnd;
        int experiment;
        bool waitForInput;
        bool printCrossroadStates;
        bool help;
        
        static Param& instance();
        bool process(int argc, char** argv);
        void print();
        void printHelp();
    private:

        Param();
        
        void postProcess();
        int charCount(int i);
        std::string getSpaces(int spaceCount);
        
};

#endif	/* PARAMETERS_H */

