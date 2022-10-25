//
// Created by olcay on 28.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#define MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#include "FsmParse.h"

class FsmParseList {
private:
    vector<FsmParse> fsmParses;
    static const string longestRootExceptions[230];
    bool isLongestRootException(const FsmParse& fsmParse) const;
public:
    FsmParseList() = default;
    explicit FsmParseList(vector<FsmParse> fsmParses);
    int size();
    FsmParse getFsmParse(int index) const;
    string rootWords() const;
    void reduceToParsesWithSameRootAndPos(Word* currentWithPos);
    FsmParse getParseWithLongestRootWord() const;
    void reduceToParsesWithSameRoot(const string& currentRoot);
    vector<FsmParseList> constructParseListForDifferentRootWithPos() const;
    string parsesWithoutPrefixAndSuffix() const;
    string to_String() const;
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSELIST_H
