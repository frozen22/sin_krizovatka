/* 
 * Soubor: RuleNextPhase.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#include "RuleNextPhase.h"

bool RuleNextPhase::Input::operator==(const Input& other)
{
    return QueeNum == other.QueeNum 
           && FrontNum == other.FrontNum 
           && RedTime == other.RedTime;
}

bool RuleNextPhase::Output::operator==(const Output& other)
{
    return Urgency == other.Urgency;
}

RuleNextPhase::RuleNextPhase() 
    : input({Value::NoDef, Value::NoDef, Value::NoDef})
    , output({Value::NoDef})
{
        
}

RuleNextPhase::RuleNextPhase(Input input, Output output) 
    : input(input)
    , output(output)
{
    
}
