//
// Created by Olcay Taner Yıldız on 11.01.2019.
//

#ifndef CORPUS_PARAGRAPH_H
#define CORPUS_PARAGRAPH_H

#include <vector>
#include "Sentence.h"

using namespace std;

class Paragraph {
private:
    vector<Sentence*> sentences;
public:
    Paragraph();
    ~Paragraph();
    void addSentence(Sentence* s);
    int sentenceCount();
    Sentence* getSentence(unsigned long index);
};


#endif //CORPUS_PARAGRAPH_H
