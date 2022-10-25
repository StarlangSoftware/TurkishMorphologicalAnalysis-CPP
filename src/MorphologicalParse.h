//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H
#define MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H

#include <vector>
#include "Dictionary/Word.h"
#include "InflectionalGroup.h"

using namespace std;

class MorphologicalParse {
protected:
    vector<InflectionalGroup> inflectionalGroups;
    Word* root;
public:
    MorphologicalParse();
    Word* getWord() const;
    explicit MorphologicalParse(const string& parse);
    explicit MorphologicalParse(const vector<string>& inflectionalGroups);
    string getTransitionList() const;
    string getInflectionalGroupString(int index) const;
    InflectionalGroup getInflectionalGroup(int index) const;
    InflectionalGroup getLastInflectionalGroup() const;
    string getTag(int index) const;
    int tagSize() const;
    int size() const;
    InflectionalGroup firstInflectionalGroup() const;
    InflectionalGroup lastInflectionalGroup() const;
    Word* getWordWithPos() const;
    string getPos() const;
    string getRootPos() const;
    string lastIGContainsCase() const;
    bool lastIGContainsTag(MorphologicalTag tag) const;
    bool lastIGContainsPossessive() const;
    bool isCapitalWord() const;
    bool isNoun() const;
    bool isVerb() const;
    bool isRootVerb() const;
    bool isAdjective() const;
    bool isProperNoun() const;
    bool isPunctuation() const;
    bool isCardinal() const;
    bool isOrdinal() const;
    bool isReal() const;
    bool isNumber() const;
    bool isTime() const;
    bool isDate() const;
    bool isHashTag() const;
    bool isEmail() const;
    bool isPercent() const;
    bool isFraction() const;
    bool isRange() const;
    bool isPlural() const;
    bool isAuxiliary() const;
    bool containsTag(MorphologicalTag tag) const;
    string getTreePos() const;
    vector<string> getUniversalDependencyFeatures(const string& uPos) const;
    string getUniversalDependencyPos() const;
    string to_string() const;
private:
    string getPronType() const;
    string getNumType() const;
    string getReflex() const;
    string getNumber() const;
    string getCase() const;
    string getDefinite() const;
    string getDegree() const;
    string getPolarity() const;
    string getPerson() const;
    string getVoice() const;
    string getAspect() const;
    string getTense() const;
    string getMood() const;
    string getVerbForm() const;
};


#endif //MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H
