/* 
 * Soubor: FuzzyControl.cpp
 * Autor:  Frantisek Nemec (xnemec61@stud.fit.vutbr.cz)
 *         Jan Opalka      (xopalk01@stud.fit.vutbr.cz)
 * Datum:  2015-11-30
 */

#include <map>

#include "FuzzyControl.h"
#include "Debug.h"

Fuzzified::Fuzzified(Value firstValue, double firstDegree, Value secondValue, double secondDegree)
{    
    value[0] = firstValue;
    degree[0] = firstDegree;
    value[1] = secondValue;
    degree[1] = secondDegree;
}

/**
 * Ulozeni informace o fuzzifikaci.
 */
void Fuzzified::setValue(Value value, double degree)
{
    //je obsazen prvni slot?
    if (this->degree[0] == 0.0)
    {
        this->value[0] = value;
        this->degree[0] = degree;
    }
    else
    {
        this->value[1] = value;
        this->degree[1] = degree;
    }
}

/**
 * Konstrukce fuzzy kontroleru.
 */
FuzzyControl::FuzzyControl() 
{
    createRules();
}

/**
 * Vytvoreni pravidel pro rozhodovani.
 */
void FuzzyControl::createRules() 
{
    //======================================================================
    //                  Pravidla pro následující fázi
    //======================================================================

    redRules.addRule(RuleNextPhase({Value::Small, Value::Small, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Small, Value::Medium}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Small, Value::Large}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Small, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Small, Value::Medium, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Medium, Value::Medium}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Medium, Value::Large}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Medium, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Small, Value::Large, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Large, Value::Medium}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Large, Value::Large}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Small, Value::Large, Value::Top}, {Value::Top}));

    //======================================================================

    redRules.addRule(RuleNextPhase({Value::Medium, Value::Small, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Small, Value::Medium}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Small, Value::Large}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Small, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Medium, Value::Medium, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Medium, Value::Medium}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Medium, Value::Large}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Medium, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Medium, Value::Large, Value::Small}, {Value::Small}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Large, Value::Medium}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Large, Value::Large}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Medium, Value::Large, Value::Top}, {Value::Top}));

    //======================================================================

    redRules.addRule(RuleNextPhase({Value::Large, Value::Small, Value::Small}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Small, Value::Medium}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Small, Value::Large}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Small, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Large, Value::Medium, Value::Small}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Medium, Value::Medium}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Medium, Value::Large}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Medium, Value::Top}, {Value::Top}));

    redRules.addRule(RuleNextPhase({Value::Large, Value::Large, Value::Small}, {Value::Medium}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Large, Value::Medium}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Large, Value::Large}, {Value::Large}));
    redRules.addRule(RuleNextPhase({Value::Large, Value::Large, Value::Top}, {Value::Top}));

    //======================================================================
    //                  Pravidla pro zelenou fázi
    //======================================================================

    greenRules.addRule(RuleGreenPhase({Value::Zero, Value::Zero}, {Value::Zero}));
    greenRules.addRule(RuleGreenPhase({Value::Small, Value::Zero}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Medium, Value::Zero}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Large, Value::Zero}, {Value::Medium}));

    greenRules.addRule(RuleGreenPhase({Value::Zero, Value::Small}, {Value::Zero}));
    greenRules.addRule(RuleGreenPhase({Value::Small, Value::Small}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Medium, Value::Small}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Large, Value::Small}, {Value::Medium}));

    greenRules.addRule(RuleGreenPhase({Value::Zero, Value::Medium}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Small, Value::Medium}, {Value::Small}));
    greenRules.addRule(RuleGreenPhase({Value::Medium, Value::Medium}, {Value::Medium}));
    greenRules.addRule(RuleGreenPhase({Value::Large, Value::Medium}, {Value::Large}));

    greenRules.addRule(RuleGreenPhase({Value::Zero, Value::Large}, {Value::Medium}));
    greenRules.addRule(RuleGreenPhase({Value::Small, Value::Large}, {Value::Medium}));
    greenRules.addRule(RuleGreenPhase({Value::Medium, Value::Large}, {Value::Large}));
    greenRules.addRule(RuleGreenPhase({Value::Large, Value::Large}, {Value::Large}));

    greenRules.addRule(RuleGreenPhase({Value::Zero, Value::Top}, {Value::Large}));
    greenRules.addRule(RuleGreenPhase({Value::Small, Value::Top}, {Value::Large}));
    greenRules.addRule(RuleGreenPhase({Value::Medium, Value::Top}, {Value::Top}));
    greenRules.addRule(RuleGreenPhase({Value::Large, Value::Top}, {Value::Top}));

    //======================================================================
    //               Pravidla pro rozhodování o prodloužení
    //     parametry: naléhavosti další fáze, prodloužení další fáze
    //   výstup: rozhodnutí o prodloužení (true) nebo změně fáze (false)
    // při stejné příslušnosti k fuzzy množině se upřednostňuje změna fáze 
    //======================================================================

    decisionBlock.addRule(RuleDecision({Value::Zero, Value::Zero},  {false}));
    decisionBlock.addRule(RuleDecision({Value::Small, Value::Zero}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Medium, Value::Zero},{false}));
    decisionBlock.addRule(RuleDecision({Value::Large, Value::Zero}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Top, Value::Zero},   {false}));

    decisionBlock.addRule(RuleDecision({Value::Zero, Value::Small},  {true}));
    decisionBlock.addRule(RuleDecision({Value::Small, Value::Small}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Medium, Value::Small},{false}));
    decisionBlock.addRule(RuleDecision({Value::Large, Value::Small}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Top, Value::Small},   {false}));

    decisionBlock.addRule(RuleDecision({Value::Zero, Value::Medium},  {true}));
    decisionBlock.addRule(RuleDecision({Value::Small, Value::Medium}, {true}));
    decisionBlock.addRule(RuleDecision({Value::Medium, Value::Medium},{false}));
    decisionBlock.addRule(RuleDecision({Value::Large, Value::Medium}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Top, Value::Medium},   {false}));

    decisionBlock.addRule(RuleDecision({Value::Zero, Value::Large},  {true}));
    decisionBlock.addRule(RuleDecision({Value::Small, Value::Large}, {true}));
    decisionBlock.addRule(RuleDecision({Value::Medium, Value::Large},{true}));
    decisionBlock.addRule(RuleDecision({Value::Large, Value::Large}, {false}));
    decisionBlock.addRule(RuleDecision({Value::Top, Value::Large},   {false}));

    decisionBlock.addRule(RuleDecision({Value::Zero, Value::Top},  {true}));
    decisionBlock.addRule(RuleDecision({Value::Small, Value::Top}, {true}));
    decisionBlock.addRule(RuleDecision({Value::Medium, Value::Top},{true}));
    decisionBlock.addRule(RuleDecision({Value::Large, Value::Top}, {true}));
    decisionBlock.addRule(RuleDecision({Value::Top, Value::Top},   {false}));

    //======================================================================
    //                Konec sekce pravidel pro rozhodování
    //======================================================================
}

/**
 * Fuzzifikace poctu aut
 * 
 * @param carCount pocet aut
 * @return fuzzy mnoziny vznikle pri fuzzifikaci poctu aut pouzite krivky tvaru A
 */
Fuzzified FuzzyControl::fuzzifyCarCount(double carCount)
{
    Fuzzified fCarCount = Fuzzified(Value::NoDef,0.,Value::NoDef,0.); 
    
    double thresholdS = 8.0;            // thresholdSmall
    double thresholdM = thresholdS * 2; // thresholdMedium
    double thresholdL = thresholdS * 3; // thresholdLarge
    
    if(carCount >= 0 && carCount <= thresholdS)
        fCarCount.setValue(Value::Small,std::max((thresholdS-carCount)/thresholdS,0.));
    if(carCount > 0 && carCount <= thresholdM)
        fCarCount.setValue(Value::Small,std::max(std::min((carCount-0)/(thresholdS-0),(thresholdM-carCount)/(thresholdM-thresholdS)),0.));
    if(carCount > thresholdS && carCount <= thresholdL)
        fCarCount.setValue(Value::Medium,std::max(std::min((carCount-thresholdS)/(thresholdM-thresholdS),(thresholdL-carCount)/(thresholdL-thresholdM)),0.));
    if(carCount > thresholdM && carCount <= thresholdL)
        fCarCount.setValue(Value::Large,std::max((carCount-thresholdM)/(thresholdL-thresholdM),0.));
    if(carCount > thresholdL)
        fCarCount.setValue(Value::Large,1.);

    return fCarCount;
}

/**
 * Fuzzifikace poctu aut jedoucich rovne.
 * 
 * @param carCount pocet aut
 * @param carCountForward pocet aut jedoucich vpred
 * @return fuzzy mnoziny vznikle pri fuzzifikaci pomeru carCount/carCountForward
 * pouzite krivky tvaru A
 */
Fuzzified FuzzyControl::fuzzifyCarCountForward(double carCount, double carCountForward)
{
    Fuzzified fCarCountForward = Fuzzified(Value::NoDef,0.,Value::NoDef,0.);
    double forwardRatio = 0.;
    
    if(carCount)
         forwardRatio = carCountForward/carCount;
    if(forwardRatio >= 0. && forwardRatio <= 0.15)
        fCarCountForward.setValue(Value::Small,std::max((0.15-forwardRatio)/0.15,0.));
    if(forwardRatio > 0. && forwardRatio <= 0.3)
        fCarCountForward.setValue(Value::Small,std::max(std::min((forwardRatio-0)/(0.15-0),(0.3-forwardRatio)/(0.3-0.15)),0.));
    if(forwardRatio > 0.15 && forwardRatio <= 0.45)
        fCarCountForward.setValue(Value::Medium,std::max(std::min((forwardRatio-0.15)/(0.3-0.15),(0.45-forwardRatio)/(0.45-0.3)),0.));
    if(forwardRatio > 0.3 && forwardRatio <= 0.45)
        fCarCountForward.setValue(Value::Large,std::max((forwardRatio-0.3)/(0.45-0.3),0.));
    if(forwardRatio > 0.45)
        fCarCountForward.setValue(Value::Large,1.);

    return fCarCountForward;
}

/**
 * Fuzzifikace casu cekajicich aut.
 * 
 * @param carWaitingTime cas cekani vozidel
 * @return fuzzy mnoziny vznikle pri fuzzifikaci pomeru casu cekani pouzite 
 * krivky tvaru A
 */
Fuzzified FuzzyControl::fuzzifyCarWaitingTime(double carWaitingTime)
{
    Fuzzified fCarWaitingTime = Fuzzified(Value::NoDef,0.,Value::NoDef,0.); 
    
    double thresholdS = 90.0;
    double thresholdM = thresholdS * 2;
    double thresholdL = thresholdS * 3;
    double thresholdT = thresholdS * 4;
    
    if(carWaitingTime >= 0. && carWaitingTime <= thresholdS)
        fCarWaitingTime.setValue(Value::Small,std::max((thresholdS-carWaitingTime)/thresholdS,0.));
    if(carWaitingTime > 0. && carWaitingTime <= thresholdM)
        fCarWaitingTime.setValue(Value::Small,std::max(std::min((carWaitingTime-0)/thresholdS,(thresholdM-carWaitingTime)/thresholdS),0.));
    if(carWaitingTime > thresholdS && carWaitingTime <= thresholdL)
        fCarWaitingTime.setValue(Value::Medium,std::max(std::min((carWaitingTime-thresholdS)/thresholdS,(thresholdL-carWaitingTime)/thresholdS),0.));
    if(carWaitingTime > thresholdM && carWaitingTime <= thresholdT)
        fCarWaitingTime.setValue(Value::Large,std::max(std::min((carWaitingTime-thresholdM)/thresholdS,(thresholdT-carWaitingTime)/thresholdS),0.));
    if(carWaitingTime > thresholdL && carWaitingTime <= thresholdT)
        fCarWaitingTime.setValue(Value::Top,std::max((carWaitingTime-thresholdL)/thresholdS,0.));
    if(carWaitingTime > thresholdT)
        fCarWaitingTime.setValue(Value::Top,1.);
    
    return fCarWaitingTime;
}

/**
 * Fuzzy inference pro cervene faze
 * 
 * @param fCarCount fuzzifikovany pocet aut
 * @param fCarCountForward fuzzifikovany pocet aut jedoucich vpred
 * @param fCarWaitingTime fuzzifikovany cas cekani
 * @return fuzzy inference pouzitych pravidel
 */
std::map<Value, double> FuzzyControl::inferenceRedPhase(Fuzzified fCarCount, Fuzzified fCarCountForward, Fuzzified fCarWaitingTime)
{
    std::map<Value, double> affiliations;
    affiliations[Value::Small] = 0.0;
    affiliations[Value::Medium] = 0.0;
    affiliations[Value::Large] = 0.0;
    affiliations[Value::Top] = 0.0;

    //vypocet vystupni fuzzy mn-y pro fazi na semaforu (fuzzy interference) 
    //optimalizace: z mn-y se vybira nejvice zastoupena nejvyssi priorita -> priorita pro cervenou fazi  
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                bool isDef = fCarCount.value[i] != Value::NoDef 
                             && fCarCountForward.value[j] != Value::NoDef
                             && fCarWaitingTime.value[k] != Value::NoDef; 
                if(isDef) {
                    //vyber nejvyssi stejné priority >= (pokud by nastalo)
                    double urgencyDegree = std::min(std::min(fCarCount.degree[i],fCarCountForward.degree[j]),fCarWaitingTime.degree[k]); 
                    Value urgency = redRules.getOutput({fCarCount.value[i], fCarCountForward.value[j], fCarWaitingTime.value[k]}).Urgency;
                    affiliations[urgency] = std::max(urgencyDegree, affiliations[urgency]);
                }       
            }
        }
    }

    return affiliations;
}

/**
 * Fuzzy inference pro zelene faze
 * 
 * @param fCarCountActive fuzzifikovany pocet aut
 * @param fCarWaitingTimeActive fuzzifikovany cas cekani
 * @return fuzzy inference pouzitych pravidel
 */
std::map<Value, double> FuzzyControl::inferenceActivatePhase(Fuzzified fCarCountActive, Fuzzified fCarWaitingTimeActive)
{
    std::map<Value, double> affiliationsGreen;
    affiliationsGreen[Value::Small] = 0.0;
    affiliationsGreen[Value::Medium] = 0.0;
    affiliationsGreen[Value::Large] = 0.0;
    affiliationsGreen[Value::Top] = 0.0;
    
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            bool isDef = fCarCountActive.value[i] != Value::NoDef
                         && fCarWaitingTimeActive.value[j] != Value::NoDef; 
            if(isDef) {
                //vyber nejvyssi stejné priority >= (pokud by nastalo)
                double urgencyDegree = std::min(fCarCountActive.degree[i], fCarWaitingTimeActive.degree[j]); 
                Value urgency = greenRules.getOutput({fCarCountActive.value[i], fCarWaitingTimeActive.value[j]}).Extend;
                affiliationsGreen[urgency] = std::max(urgencyDegree, affiliationsGreen[urgency]);
            }       
        }
    }
    
    return affiliationsGreen;
}

/**
 * Fuzzy inference pro rozhodnuti o prodlouzeni zelene faze
 * 
 * @param affiliationsRed fuzzy inference nejuspesnejsi cervene faze
 * @param affiliationsGreen fuzzy interference rozhodujici o prodlouzeni zelene faze
 * @return fuzzy inference pouzitych pravidel
 */
std::map<bool, double> FuzzyControl::inferenceDecision(std::map<Value, double> affiliationsRed,
                                                       std::map<Value, double> affiliationsGreen)
{
    std::map<bool, double> affiliationsExtend;
    affiliationsExtend[true] = 0.0;
    affiliationsExtend[false] = 0.0;
    
    for(int i = (int)Value::Small; i <= (int)Value::Top; i++)
    {
        for (int j = (int)Value::Small; j <= (int)Value::Top; j++)
        {
            double extendDegree = std::min(affiliationsRed[(Value)i], affiliationsGreen[(Value)j]);
            bool extend = decisionBlock.getOutput({(Value)i, (Value)j}).Extend;
            affiliationsExtend[extend] = std::max(extendDegree, affiliationsExtend[extend]);
        }
    }
    
    return affiliationsExtend;
}

/**
 * Ziskani indexu nove faze.
 * 
 * @param crossroadPhases mozne faze
 * @param activePhaseIndex aktualni faze
 * @return index nove faze
 */
int FuzzyControl::makeDecision(const std::vector<CrossroadPhase>& crossroadPhases, int activePhaseIndex)
{
    int nextCrossroadPhase = EXTEND_PHASE;
    double phaseTopDegree = 0.0;
    
    std::map<Value, double> affiliationsRed;
    
    //Fuzzifikace vstupnich promennych pro cervene faze
    // pouzity A tvary/krivky pro fuzzy mnoziny
    // maximálně 2 fuzzy mn-y pro jednu ostrou vstupni hodnotu
    for (int i = 0; i < (int)crossroadPhases.size(); i++)
    {
        if (i == activePhaseIndex)
        {
            continue;
        }
        
        CrossroadPhase phase = crossroadPhases[i];
        
        // fuzzyfikace pro atributy cervene faze
        Fuzzified fCarCount = fuzzifyCarCount(phase.getCarCount());
        Fuzzified fCarCountForward = fuzzifyCarCountForward(phase.getCarCount(), phase.getCarCountForward());
        Fuzzified fCarWaitingTime = fuzzifyCarWaitingTime(phase.getCarWaitingTime());
        
        std::map<Value, double> affiliations = inferenceRedPhase(fCarCount, fCarCountForward, fCarWaitingTime);
        
        double result = 0.0;
        double resultDiv = 0.0;
        for (auto affiliation : affiliations)
        {
            result += affiliation.second * (int)affiliation.first;
            resultDiv += affiliation.second; 
        }
        result /= resultDiv;
        
        if (result > phaseTopDegree)
        {
            affiliationsRed = affiliations;
            phaseTopDegree = result;
            nextCrossroadPhase = i;
        }
    } //konec pro for pres phases
    
    // fuzzyfikace pro atributy zelene fazi
    CrossroadPhase activePhase = crossroadPhases[activePhaseIndex];
    Fuzzified fCarCountActive = fuzzifyCarCount(activePhase.getCarCount());
    Fuzzified fCarWaitingTimeActive = fuzzifyCarWaitingTime(activePhase.getCarWaitingTime());

    // fuzzy inference
    std::map<Value, double> affiliationsGreen = inferenceActivatePhase(fCarCountActive, fCarWaitingTimeActive);
    std::map<bool, double> affiliationsExtend = inferenceDecision(affiliationsRed, affiliationsGreen);
    
    // "defuzzyfikace" vysledku - porovnání velikosti prislusnosti k prodlouzeni/neprodlouzeni
    bool extendPhase = affiliationsExtend[true] > affiliationsExtend[false];
    return extendPhase ? EXTEND_PHASE : nextCrossroadPhase;
}
