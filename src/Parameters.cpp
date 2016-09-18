/* 
 * Soubor: Parameters.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-20
 */

#include "Parameters.h"

#include <ctime>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using std::cout;
using std::endl;

/**
 * Konstruktor;
 */
Param::Param()
{
    fuzzyControl = false;
    sequentialControl = false;
    seedTime = false;
    seedNumber = false;
    seed = 0;
    timeEnd = -1;
    experiment = -1;
    waitForInput = false;
    printCrossroadStates = false;
    help = false;
}

/**
 * Ziskani instance singleton tridy;
 * 
 * @return Param instance
 */
Param& Param::instance()
{
    static Param instance;
    return instance;
}

/**
 * Zpracovani vstupnich argumentu programu.
 * 
 * @param argc pocet argumentu
 * @param argv argumenty
 * @return false - spatne argumenty
 */
bool Param::process(int argc, char** argv)
{
    opterr = 0;
    int c;
    while ((c = getopt(argc, argv, "fsr:tz:e:ich")) != -1)
    {
        switch (c)
        {
            case 'f':
                Param::instance().fuzzyControl = true;
                break;
            case 's':
                Param::instance().sequentialControl = true;
                break;
            case 'r':
                Param::instance().seedNumber = true;
                Param::instance().seed = std::stoi(std::string(optarg));
                break;
            case 't':
                Param::instance().seedTime = true;
                break;
            case 'z':
                Param::instance().timeEnd = std::stoi(std::string(optarg));
                break;
            case 'e':
                Param::instance().experiment = std::stoi(std::string(optarg));
                break;
            case 'i':
                Param::instance().waitForInput = true;
                break;
            case 'c':
                Param::instance().printCrossroadStates = true;
                break;
            case 'h':
                Param::instance().help = true;
                break;
            case '?':
                if (optopt == 'r')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (optopt == 'z')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (optopt == 'e')
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr,
                        "Unknown option character `\\x%x'.\n",
                        optopt);
                printHelp();
                return false;
            default:
                abort();
        }
    }
    
    if (Param::instance().experiment == 0)
    {
        fprintf(stderr, "Option -e (experiment) allows only value 1 or 2.\n");
        printHelp();
        return false;
    }
    
    postProcess();
    return true;
}

/**
 * Zpracovani parametru;
 */
void Param::postProcess()
{
    if (!fuzzyControl && !sequentialControl)
    {
        fuzzyControl = true;
        sequentialControl = true;
    }

    if (!seedNumber && seedTime)
    {
        seed = time(0);
    }
    
    if (experiment == -1)
    {
        experiment = 1;
    }
    
    if (timeEnd == -1)
    {
        timeEnd = 3 HODINA;
    }
}

/**
 * Vypocet poctu cifer cisla.
 * 
 * @param i cislo
 * @return pocet cifer
 */
int Param::charCount(int i)
{
    double d = i;
    int chars = 0;
    
    while (d >= 1)
    {
        chars++;
        d /= 10;
    }
    
    return chars;
}

/**
 * Vytvoreni daneho poctu mezer;
 * 
 * @param spaceCount pocet mezer
 * @return retezec mezer
 */
std::string Param::getSpaces(int spaceCount)
{
    std::string spaces;
    
    for (int i = 0; i < spaceCount; i++)
    {
        spaces += " ";
    }
    
    return spaces;
}

/**
 * Tisk parametru na standardni vystup.
 */
void Param::print()
{
    cout << "+-------------------------------------------------------------+" << endl; 
    cout << "| Parameters:                                                 |" << endl;
    
    if (seedNumber)
    {
        cout << "|    Seed: " << seed << getSpaces(51 - charCount(seed)) << "|" << endl;
    }
    else if (seedTime)
    {
        cout << "|    Seed: time                                               |" << endl;;
    }
    else
    {
        cout << "|    Seed: default                                            |" << endl;
    }
    cout << "|    Time unit: second                                        |" << endl;
    cout << "|    Time end: " << timeEnd << getSpaces(47 - charCount(timeEnd)) << "|"<< endl;
    if (experiment == 1)
    {
        cout << "|    Experiment 1:                                            |" << endl
             << "|       Forward and right lanes generate vehicles with Gauss  |" << endl
             << "|       distribution mi=15 sigma=6. Left lanes mi=30 sigma=10 |" << endl
             << "|       Time 1800-5400: north lanes generate 2x vehicles      |" << endl
             << "|       Time 5400-9000: south lanes generate 2x vehicles      |" << endl;
    }
    else if (experiment == 2)
    {
        cout << "|    Experiment 2:                                            |" << endl
             << "|       Forward and right lanes generate vehicles with Gauss  |" << endl
             << "|       distribution mi=12 sigma=4. Left lanes mi=30 sigma=10 |" << endl;
    }
    
    cout << "+-------------------------------------------------------------+" << endl << endl;
}

/**
 * Tisk napovedy
 */
void Param::printHelp()
{
    std::string helpStr = 
        "  Crossroad semaphore control with Fuzzy logic.\n"
        "\n"
        "    Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)\n"
        "    Jan Opalka      (xopalk01@stud.fit.vutbr.cz)\n"
        "\n"
        "    2015\n"
        "\n"
        "  Parameters:\n"
        "\n"
        "    -f            Fuzzy control (usable with -s)\n"
        "\n"
        "    -s            Sequential control (usable with -f)\n"
        "\n"
        "    -r VALUE      Seed\n"
        "\n"
        "    -t            Use current time as seed\n"
        "\n"
        "    -z TIME_END   Simulation end (seconds)\n"
        "\n"
        "    -e VALUE      Scenario (1 or 2)\n"
        "\n"
        "    -i            Wait for input at the end of simulation\n"
        "\n"
        "    -c            Print crossroad state every 20 seconds\n"
        "\n"
        "    -h            Print help\n"
        "\n"
        "  Default parameters:\n"
        "\n"
        "    -f -s -e 1 -z 10800\n";
    
    std::cerr << helpStr;
}
