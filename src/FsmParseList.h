//
// Created by olcay on 28.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#define MORPHOLOGICALANALYSIS_FSMPARSELIST_H
#include "FsmParse.h"

class FsmParseList {
private:
    vector<FsmParse> fsmParses;
    static const string longestRootExceptions[231];
    [[nodiscard]] bool isLongestRootException(const FsmParse& fsmParse) const;
public:
    FsmParseList() = default;
    explicit FsmParseList(vector<FsmParse> fsmParses);
    [[nodiscard]] int size() const;
    [[nodiscard]] FsmParse getFsmParse(int index) const;
    [[nodiscard]] string rootWords() const;
    void reduceToParsesWithSameRootAndPos(const Word* currentWithPos);
    [[nodiscard]] FsmParse getParseWithLongestRootWord() const;
    void reduceToParsesWithSameRoot(const string& currentRoot);
    [[nodiscard]] vector<FsmParseList> constructParseListForDifferentRootWithPos() const;
    [[nodiscard]] string parsesWithoutPrefixAndSuffix() const;
    [[nodiscard]] string to_String() const;
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSELIST_H
