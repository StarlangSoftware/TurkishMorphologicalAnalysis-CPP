//
// Created by Olcay Taner YILDIZ on 2019-04-01.
//

#include "DisambiguatedWord.h"

/**
 * The constructor of DisambiguatedWord class which takes a String and a MorphologicalParse
 * as inputs. It creates a new MorphologicalParse with given MorphologicalParse. It generates a new instance with
 * given String.
 *
 * @param name  Instances that will be a DisambiguatedWord.
 * @param parse MorphologicalParse of the DisambiguatedWord.
 */
DisambiguatedWord::DisambiguatedWord(const string& name, const MorphologicalParse& parse) : Word(name){
    this->parse = parse;
}

/**
 * Accessor for the MorphologicalParse.
 *
 * @return MorphologicalParse.
 */
MorphologicalParse DisambiguatedWord::getParse() const{
    return parse;
}
