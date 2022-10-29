//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include <iostream>
#include "catch.hpp"
#include <fstream>
#include <sstream>
#include "../src/FsmMorphologicalAnalyzer.h"

TEST_CASE("testGenerateAllParses") {
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    TxtDictionary* dictionary = fsm.getDictionary();
    vector<string> testWords = {"açıkla", "yıldönümü", "resim",
                            "hal", "emlak", "git",
                            "kavur", "ye", "yemek", "göç",
                            "ak", "sıska", "yıka", "bul",
                            "cevapla", "coş", "böl", "del",
                            "giy", "kaydol", "anla", "çök",
                            "çık", "doldur", "azal", "göster",
                            "aksa", "cenk", "kalp"};
    vector<FsmParse> parsesGenerated;
    vector<string> parsesExpected;
    string line;
    for (auto & testWord : testWords) {
        auto* word = (TxtWord*) dictionary->getWord(testWord);
        parsesExpected.clear();
        ifstream inputFile;
        inputFile.open("parses/" + word->getName() + ".txt", ifstream :: in);
        while (inputFile.good()) {
            getline(inputFile, line);
            if (!line.empty()){
                parsesExpected.push_back(Word::split(line)[1]);
            }
        }
        inputFile.close();
        parsesGenerated = fsm.generateAllParses(word, Word::size(word->getName()) + 5);
        REQUIRE(parsesExpected.size() == parsesGenerated.size());
        for (const FsmParse& parseGenerated : parsesGenerated) {
            REQUIRE(std::find(parsesExpected.begin(), parsesExpected.end(), parseGenerated.to_String()) != parsesExpected.end());
        }
    }
}

TEST_CASE("FsmMorphologicalAnalyzerTest") {
    static FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    static TxtDictionary* dictionary = fsm.getDictionary();

    SECTION("morphologicalAnalysisDataTimeNumber") {
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

    SECTION("morphologicalAnalysisProperNoun") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isProperNoun()) {
                REQUIRE_FALSE(fsm.morphologicalAnalysis(Word::toUpperCase(word->getName())).size() == 0);
            }
        }
    }

    SECTION("FsmMorphologicalAnalyzerTest-morphologicalAnalysisNounSoftenDuringSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->nounSoftenDuringSuffixation()) {
                State transitionState = State("Possessive", false, false);
                State startState = State("NominalRoot", true, false);
                Transition transition = Transition(transitionState, "yH", "ACC");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisVowelAChangesToIDuringYSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isVerb() && word->vowelAChangesToIDuringYSuffixation()) {
                State transitionState = State("VerbalStem", false, false);
                State startState = State("VerbalRoot", true, false);
                Transition transition = Transition(transitionState, "Hyor", "PROG1");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisIsPortmanteau") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->isPortmanteau() && !word->isPlural() &&
                !word->isPortmanteauFacedVowelEllipsis()) {
                State transitionState = State("CompoundNounRoot", true, false);
                State startState = State("CompoundNounRoot", true, false);
                Transition transition = Transition(transitionState, "lArH", "A3PL+P3PL");
                string rootForm, surfaceForm, exceptLast2, exceptLast;
                exceptLast2 = Word::substringExceptLastTwoChars(word->getName());
                exceptLast = Word::substringExceptLastChar(word->getName());
                if (word->isPortmanteauFacedSoftening()) {
                    int index = Word::size(word->getName()) - 2;
                    string ch = Word::charAt(word->getName(), index);
                    if (ch == "b") {
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
                    if (word->isPortmanteauEndingWithSI()) {
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

    SECTION("morphologicalAnalysisNotObeysVowelHarmonyDuringAgglutination") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->notObeysVowelHarmonyDuringAgglutination()) {
                State transitionState = State("Possessive", false, false);
                State startState = State("NominalRoot", true, false);
                Transition transition = Transition(transitionState, "yH", "ACC");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisLastIdropsDuringSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->lastIdropsDuringSuffixation()) {
                State transitionState = State("Possessive", false, false);
                State startState = State("NominalRoot", true, false);
                Transition transition = Transition(transitionState, "yH", "ACC");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisVerbSoftenDuringSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isVerb() && word->verbSoftenDuringSuffixation()) {
                State transitionState = State("VerbalStem", false, false);
                State startState = State("VerbalRoot", true, false);
                Transition transition = Transition(transitionState, "Hyor", "PROG1");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisDuplicatesDuringSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->duplicatesDuringSuffixation()) {
                State transitionState = State("Possessive", false, false);
                State startState = State("NominalRoot", true, false);
                Transition transition = Transition(transitionState, "yH", "ACC");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisEndingKChangesIntoG") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isNominal() && word->endingKChangesIntoG()) {
                State transitionState = State("Possessive", false, false);
                State startState = State("NominalRoot", true, false);
                Transition transition = Transition(transitionState, "yH", "ACC");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("morphologicalAnalysisLastIdropsDuringPassiveSuffixation") {
        for (int i = 0; i < dictionary->size(); i++) {
            auto *word = (TxtWord *) dictionary->getWord(i);
            if (word->isVerb() && word->lastIdropsDuringPassiveSuffixation()) {
                State transitionState = State("VerbalStem", false, false);
                State startState = State("VerbalRoot", true, false);
                Transition transition = Transition(transitionState, "Hl", "^DB+VERB+PASS");
                string surfaceForm = transition.makeTransition(word, word->getName(), startState);
                REQUIRE_FALSE(fsm.morphologicalAnalysis(surfaceForm).size() == 0);
            }
        }
    }

    SECTION("replaceWord") {
        REQUIRE("Hemşirenle evlendim" ==
                fsm.replaceWord(new Sentence("Kız kardeşinle evlendim"), "kız kardeş", "hemşire")->to_string());
        REQUIRE("Yemin etmişlerdi vazoyu kırmadığına" ==
                fsm.replaceWord(new Sentence("Yemin billah vermişlerdi vazoyu kırmadığına"), "yemin billah ver",
                                "yemin et")->to_string());
        REQUIRE("Burada çok abartma var" ==
                fsm.replaceWord(new Sentence("Burada çok mübalağa var"), "mübalağa", "abartma")->to_string());
        REQUIRE("Bu bina çok kötü şekilsizleştirildi" ==
                fsm.replaceWord(new Sentence("Bu bina çok kötü biçimsizleştirildi"), "biçimsizleş",
                                "şekilsizleş")->to_string());
        REQUIRE("Kız kardeşinle evlendim" ==
                fsm.replaceWord(new Sentence("Hemşirenle evlendim"), "hemşire", "kız kardeş")->to_string());
        REQUIRE("Abim geçen yıl ölmüştü gibi" ==
                fsm.replaceWord(new Sentence("Abim geçen yıl son yolculuğa çıkmıştı gibi"), "son yolculuğa çık",
                                "öl")->to_string());
        REQUIRE("Dün yaptığı güreş maçında yenildi" ==
                fsm.replaceWord(new Sentence("Dün yaptığı güreş maçında mağlup oldu"), "mağlup ol",
                                "yenil")->to_string());
        REQUIRE("Abim geçen yıl son yolculuğa çıkmıştı gibi" ==
                fsm.replaceWord(new Sentence("Abim geçen yıl ölmüştü gibi"), "öl", "son yolculuğa çık")->to_string());
        REQUIRE("Dün yaptığı güreş maçında mağlup oldu" ==
                fsm.replaceWord(new Sentence("Dün yaptığı güreş maçında yenildi"), "yenil", "mağlup ol")->to_string());
        REQUIRE("Dün yaptığı güreş maçında alt oldu sanki" ==
                fsm.replaceWord(new Sentence("Dün yaptığı güreş maçında mağlup oldu sanki"), "mağlup ol",
                                "alt ol")->to_string());
        REQUIRE("Yemin billah vermişlerdi vazoyu kırmadığına" ==
                fsm.replaceWord(new Sentence("Yemin etmişlerdi vazoyu kırmadığına"), "yemin et",
                                "yemin billah ver")->to_string());
        REQUIRE("Şvesterine söyle kazağı güzelmiş" ==
                fsm.replaceWord(new Sentence("Hemşirene söyle kazağı güzelmiş"), "hemşire", "şvester")->to_string());
    }
}