/* 
 * Soubor: FuzzyControl.h
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#ifndef FUZZYCONTROL_H
#define	FUZZYCONTROL_H

#include "Rules.h"
#include "CrossroadPhase.h"
#include "RuleGreenPhase.h"
#include "RuleNextPhase.h"
#include "RuleDecision.h"

struct Fuzzified
{ 
    Value value[2];
    double degree[2];
    
    Fuzzified(Value firstValue, double firstDegree, Value secondValue, double secondDegree);
    void setValue(Value value, double degree);
};

/**
 * Trida fuzzy kontroleru
 */
class FuzzyControl
{
    public:
        
        // Konstanta definujicic prodlouzeni aktualni faze
        static const int EXTEND_PHASE = -1;
        
    private:

        // Fuzzy pravidla
        Rules<RuleNextPhase, RuleNextPhase::Input, RuleNextPhase::Output> redRules;
        Rules<RuleGreenPhase, RuleGreenPhase::Input, RuleGreenPhase::Output> greenRules;
        Rules<RuleDecision, RuleDecision::Input, RuleDecision::Output> decisionBlock;

    public:

        FuzzyControl();

        int makeDecision(const std::vector<CrossroadPhase>& crossroadPhases, int activePhaseIndex);

    private:

        void createRules();

        Fuzzified fuzzifyCarCount(double carCount);
        Fuzzified fuzzifyCarCountForward(double carCount, double carCountForward);
        Fuzzified fuzzifyCarWaitingTime(double carWaitingTime);

        std::map<Value, double> inferenceRedPhase(Fuzzified fCarCount, Fuzzified fCarCountForward, Fuzzified fCarWaitingTime); 
        std::map<Value, double> inferenceActivatePhase(Fuzzified fCarCountActive, Fuzzified fCarWaitingTimeActive);
        std::map<bool, double> inferenceDecision(std::map<Value, double> affiliationsRed, std::map<Value, double> affiliationsGreen);

};

#endif	/* FUZZYCONTROL_H */
