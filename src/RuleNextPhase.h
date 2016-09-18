/* 
 * Soubor: RuleNextPhase.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#ifndef RULENEXTPHASE_H
#define	RULENEXTPHASE_H

#include "Rules.h" // Value

/**
 * Pravidla pro vypocet nasledujici faze
 */
struct RuleNextPhase
{
    struct Input
    {
        Value QueeNum;
        Value FrontNum;
        Value RedTime;

        bool operator==(const Input& other);
    };
    
    struct Output
    {
        Value Urgency;

        bool operator==(const Output& other);
    };
    
    Input input;
    Output output;
    
    RuleNextPhase();
    RuleNextPhase(Input input, Output output);
};

#endif	/* RULENEXTPHASE_H */

