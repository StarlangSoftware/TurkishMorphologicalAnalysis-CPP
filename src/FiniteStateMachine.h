//
// Created by Olcay Taner Yıldız on 1.03.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H
#define MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H

#include <vector>
#include <map>
#include "State.h"
#include "Transition.h"

using namespace std;

class FiniteStateMachine {
private:
    vector<State> states;
    map<State, vector<Transition>> transitions;
public:
    FiniteStateMachine() = default;
    explicit FiniteStateMachine(const string& fileName);
    bool isValidTransition(const string& transition) const;
    State getState(const string& name) const;
    vector<State> getStates() const;
    void addTransition(const State& fromState, const State& toState, const string& with, const string& withName);
    void addTransition(const State& fromState, const State& toState, const string& with, const string& withName, const string& toPos);
    vector<Transition> getTransitions(const State& state) const;
};


#endif //MORPHOLOGICALANALYSIS_FINITESTATEMACHINE_H
