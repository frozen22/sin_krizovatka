/* 
 * Soubor: Rules.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#include "Rules.h"

/**
 * Operator vypisu pro fuzzy stav.
 * 
 * @param os proud
 * @param value hodnota
 * @return proud
 */
std::ostream& operator<<(std::ostream& os, const Value& value)
{
    switch (value)
    {
        case Value::Zero:   os << "Zero";   break;
        case Value::Small:  os << "Small";  break;
        case Value::Medium: os << "Medium"; break;
        case Value::Large:  os << "Large";  break;
        case Value::Top:    os << "Top";    break;
        case Value::NoDef:  os << "NoDef";  break;
    }
    
    return os;
}
