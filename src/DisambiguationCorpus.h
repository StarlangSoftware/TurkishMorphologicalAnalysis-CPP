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
    DisambiguationCorpus emptyCopy() const;
    explicit DisambiguationCorpus(const string& fileName);
    void writeToFile(const string& fileName) const;
    void writeToFile(const string& fileName, WordFormat format) const;
};


#endif //MORPHOLOGICALDISAMBIGUATION_DISAMBIGUATIONCORPUS_H
