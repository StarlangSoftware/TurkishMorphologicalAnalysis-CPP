//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_TRANSITION_H
#define MORPHOLOGICALANALYSIS_TRANSITION_H

#include "State.h"

class Transition {
private:
    State toState;
    string with;
    string withName;
    string formationToCheck;
    string toPos;
public:
    Transition(State toState, string with, string withName);
    Transition(State toState, string with, string withName, string toPos);
    explicit Transition(string with);
    State getToState();
    string getToPos();
    bool transitionPossible(string currentSurfaceForm, string realSurfaceForm);
};


#endif //MORPHOLOGICALANALYSIS_TRANSITION_H
