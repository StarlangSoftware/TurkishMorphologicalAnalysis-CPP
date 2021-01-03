//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include "catch.hpp"
#include "../FiniteStateMachine.h"
#include <CounterHashMap.h>

TEST_CASE("FiniteStateMachineTest-testStateCount") {
    FiniteStateMachine fsm = FiniteStateMachine("turkish_finite_state_machine.xml");
    vector<State> stateList = fsm.getStates();
    REQUIRE(139 == stateList.size());
}

TEST_CASE("FiniteStateMachineTest-testStartEndStates") {
    FiniteStateMachine fsm = FiniteStateMachine("turkish_finite_state_machine.xml");
    vector<State> stateList = fsm.getStates();
    int endStateCount = 0;
    for (State state : stateList){
        if (state.isEndState()){
            endStateCount++;
        }
    }
    REQUIRE(35 == endStateCount);
    CounterHashMap<string> posCounts = CounterHashMap<string>();
    for (State state : stateList){
        posCounts.put(state.getPos());
    }
    REQUIRE(1 == posCounts["HEAD"]);
    REQUIRE(6 == posCounts["PRON"]);
    REQUIRE(1 == posCounts["PROP"]);
    REQUIRE(8 == posCounts["NUM"]);
    REQUIRE(7 == posCounts["ADJ"]);
    REQUIRE(1 == posCounts["INTERJ"]);
    REQUIRE(1 == posCounts["DET"]);
    REQUIRE(1 == posCounts["ADVERB"]);
    REQUIRE(1 == posCounts["QUES"]);
    REQUIRE(1 == posCounts["CONJ"]);
    REQUIRE(26 == posCounts["VERB"]);
    REQUIRE(1 == posCounts["POSTP"]);
    REQUIRE(1 == posCounts["DUP"]);
    REQUIRE(11 == posCounts["NOUN"]);
}

TEST_CASE("FiniteStateMachineTest-testTransitionCount") {
    FiniteStateMachine fsm = FiniteStateMachine("turkish_finite_state_machine.xml");
    vector<State> stateList = fsm.getStates();
    int transitionCount = 0;
    for (const State& state : stateList){
        transitionCount += fsm.getTransitions(state).size();
    }
    REQUIRE(779 == transitionCount);
}

TEST_CASE("FiniteStateMachineTest-testTransitionWith") {
    FiniteStateMachine fsm = FiniteStateMachine("turkish_finite_state_machine.xml");
    vector<State> stateList = fsm.getStates();
    CounterHashMap<string> transitionCounts = CounterHashMap<string>();
    for (State state : stateList){
        vector<Transition> transitions = fsm.getTransitions(state);
        for (Transition transition : transitions){
            transitionCounts.put(transition.to_String());
        }
    }
    vector<pair<string, int>> topList = transitionCounts.topN(5);
    REQUIRE("0" == topList[0].first);
    REQUIRE(111 == topList[0].second);
    REQUIRE("lAr" == topList[1].first);
    REQUIRE(37 == topList[1].second);
    REQUIRE("DHr" == topList[2].first);
    REQUIRE(28 == topList[2].second);
    REQUIRE("Hn" == topList[3].first);
    REQUIRE(24 == topList[3].second);
    REQUIRE("lArH" == topList[4].first);
    REQUIRE(23 == topList[4].second);
}

TEST_CASE("FiniteStateMachineTest-testTransitionWithName") {
    FiniteStateMachine fsm = FiniteStateMachine("turkish_finite_state_machine.xml");
    vector<State> stateList = fsm.getStates();
    CounterHashMap<string> transitionCounts = CounterHashMap<string>();
    for (const State& state : stateList){
        vector<Transition> transitions = fsm.getTransitions(state);
        for (Transition transition : transitions){
            transitionCounts.put(transition.getWith());
        }
    }
    vector<pair<string, int>> topList = transitionCounts.topN(5);
    REQUIRE("" == topList[0].first);
    REQUIRE(52 == topList[0].second);
    REQUIRE("^DB+VERB+CAUS" == topList[1].first);
    REQUIRE(33 == topList[1].second);
    REQUIRE("^DB+VERB+PASS" == topList[2].first);
    REQUIRE(31 == topList[2].second);
    REQUIRE("A3PL" == topList[3].first);
    REQUIRE(28 == topList[3].second);
    REQUIRE("LOC" == topList[4].first);
    REQUIRE(24 == topList[4].second);
}