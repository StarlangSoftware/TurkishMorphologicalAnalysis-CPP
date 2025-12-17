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
    [[nodiscard]] Word* getWord() const;
    explicit MorphologicalParse(const string& parse);
    explicit MorphologicalParse(const vector<string>& inflectionalGroups);
    [[nodiscard]] string getTransitionList() const;
    [[nodiscard]] string getInflectionalGroupString(int index) const;
    [[nodiscard]] InflectionalGroup getInflectionalGroup(int index) const;
    [[nodiscard]] InflectionalGroup getLastInflectionalGroup() const;
    [[nodiscard]] string getTag(int index) const;
    [[nodiscard]] int tagSize() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] InflectionalGroup firstInflectionalGroup() const;
    [[nodiscard]] InflectionalGroup lastInflectionalGroup() const;
    [[nodiscard]] Word* getWordWithPos() const;
    [[nodiscard]] string getPos() const;
    [[nodiscard]] string getRootPos() const;
    [[nodiscard]] string lastIGContainsCase() const;
    [[nodiscard]] bool lastIGContainsTag(MorphologicalTag tag) const;
    [[nodiscard]] bool lastIGContainsPossessive() const;
    [[nodiscard]] bool isCapitalWord() const;
    [[nodiscard]] bool isNoun() const;
    [[nodiscard]] bool isVerb() const;
    [[nodiscard]] bool isRootVerb() const;
    [[nodiscard]] bool isAdjective() const;
    [[nodiscard]] bool isProperNoun() const;
    [[nodiscard]] bool isPunctuation() const;
    [[nodiscard]] bool isCardinal() const;
    [[nodiscard]] bool isOrdinal() const;
    [[nodiscard]] bool isReal() const;
    [[nodiscard]] bool isNumber() const;
    [[nodiscard]] bool isTime() const;
    [[nodiscard]] bool isDate() const;
    [[nodiscard]] bool isHashTag() const;
    [[nodiscard]] bool isEmail() const;
    [[nodiscard]] bool isPercent() const;
    [[nodiscard]] bool isFraction() const;
    [[nodiscard]] bool isRange() const;
    [[nodiscard]] bool isPlural() const;
    [[nodiscard]] bool isAuxiliary() const;
    [[nodiscard]] bool containsTag(MorphologicalTag tag) const;
    [[nodiscard]] string getTreePos() const;
    [[nodiscard]] vector<string> getUniversalDependencyFeatures(const string& uPos) const;
    [[nodiscard]] string getUniversalDependencyPos() const;
    [[nodiscard]] string to_string() const;
private:
    void updateRootAndInflectionalGroups(const vector<string>& _inflectionalGroups);
    [[nodiscard]] string getPronType() const;
    [[nodiscard]] string getNumType() const;
    [[nodiscard]] string getReflex() const;
    [[nodiscard]] string getNumber() const;
    [[nodiscard]] string getPossessiveNumber() const;
    [[nodiscard]] string getCase() const;
    [[nodiscard]] string getDefinite() const;
    [[nodiscard]] string getDegree() const;
    [[nodiscard]] string getPolarity() const;
    [[nodiscard]] string getPerson() const;
    [[nodiscard]] string getPossessivePerson() const;
    [[nodiscard]] string getVoice() const;
    [[nodiscard]] string getAspect() const;
    [[nodiscard]] string getTense() const;
    [[nodiscard]] string getMood() const;
    [[nodiscard]] string getVerbForm() const;
    [[nodiscard]] string getEvident() const;
};


#endif //MORPHOLOGICALANALYSIS_MORPHOLOGICALPARSE_H
