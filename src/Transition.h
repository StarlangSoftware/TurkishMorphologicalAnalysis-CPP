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
    [[nodiscard]] string withFirstChar() const;
    [[nodiscard]] bool startWithVowelorConsonantDrops() const;
public:
    Transition(const State& toState, const string& with, const string& withName);
    Transition(const State& toState, const string& with, const string& withName, const string& toPos);
    explicit Transition(const string& with);
    [[nodiscard]] State getToState() const;
    [[nodiscard]] string getToPos() const;
    [[nodiscard]] bool transitionPossible(const string& currentSurfaceForm, const string& realSurfaceForm) const;
    [[nodiscard]] bool transitionPossible(const FsmParse& currentFsmParse) const;
    bool transitionPossible(const TxtWord* root, const State& fromState) const;
    bool softenDuringSuffixation(const TxtWord* root, const State& startState) const;
    string makeTransition(TxtWord* root, const string& stem) const;
    string makeTransition(TxtWord* root, const string& stem, const State& startState) const;
    [[nodiscard]] string to_String() const;
    [[nodiscard]] string getWith() const;
};


#endif //MORPHOLOGICALANALYSIS_TRANSITION_H
