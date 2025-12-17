//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
#define MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H

#include <vector>
#include <string>
#include "MorphologicalTag.h"

using namespace std;

class InflectionalGroup {
public:
    static MorphologicalTag getMorphologicalTag(const string& tag);
    static string getTag(MorphologicalTag tag);
    explicit InflectionalGroup(const string& IG);
    [[nodiscard]] MorphologicalTag getTag(int index) const;
    [[nodiscard]] int size() const;
    [[nodiscard]] string to_String() const;
    [[nodiscard]] MorphologicalTag containsCase() const;
    [[nodiscard]] bool containsPlural() const;
    [[nodiscard]] bool containsTag(MorphologicalTag tag) const;
    [[nodiscard]] bool containsPossessive() const;
    static const int TAG_SIZE = 133;
    static const MorphologicalTag morphoTags[TAG_SIZE];
private:
    vector<MorphologicalTag> IG;
    static const string tags[TAG_SIZE];
};

#endif //MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
