//
// Created by Olcay Taner YILDIZ on 2019-04-01.
//

#ifndef MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATIONCORPUS_H
#define MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATIONCORPUS_H

#include <string>
#include "Corpus.h"

using namespace std;

class DisambiguationCorpus : public Corpus{
public:
    DisambiguationCorpus();
    DisambiguationCorpus emptyCopy();
    explicit DisambiguationCorpus(string fileName);
    void writeToFile(string fileName);
    void writeToFile(string fileName, WordFormat format);
};


#endif //MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATIONCORPUS_H
