//
// Created by Olcay Taner YILDIZ on 20.04.2022.
//

#ifndef MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H
#define MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H


#include "TxtWord.h"

class MorphotacticEngine {
public:
    static string resolveD(TxtWord* root, string formation, string formationToCheck);
    static string resolveA(TxtWord* root, string formation, bool rootWord, string formationToCheck);
    static string resolveH(TxtWord* root, string formation, bool beginningOfSuffix, bool specialCaseTenseSuffix, bool rootWord, string formationToCheck);
    static string resolveC(string formation, string formationToCheck);
    static string resolveS(string formation);
    static string resolveSh(string formation);
};


#endif //MORPHOLOGICALANALYSIS_MORPHOTACTICENGINE_H
