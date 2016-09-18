/* 
 * Soubor: RuleGreenPhase.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#include "RuleGreenPhase.h"

bool RuleGreenPhase::Input::operator==(const Input& other)
{
    return QueeNum == other.QueeNum && FrontNum == other.FrontNum;
}

bool RuleGreenPhase::Output::operator==(const Output& other)
{
    return Extend == other.Extend;
}

RuleGreenPhase::RuleGreenPhase()
    : input({Value::NoDef, Value::NoDef})
    , output({Value::NoDef})
{
        
}

RuleGreenPhase::RuleGreenPhase(Input input, Output output)
    : input(input)
    , output(output)
{
    
}
