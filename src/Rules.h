/* 
 * Soubor: Rules.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */


#ifndef RULES_H
#define	RULES_H

#include <vector> 
#include <iostream>

// Fuzzy ohodnoceni/hodnoty jednotlivych stavu
enum class Value
{
    Zero,
    Small,
    Medium,
    Large,
    Top,
    NoDef
};

std::ostream& operator<<(std::ostream& os, const Value& value);
    
/**
 * Kontejner pro ukladani pravidel.
 */
template<typename TRule, typename TInput, typename TOutput>
class Rules
{
    private:
        
        std::vector<TRule> rules;

    public:

        void addRule(TRule rule)
        {
            // Hledani uz vlozeneho pravidla
            for (TRule& r : rules) // reference
            {
                if (r.input == rule.input)
                {
                    // Zmena vystupu pravidla
                    r.output = rule.output;
                    return;
                }
            }

            // Pravidlo s danym vstupem jeste neexistuje
            rules.push_back(rule);
        }
        
        bool contains(TRule rule)
        {
            for (TRule r : rules)
            {
                if (r.input == rule.input && r.output == rule.output)
                {
                    return true;
                }
            }

            return false;
        }
        
        bool contains(TInput input)
        {
            for (TRule rule : rules)
            {
                if (rule.input == input)
                {
                    return true;
                }
            }

            return false;
        }
        
        
        TRule getRule(TInput input)
        {
            for (TRule rule : rules)
            {
                if (rule.input == input)
                {
                    return rule;
                }
            }

            return TRule();
        }
        
        
        TOutput getOutput(TInput input)
        {
            return getRule(input).output;
        }
        
};

#endif	/* RULES_H */
