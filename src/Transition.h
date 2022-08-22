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
    string formationToCheck;
    string toPos;
    string withFirstChar();
    bool startWithVowelorConsonantDrops();
public:
    Transition(State toState, string with, string withName);
    Transition(State toState, string with, string withName, string toPos);
    explicit Transition(string with);
    State getToState();
    string getToPos();
    bool transitionPossible(string currentSurfaceForm, string realSurfaceForm);
    bool transitionPossible(FsmParse currentFsmParse);
    bool transitionPossible(TxtWord* root, State fromState);
    bool softenDuringSuffixation(TxtWord* root);
    string makeTransition(TxtWord* root, string stem);
    string makeTransition(TxtWord* root, string stem, State startState);
    string to_String();
    string getWith();
};


#endif //MORPHOLOGICALANALYSIS_TRANSITION_H
