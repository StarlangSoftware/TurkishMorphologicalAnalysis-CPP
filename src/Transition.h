//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_TRANSITION_H
#define MORPHOLOGICALANALYSIS_TRANSITION_H

#include "State.h"
#include "FsmParse.h"

class Transition {
private:
    State toState;
    string with;
    string withName;
    string toPos;
    string withFirstChar() const;
    bool startWithVowelorConsonantDrops() const;
public:
    Transition(const State& toState, const string& with, const string& withName);
    Transition(const State& toState, const string& with, const string& withName, const string& toPos);
    explicit Transition(const string& with);
    State getToState() const;
    string getToPos() const;
    bool transitionPossible(const string& currentSurfaceForm, const string& realSurfaceForm) const;
    bool transitionPossible(const FsmParse& currentFsmParse) const;
    bool transitionPossible(TxtWord* root, const State& fromState) const;
    bool softenDuringSuffixation(TxtWord* root) const;
    string makeTransition(TxtWord* root, const string& stem) const;
    string makeTransition(TxtWord* root, const string& stem, const State& startState) const;
    string to_String() const;
    string getWith() const;
};


#endif //MORPHOLOGICALANALYSIS_TRANSITION_H
