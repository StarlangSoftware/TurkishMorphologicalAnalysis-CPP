//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#include "MetamorphicParse.h"

/**
 * The getMetaMorphemeTag method takes a String tag as an input and takes the first char of the tag. If first char
 * is a punctuation it gets a substring from the tag. And gets the meta morphemes of this tag then adds to the
 * result {@link vector}.
 *
 * @param tag String to get meta morphemes from.
 * @return vector type result which holds meta morphemes.
 */
vector<MorphologicalTag> MetamorphicParse::getMetaMorphemeTag(string tag) {
    vector<MorphologicalTag> result;
    string s = Word::charAt(tag, 0);
    if (Word::isPunctuation(s)) {
        tag = tag.substr(1, tag.size());
    }
    for (int j = 0; j < META_MORPHEME_SIZE; j++) {
        if (tag == MetamorphicParse::metaMorphemes[j]) {
            result.emplace_back(morphotacticTags[j]);
        }
    }
    return result;
}

/**
 * Another getMetaMorphemeTag method which also takes parse as an input. It also checks the morphotactic tags.
 *
 * @param parse MorphologicalParse type input.
 * @param tag   String to get meta morphemes from.
 * @return ArrayList type result which holds meta morphemes.
 */
vector<MorphologicalTag> MetamorphicParse::getMetaMorphemeTag(MorphologicalParse parse, string tag){
    vector<MorphologicalTag> result;
    string s = Word::charAt(tag, 0);
    if (Word::isPunctuation(s)) {
        tag = tag.substr(1, tag.size());
    }
    for (int j = 0; j < META_MORPHEME_SIZE; j++) {
        if (tag == MetamorphicParse::metaMorphemes[j] && parse.containsTag(morphotacticTags[j])) {
            result.emplace_back(morphotacticTags[j]);
        }
    }
    return result;
}

/**
 * The getter method for Private Word root.
 *
 * @return Word type root.
 */
Word MetamorphicParse::getWord() {
    return root;
}

/**
 * An empty constructor of {@link MetamorphicParse} class.
 */
MetamorphicParse::MetamorphicParse() = default;

/**
 * A constructor of {@link MetamorphicParse} class which creates an {@link vector} metaMorphemeList which has split words
 * according to +.
 *
 * @param parse String to parse.
 */
MetamorphicParse::MetamorphicParse(string parse){
    int i;
    if (parse == "+") {
        root = Word("+");
    } else {
        vector<string> words = Word::split(parse, "+");
        root = Word(words[0]);
        for (i = 1; i < words.size(); i++)
            metaMorphemeList.emplace_back(words[i]);
    }
}

/**
 * The size method returns the size of the metaMorphemeList.
 *
 * @return the size of the metaMorphemeList.
 */
int MetamorphicParse::size(){
    return metaMorphemeList.size() + 1;
}

/**
 * The addMetaMorphemeList method splits input String by + and add to the metaMorphemeList.
 *
 * @param newTacticSet String to add the metaMorphemeList.
 */
void MetamorphicParse::addMetaMorphemeList(string newTacticSet) {
    vector<string> tactics = Word::split(move(newTacticSet), "+");
    metaMorphemeList.insert(metaMorphemeList.end(), tactics.begin(), tactics.end());
}

/**
 * The removeMetaMorphemeFromIndex method removes the meta morpheme at given index from metaMorphemeList.
 *
 * @param index to remove from metaMorphemeList.
 */
void MetamorphicParse::removeMetaMorphemeFromIndex(int index) {
    metaMorphemeList.erase(metaMorphemeList.begin() + index - 1, metaMorphemeList.end());
}

/**
 * The getMetaMorpheme method gets the meta morpheme at given index.
 *
 * @param index is used to get the meta morpheme.
 * @return metaMorphemeList's corresponding meta morpheme.
 */
string MetamorphicParse::getMetaMorpheme(int index) {
    if (index == 0) {
        return root.getName();
    } else {
        return metaMorphemeList.at(index - 1);
    }
}

/**
 * Overridden toString method to return resulting meta morphemes in metaMorphemeList.
 *
 * @return String result.
 */
string MetamorphicParse::to_string() {
    string result = root.getName();
    for (string metaMorpheme : metaMorphemeList) {
        result = result + "+" + metaMorpheme;
    }
    return result;
}
