//
// Created by Olcay Taner Yıldız on 2.03.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
#define MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H

#include <regex>
#include "Dictionary/Trie/Trie.h"
#include "Sentence.h"
#include "FiniteStateMachine.h"
#include "Dictionary/TxtDictionary.h"
#include "LRUCache.h"
#include "FsmParseList.h"
#include "MetamorphicParse.h"

class FsmMorphologicalAnalyzer {
private:
    Trie* dictionaryTrie;
    Trie* suffixTrie;
    FiniteStateMachine finiteStateMachine;
    int MAX_DISTANCE = 2;
    TxtDictionary* dictionary;
    LRUCache<string, FsmParseList> cache;
    map<string, regex> mostUsedPatterns;
    map<string, string> parsedSurfaceForms;
    map<string, string> pronunciations;
    bool isPossibleSubstring(const string& shortString, const string& longString, const TxtWord* root) const;
    void initializeParseList(vector<FsmParse>& fsmParse, TxtWord* root, bool isProper) const;
    void initializeParseListFromRoot(vector<FsmParse>& fsmParse, TxtWord* root, bool isProper) const;
    [[nodiscard]] vector<FsmParse> initializeParseListFromSurfaceForm(const string& surfaceForm, bool isProper) const;
    void addNewParsesFromCurrentParse(const FsmParse& currentFsmParse, deque<FsmParse>& fsmParse, int maxLength, TxtWord* root) const;
    void addNewParsesFromCurrentParse(const FsmParse& currentFsmParse, deque<FsmParse>& fsmParse, const string& surfaceForm, TxtWord* root) const;
    bool parseExists(vector<FsmParse>& fsmParse, const string& surfaceForm) const;
    [[nodiscard]] vector<FsmParse> parseWord(vector<FsmParse> fsmParse, int maxLength) const;
    [[nodiscard]] vector<FsmParse> parseWord(vector<FsmParse> fsmParse, const string& surfaceForm) const;
    bool analysisExists(TxtWord* rootWord, const string& surfaceForm, bool isProper);
    vector<FsmParse> analysis(const string& surfaceForm, bool isProper);
    bool isInteger(const string& surfaceForm);
    bool isDouble(const string& surfaceForm);
    [[nodiscard]] bool isNumber(const string& surfaceForm) const;
    bool isPercent(const string& surfaceForm);
    bool isTime(const string& surfaceForm);
    bool isRange(const string& surfaceForm);
    bool isDate(const string& surfaceForm);
    bool isCode(const string& surfaceForm);
    bool patternMatches(const string& expr, const string& value);
    [[nodiscard]] string reverseString(const string& s) const;
    void prepareSuffixTrie();
    [[nodiscard]] vector<TxtWord*> rootOfPossiblyNewWord(const string& surfaceForm) const;
public:
    explicit FsmMorphologicalAnalyzer(const string& fileName = "turkish_finite_state_machine.xml", TxtDictionary* dictionary = new TxtDictionary(), int cacheSize = 10000);
    explicit FsmMorphologicalAnalyzer(const string& dictionaryFileName, const string& fileName = "turkish_finite_state_machine.xml");
    void addSurfaceForms(const string& fileName);
    void addPronunciations(const string& fileName);
    [[nodiscard]] TxtDictionary* getDictionary() const;
    [[nodiscard]] FiniteStateMachine getFiniteStateMachine() const;
    [[nodiscard]] unordered_set<string> getPossibleWords(const MorphologicalParse& morphologicalParse, const MetamorphicParse& parse) const;
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, const string& surfaceForm, const string& state) const;
    vector<FsmParse> generateAllParses(TxtWord* root, int maxLength) const;
    vector<FsmParse> morphologicalAnalysis(TxtWord* root, const string& surfaceForm) const;
    Sentence* replaceWord(Sentence* original, const string& previousWord, const string& newWord);
    [[nodiscard]] bool isProperNoun(const string& surfaceForm) const;
    FsmParseList robustMorphologicalAnalysis(const string& surfaceForm);
    FsmParseList* morphologicalAnalysis(const Sentence& sentence);
    FsmParseList* robustMorphologicalAnalysis(const Sentence& sentence);
    FsmParseList morphologicalAnalysis(const string& surfaceForm);
    bool morphologicalAnalysisExists(TxtWord* rootWord, const string& surfaceForm);
};


#endif //MORPHOLOGICALANALYSIS_FSMMORPHOLOGICALANALYZER_H
