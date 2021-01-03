//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include <iostream>
#include "catch.hpp"
#include "../FsmMorphologicalAnalyzer.h"

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisDataTimeNumber") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    REQUIRE_FALSE(fsm.morphologicalAnalysis("3/4").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("3\\/4").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("4/2/1973").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("14/2/1993").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("14/12/1933").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("6/12/1903").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("%34.5").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("%3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("%56").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("2:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("12:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("4:23").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("11:56").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("1:2:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("3:12:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("5:4:23").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("7:11:56").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("12:2:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("10:12:3").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("11:4:23").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("22:11:56").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("45").size() == 0);
    REQUIRE_FALSE(fsm.morphologicalAnalysis("34.23").size() == 0);
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisProperNoun") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isProperNoun()){
            REQUIRE_FALSE(fsm.morphologicalAnalysis(Word::toUpperCase(word->getName())).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisNounSoftenDuringSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->nounSoftenDuringSuffixation()){
            State transitionState = State("Possessive", false, false);
            State startState = State("NominalRoot", true, false);
            Transition transition = Transition(transitionState,"yH", "ACC");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisVowelAChangesToIDuringYSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isVerb() && word->vowelAChangesToIDuringYSuffixation()){
            State transitionState = State("VerbalStem", false, false);
            State startState = State("VerbalRoot", true, false);
            Transition transition = Transition(transitionState,"Hyor", "PROG1");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisIsPortmanteau") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->isPortmanteau() && !word->isPlural() && !word->isPortmanteauFacedVowelEllipsis()){
            State transitionState = State("CompoundNounRoot", true, false);
            State startState = State("CompoundNounRoot", true, false);
            Transition transition = Transition(transitionState,"lArH", "A3PL+P3PL");
            string rootForm, surfaceForm, exceptLast2, exceptLast;
            exceptLast2 = Word::substringExceptLastTwoChars(word->getName());
            exceptLast = Word::substringExceptLastChar(word->getName());
            if (word->isPortmanteauFacedSoftening()){
                int index = Word::size(word->getName()) - 2;
                string ch = Word::charAt(word->getName(), index);
                if (ch == "b"){
                    rootForm = exceptLast2 + "p";
                } else {
                    if (ch == "c") {
                        rootForm = exceptLast2 + "ç";
                    } else {
                        if (ch == "d") {
                            rootForm = exceptLast2 + "t";
                        } else {
                            if (ch == "ğ") {
                                rootForm = exceptLast2 + "k";
                            } else {
                                rootForm = exceptLast;
                            }
                        }
                    }
                }
            } else {
                if (word->isPortmanteauEndingWithSI()){
                    rootForm = exceptLast2;
                } else {
                    rootForm = exceptLast;
                }
            }
            surfaceForm = transition.makeTransition(word, rootForm, startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisNotObeysVowelHarmonyDuringAgglutination") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->notObeysVowelHarmonyDuringAgglutination()){
            State transitionState = State("Possessive", false, false);
            State startState = State("NominalRoot", true, false);
            Transition transition = Transition(transitionState,"yH", "ACC");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisLastIdropsDuringSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->lastIdropsDuringSuffixation()){
            State transitionState = State("Possessive", false, false);
            State startState = State("NominalRoot", true, false);
            Transition transition = Transition(transitionState,"yH", "ACC");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisVerbSoftenDuringSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isVerb() && word->verbSoftenDuringSuffixation()){
            State transitionState = State("VerbalStem", false, false);
            State startState = State("VerbalRoot", true, false);
            Transition transition = Transition(transitionState,"Hyor", "PROG1");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisDuplicatesDuringSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->duplicatesDuringSuffixation()){
            State transitionState = State("Possessive", false, false);
            State startState = State("NominalRoot", true, false);
            Transition transition = Transition(transitionState,"yH", "ACC");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisEndingKChangesIntoG") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isNominal() && word->endingKChangesIntoG()){
            State transitionState = State("Possessive", false, false);
            State startState = State("NominalRoot", true, false);
            Transition transition = Transition(transitionState,"yH", "ACC");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest-morphologicalAnalysisLastIdropsDuringPassiveSuffixation") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary dictionary = fsm.getDictionary();
    for (int i = 0; i < dictionary.size(); i++){
        auto* word = (TxtWord*) dictionary.getWord(i);
        if (word->isVerb() && word->lastIdropsDuringPassiveSuffixation()){
            State transitionState = State("VerbalStem", false, false);
            State startState = State("VerbalRoot", true, false);
            Transition transition = Transition(transitionState,"Hl", "^DB+VERB+PASS");
            string surfaceForm = transition.makeTransition(word, word->getName(), startState);
            REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
        }
    }
}