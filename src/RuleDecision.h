/* 
 * Soubor: RuleDecision.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#ifndef RULEDECISION_H
#define	RULEDECISION_H

#include "Rules.h" // Value

/**
 * Struktura pro pravidla pri rozhodovani o prodlouzeni zelene na aktivnim semaforu
 */
struct RuleDecision   
{
    struct Input
    {
        Value Urgency;
        Value Extend;

        bool operator==(const Input& other);
    };
    
    struct Output
    {
        bool Extend;

        bool operator==(const Output& other);
    };
    
    Input input;
    Output output;
    
    RuleDecision();
    RuleDecision(Input input, Output output);
    
};

#endif	/* RULEDECISION_H */

