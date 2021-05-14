//
// Created by Olcay Taner YILDIZ on 2019-04-01.
//

#include "DisambiguatedWord.h"

/**
 * The constructor of {@link DisambiguatedWord} class which takes a {@link String} and a {@link MorphologicalParse}
 * as inputs. It creates a new {@link MorphologicalParse} with given MorphologicalParse. It generates a new instance with
 * given {@link String}.
 *
 * @param name  Instances that will be a DisambiguatedWord.
 * @param parse {@link MorphologicalParse} of the {@link DisambiguatedWord}.
 */
DisambiguatedWord::DisambiguatedWord(string name, MorphologicalParse parse) : Word(move(name)){
    this->parse = move(parse);
}

/**
 * Accessor for the {@link MorphologicalParse}.
 *
 * @return MorphologicalParse.
 */
MorphologicalParse DisambiguatedWord::getParse() {
    return parse;
}
