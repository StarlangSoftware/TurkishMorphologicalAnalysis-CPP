//
// Created by LMF319018 on 09/01/2019.
//

#ifndef CORPUS_WORDFORMAT_H
#define CORPUS_WORDFORMAT_H

enum class WordFormat{
/**
 * Surface/Original form
 */
            SURFACE,
    /**
     * Create 2-Gram words as output.
     */
            LETTER_2,
    /**
     * Create 3-Gram words as output.
     */
            LETTER_3,
    /**
     * Create 4-Gram words as output.
     */
            LETTER_4
};

#endif //CORPUS_WORDFORMAT_H
