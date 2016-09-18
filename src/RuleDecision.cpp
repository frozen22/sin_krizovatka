/* 
 * Soubor: RuleDecision.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#include "RuleDecision.h"

bool RuleDecision::Input::operator==(const Input& other)
{
    return Urgency == other.Urgency && Extend == other.Extend;
}

bool RuleDecision::Output::operator==(const Output& other)
{
    return Extend == other.Extend;
}

RuleDecision::RuleDecision()
    : input({Value::NoDef, Value::NoDef})
    , output({false})
{
        
}

RuleDecision::RuleDecision(Input input, Output output)
    : input(input)
    , output(output)
{
    
}
