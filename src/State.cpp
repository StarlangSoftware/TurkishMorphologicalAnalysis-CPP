//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "State.h"

/**
 * First constructor of the State class which takes 3 parameters String name, boolean startState,
 * and boolean endState as input and initializes the private variables of the class also leaves pos as null.
 *
 * @param name       String input.
 * @param startState boolean input.
 * @param endState   boolean input.
 */
State::State(const string& name, bool startState, bool endState) {
    this->name = name;
    this->startState = startState;
    this->endState = endState;
    this->pos = "";
}

/**
 * Second constructor of the State class which takes 4 parameters as input; String name, boolean startState,
 * boolean endState, and String pos and initializes the private variables of the class.
 *
 * @param name       String input.
 * @param startState boolean input.
 * @param endState   boolean input.
 * @param pos        String input.
 */
State::State(const string& name, bool startState, bool endState, const string& pos) {
    this->name = name;
    this->startState = startState;
    this->endState = endState;
    this->pos = pos;
}

/**
 * Getter for the name.
 *
 * @return String name.
 */
string State::getName() const{
    return name;
}

/**
 * Getter for the pos.
 *
 * @return String pos.
 */
string State::getPos() const{
    return pos;
}

/**
 * The isEndState method returns endState's value.
 *
 * @return boolean endState.
 */
bool State::isEndState() const{
    return endState;
}

/**
 * Overridden toString method which  returns the name.
 *
 * @return String name.
 */
string State::to_String() const{
    return name;
}

State::State() = default;
