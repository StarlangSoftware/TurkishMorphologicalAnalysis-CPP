//
// Created by Olcay Taner YILDIZ on 20.04.2022.
//

#ifndef MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H
#define MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H


#include "Dictionary/TxtWord.h"

class MorphotacticEngine {
public:
    static string resolveD(TxtWord* root, const string& formation, const string& formationToCheck);
    static string resolveA(TxtWord* root, const string& formation, bool rootWord, const string& formationToCheck);
    static string resolveH(TxtWord* root, const string& formation, bool beginningOfSuffix, bool specialCaseTenseSuffix, bool rootWord, const string& formationToCheck);
    static string resolveC(const string& formation, const string& formationToCheck);
    static string resolveS(const string& formation);
    static string resolveSh(const string& formation);
};


#endif //MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H
