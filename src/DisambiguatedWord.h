//
// Created by Olcay Taner YILDIZ on 2019-04-01.
//

#ifndef MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATEDWORD_H
#define MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATEDWORD_H

#include "Dictionary/Word.h"
#include "MorphologicalParse.h"

class DisambiguatedWord : public Word {
private:
    MorphologicalParse parse;
public:
    DisambiguatedWord(string name, MorphologicalParse parse);
    MorphologicalParse getParse();
};


#endif //MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATEDWORD_H
