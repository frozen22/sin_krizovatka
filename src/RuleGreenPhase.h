/* 
 * Soubor: RuleGreenPhase.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#ifndef RULEGREENPHASE_H
#define	RULEGREENPHASE_H

#include "Rules.h" // Value

/**
 * Struktura pro pravidla u zelene faze
 */
struct RuleGreenPhase   
{
    struct Input
    {
        Value QueeNum;
        Value FrontNum;

        bool operator==(const Input& other);
    };
    
    struct Output
    {
        Value Extend;

        bool operator==(const Output& other);
    };
    
    Input input;
    Output output;
    
    RuleGreenPhase();
    RuleGreenPhase(Input input, Output output);
    
};

#endif	/* RULEGREENPHASE_H */
