//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "Transition.h"

/**
 * A constructor of {@link Transition} class which takes  a {@link State}, and two {@link String}s as input. Then it
 * initializes toState, with and withName variables with given inputs.
 *
 * @param toState  {@link State} input.
 * @param with     String input.
 * @param withName String input.
 */
Transition::Transition(State toState, string with, string withName) {
    this->toState = move(toState);
    this->with = move(with);
    this->withName = move(withName);
    toPos = "";
}

/**
 * Another constructor of {@link Transition} class which takes  a {@link State}, and three {@link String}s as input. Then it
 * initializes toState, with, withName and toPos variables with given inputs.
 *
 * @param toState  {@link State} input.
 * @param with     String input.
 * @param withName String input.
 * @param toPos    String input.
 */
Transition::Transition(State toState, string with, string withName, string toPos) {
    this->toState = move(toState);
    this->with = move(with);
    this->withName = move(withName);
    this->toPos = move(toPos);
}

/**
 * Another constructor of {@link Transition} class which only takes a {@link String}s as an input. Then it
 * initializes toState, withName and toPos variables as null and with variable with the given input.
 *
 * @param with String input.
 */
Transition::Transition(string with) {
    withName = "";
    toPos = "";
    this->with = move(with);
}

/**
 * Getter for the toState variable.
 *
 * @return toState variable.
 */
State Transition::getToState() {
    return toState;
}

/**
 * Getter for the toPos variable.
 *
 * @return toPos variable.
 */
string Transition::getToPos() {
    return toPos;
}

/**
 * The transitionPossible method takes two {@link String} as inputs; currentSurfaceForm and realSurfaceForm. If the
 * length of the given currentSurfaceForm is greater than the given realSurfaceForm, it directly returns true. If not,
 * it takes a substring from given realSurfaceForm with the size of currentSurfaceForm. Then checks for the characters of
 * with variable.
 * <p>
 * If the character of with that makes transition is C, it returns true if the substring contains c or ç.
 * If the character of with that makes transition is D, it returns true if the substring contains d or t.
 * If the character of with that makes transition is A, it returns true if the substring contains a or e.
 * If the character of with that makes transition is K, it returns true if the substring contains k, g or ğ.
 * If the character of with that makes transition is other than the ones above, it returns true if the substring
 * contains the same character as with.
 *
 * @param currentSurfaceForm {@link String} input.
 * @param realSurfaceForm    {@link String} input.
 * @return true when the transition is possible according to Turkish grammar, false otherwise.
 */
bool Transition::transitionPossible(string currentSurfaceForm, string realSurfaceForm) {
    if (currentSurfaceForm.size() == 0 || currentSurfaceForm.size() >= realSurfaceForm.size()) {
        return true;
    }
    string searchString = realSurfaceForm.substr(0, currentSurfaceForm.size());
    for (int i = 0; i < with.size(); i++) {
        switch (with[i]) {
            case 'C':
                return searchString.find('c') != string::npos || searchString.find("ç") != string::npos;
            case 'D':
                return searchString.find('d') != string::npos || searchString.find('t') != string::npos;
            case 'c':
            case 'e':
            case 'r':
            case 'p':
            case 'l':
            case 'b':
            case 'g':
            case 'o':
            case 'm':
            case 'v':
            case 'i':
            //case 'ü':
            case 'z':
                return searchString.find(with[i]) != string::npos;
            case 'A':
                return searchString.find('a') != string::npos || searchString.find('e') != string::npos;
            case 'k':
                return searchString.find('k') != string::npos || searchString.find('g') != string::npos || searchString.find("ğ") != string::npos;
        }
    }
    return true;
}
