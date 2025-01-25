//
// Created by Olcay Taner Yıldız on 1.03.2019.
//

#include <XmlDocument.h>
#include "FiniteStateMachine.h"

/**
 * Constructor reads the finite state machine in the given input file. It has a NodeList which holds the states
 * of the nodes and there are 4 different type of nodes; stateNode, root Node, transitionNode and withNode.
 * Also there are two states; state that a node currently in and state that a node will be in.
 * <p>
 * DOMParser is used to parse the given file. Firstly it gets the document to parse, then gets its elements by the
 * tag names. For instance, it gets states by the tag name 'state' and puts them into an ArrayList called stateList.
 * Secondly, it traverses this stateList and gets each Node's attributes. There are three attributes; name, start,
 * and end which will be named as states. If a node is in a startState it is tagged as 'yes', otherwise 'no'.
 * Also, if a node is in a startState, additional attribute will be fetched; originalPos that represents its original
 * part of speech.
 * <p>
 * At the last step, by starting rootNode's first child, it gets all the transitionNodes and next states called toState,
 * then continue with the nextSiblings. Also, if there is no possible toState, it prints this case and the causative states.
 *
 * @param fileName the resource file to read the finite state machine. Only files in resources folder are supported.
 */
FiniteStateMachine::FiniteStateMachine(const string& fileName) {
    State state, toState;
    XmlElement *stateListNode, *stateNode, *transitionNode, *withNode;
    XmlDocument xmlDocument(fileName);
    xmlDocument.parse();
    stateListNode = xmlDocument.getFirstChild();
    stateNode = stateListNode->getFirstChild();
    while (stateNode != nullptr) {
        if (stateNode->hasAttributes()) {
            string stateName = stateNode->getAttributeValue("name");
            string startState = stateNode->getAttributeValue("start");
            string endState = stateNode->getAttributeValue("end");
            if (startState == "yes") {
                string originalPos = stateNode->getAttributeValue("originalpos");
                state = State(stateName, true, endState == "yes", originalPos);
            } else {
                state = State(stateName, false, endState == "yes");
            }
            states.push_back(state);
        }
        stateNode = stateNode->getNextSibling();
    }
    stateNode = stateListNode->getFirstChild();
    while (stateNode != nullptr){
        if (stateNode->hasAttributes()){
            string stateName = stateNode->getAttributeValue("name");
            state = getState(stateName);
            transitionNode = stateNode->getFirstChild();
            while (transitionNode != nullptr){
                if (transitionNode->hasAttributes()){
                    string toStateName = transitionNode->getAttributeValue("name");
                    toState = getState(toStateName);
                    string withName = transitionNode->getAttributeValue("transitionname");
                    string rootToPos = transitionNode->getAttributeValue("topos");
                    withNode = transitionNode->getFirstChild();
                    while (withNode != nullptr){
                        string toPos;
                        if (withNode->hasAttributes()){
                            withName = withNode->getAttributeValue("name");
                            toPos = withNode->getAttributeValue("topos");
                        } else {
                            toPos = "";
                        }
                        if (toPos.empty()){
                            if (rootToPos.empty()){
                                addTransition(state, toState, withNode->getPcData(), withName);
                            } else {
                                addTransition(state, toState, withNode->getPcData(), withName, rootToPos);
                            }
                        } else {
                            addTransition(state, toState, withNode->getPcData(), withName, toPos);
                        }
                        withNode = withNode->getNextSibling();
                    }
                }
                transitionNode = transitionNode->getNextSibling();
            }
        }
        stateNode = stateNode->getNextSibling();
    }
}

/**
 * The isValidTransition loops through states ArrayList and checks transitions between states. If the actual transition
 * equals to the given transition input, method returns true otherwise returns false.
 *
 * @param transition is used to compare with the actual transition of a state.
 * @return true when the actual transition equals to the transition input, false otherwise.
 */
bool FiniteStateMachine::isValidTransition(const string& transition) const {
    for (const auto& state : transitions) {
        for (const Transition& transition1 : state.second) {
            if (!transition1.to_String().empty() && transition1.to_String() == transition) {
                return true;
            }
        }
    }
    return false;
}

/**
 * The getState method is used to loop through the states ArrayList and return the state whose name equal
 * to the given input name.
 *
 * @param name is used to compare with the state's actual name.
 * @return state if found any, null otherwise.
 */
State FiniteStateMachine::getState(const string& name) const{
    for (State state : states) {
        if (state.getName() == name) {
            return state;
        }
    }
    return State();
}

/**
 * The addTransition method creates a new Transition with given input parameters and adds the transition to
 * transitions ArrayList.
 *
 * @param fromState  State type input indicating the next state.
 * @param toState  State type input indicating the next state.
 * @param with     String input indicating with what the transition will be made.
 * @param withName String input.
 */
void FiniteStateMachine::addTransition(const State& fromState, const State& toState, const string& with, const string& withName) {
    vector<Transition> transitionList;
    Transition newTransition = Transition(toState, with, withName);
    if (transitions.contains(fromState)){
        transitionList = transitions.find(fromState)->second;
    }
    transitionList.emplace_back(newTransition);
    transitions.insert_or_assign(fromState, transitionList);
}

/**
 * Another addTransition method which takes additional argument; toPos and. It creates a new Transition
 * with given input parameters and adds the transition to transitions ArrayList.
 *
 * @param toState  State type input indicating the next state.
 * @param with     String input indicating with what the transition will be made.
 * @param withName String input.
 * @param toPos    String input.
 */
void FiniteStateMachine::addTransition(const State& fromState, const State& toState, const string& with, const string& withName, const string& toPos) {
    vector<Transition> transitionList;
    Transition newTransition = Transition(toState, with, withName, toPos);
    if (transitions.contains(fromState)){
        transitionList = transitions.find(fromState)->second;
    }
    transitionList.emplace_back(newTransition);
    transitions.insert_or_assign(fromState, transitionList);
}

/**
 * The getTransitions method returns the transitions at the given state.
 *
 * @param state State input.
 * @return transitions at given state.
 */
vector<Transition> FiniteStateMachine::getTransitions(const State& state) const{
    vector<Transition> transitionList;
    if (transitions.contains(state)){
        return transitions.find(state)->second;
    } else {
        return transitionList;
    }
}

/**
 * the getStates method returns the states in the FiniteStateMachine.
 * @return StateList.
 */
vector<State> FiniteStateMachine::getStates() const{
    return states;
}
