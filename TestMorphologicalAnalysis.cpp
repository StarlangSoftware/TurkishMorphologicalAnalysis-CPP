//
// Created by Olcay Taner Yıldız on 2.03.2019.
//

#include <iostream>
#include "FsmMorphologicalAnalyzer.h"

void testWord(FsmMorphologicalAnalyzer fsm, string word){
    FsmParseList fsmParses = fsm.morphologicalAnalysis(move(word));
    for (int i = 0; i < fsmParses.size(); i++){
        cout << fsmParses.getFsmParse(i).getTransitionList();
    }
}

void analyze(){
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    string word = "ali topu at";
    while (Word::size(word) > 1){
        cout << "->";
        cin >> word;
        testWord(fsm, word);
    }
}

int main(){
    analyze();
}