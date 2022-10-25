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
    MorphologicalTag getTag(int index) const;
    int size() const;
    string to_String() const;
    MorphologicalTag containsCase() const;
    bool containsPlural() const;
    bool containsTag(MorphologicalTag tag) const;
    bool containsPossessive() const;
    static const int TAG_SIZE = 131;
    static const MorphologicalTag morphoTags[TAG_SIZE];
private:
    vector<MorphologicalTag> IG;
    static const string tags[TAG_SIZE];
};

#endif //MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
