//
// Created by olcay on 28.02.2019.
//

#include "FsmParseList.h"

struct fsmParseComparator{
    bool operator() (FsmParse fsmParseA, FsmParse fsmParseB){
        return fsmParseA.transitionlist() < fsmParseB.transitionlist();
    }
};

/**
 * A constructor of {@link FsmParseList} class which takes an {@link vector} fsmParses as an input. First it sorts
 * the items of the {@link vector} then loops through it, if the current item's transitions equal to the next item's
 * transitions, it removes the latter item. At the end, it assigns this {@link vector} to the fsmParses variable.
 *
 * @param fsmParses {@link FsmParse} type{@link vector} input.
 */
FsmParseList::FsmParseList(vector<FsmParse> fsmParses) {
    if (!fsmParses.empty()){
        stable_sort(fsmParses.begin(), fsmParses.end(), fsmParseComparator());
        for (int i = 0; i < fsmParses.size() - 1; i++) {
            if (fsmParses.at(i).transitionlist() == fsmParses.at(i + 1).transitionlist()) {
                fsmParses.erase(fsmParses.begin() + i + 1);
                i--;
            }
        }
    }
    this->fsmParses = fsmParses;
}

/**
 * The size method returns the size of fsmParses {@link vector}.
 *
 * @return the size of fsmParses {@link vector}.
 */
int FsmParseList::size() {
    return fsmParses.size();
}

/**
 * The getFsmParse method takes an integer index as an input and returns the item of fsmParses {@link vector} at given index.
 *
 * @param index Integer input.
 * @return the item of fsmParses {@link vector} at given index.
 */
FsmParse FsmParseList::getFsmParse(int index) {
    return fsmParses.at(index);
}

/**
 * The rootWords method gets the first item's root of fsmParses {@link vector} and uses it as currentRoot. Then loops through
 * the fsmParses, if the current item's root does not equal to the currentRoot, it then assigns it as the currentRoot and
 * accumulates root words in a {@link String} result.
 *
 * @return String result that has root words.
 */
string FsmParseList::rootWords() {
    string result = fsmParses.at(0).getWord()->getName(), currentRoot = result;
    for (int i = 1; i < fsmParses.size(); i++) {
        if (fsmParses.at(i).getWord()->getName() != currentRoot) {
            currentRoot = fsmParses.at(i).getWord()->getName();
            result += "$" + currentRoot;
        }
    }
    return result;
}

/**
 * The reduceToParsesWithSameRootAndPos method takes a {@link Word} currentWithPos as an input and loops i times till
 * i equals to the size of the fsmParses {@link vector}. If the given currentWithPos does not equal to the ith item's
 * root and the MorphologicalTag of the first inflectional of fsmParses, it removes the ith item from the {@link vector}.
 *
 * @param currentWithPos {@link Word} input.
 */
void FsmParseList::reduceToParsesWithSameRootAndPos(Word* currentWithPos) {
    int i = 0;
    while (i < fsmParses.size()) {
        if (fsmParses.at(i).getWordWithPos()->getName() != currentWithPos->getName()) {
            fsmParses.erase(fsmParses.begin() + i);
        } else {
            i++;
        }
    }
}

/**
 * The getParseWithLongestRootWord method returns the parse with the longest root word. If more than one parse has the
 * longest root word, the first parse with that root is returned.
 *
 * @return FsmParse Parse with the longest root word.
 */
FsmParse FsmParseList::getParseWithLongestRootWord() {
    FsmParse bestParse;
    int maxLength = -1;
    for (auto & fsmParse : fsmParses){
        int length = Word::size(fsmParse.getWord()->getName());
        if (length > maxLength){
            maxLength = length;
            bestParse = fsmParse;
        }
    }
    return bestParse;
}

/**
 * The reduceToParsesWithSameRoot method takes a {@link String} currentWithPos as an input and loops i times till
 * i equals to the size of the fsmParses {@link vector}. If the given currentRoot does not equal to the root of ith item of
 * fsmParses, it removes the ith item from the {@link vector}.
 *
 * @param currentRoot {@link String} input.
 */
void FsmParseList::reduceToParsesWithSameRoot(string currentRoot) {
    int i = 0;
    while (i < fsmParses.size()) {
        if (fsmParses.at(i).getWord()->getName() != currentRoot) {
            fsmParses.erase(fsmParses.begin() + i);
        } else {
            i++;
        }
    }
}

/**
 * The constructParseListForDifferentRootWithPos method initially creates a result {@link ArrayList} then loops through the
 * fsmParses {@link ArrayList}. For the first iteration, it creates new {@link ArrayList} as initial, then adds the
 * first item od fsmParses to initial and also add this initial {@link ArrayList} to the result {@link ArrayList}.
 * For the following iterations, it checks whether the current item's root with the MorphologicalTag of the first inflectional
 * equal to the previous item's  root with the MorphologicalTag of the first inflectional. If so, it adds that item
 * to the result {@link ArrayList}, if not it creates new {@link ArrayList} as initial and adds the first item od fsmParses
 * to initial and also add this initial {@link ArrayList} to the result {@link ArrayList}.
 *
 * @return result {@link ArrayList} type of {@link FsmParseList}.
 */
vector<FsmParseList> FsmParseList::constructParseListForDifferentRootWithPos() {
    vector<FsmParseList> result;
    int i = 0;
    while (i < fsmParses.size()) {
        if (i == 0) {
            vector<FsmParse> initial;
            initial.emplace_back(fsmParses.at(i));
            result.emplace_back(FsmParseList(initial));
        } else {
            if (*(fsmParses.at(i).getWordWithPos()) == *(fsmParses.at(i - 1).getWordWithPos())) {
                result.at(result.size() - 1).fsmParses.emplace_back(fsmParses.at(i));
            } else {
                vector<FsmParse> initial;
                initial.emplace_back(fsmParses.at(i));
                result.emplace_back(FsmParseList(initial));
            }
        }
        i++;
    }
    return result;
}

/**
 * The parsesWithoutPrefixAndSuffix method first creates a {@link String} array named analyses with the size of fsmParses {@link ArrayList}'s size.
 * <p>
 * If the size is just 1, it then returns the first item's transitionList, if it is greater than 1, loops through the fsmParses and
 * puts the transitionList of each item to the analyses array.
 * <p>
 * If the removePrefix condition holds, it loops through the analyses array and takes each item's substring after the first + sign and updates that
 * item of analyses array with that substring.
 * <p>
 * If the removeSuffix condition holds, it loops through the analyses array and takes each item's substring till the last + sign and updates that
 * item of analyses array with that substring.
 * <p>
 * It then removes the duplicate items of analyses array and returns a result {@link String} that has the accumulated items of analyses array.
 *
 * @return result {@link String} that has the accumulated items of analyses array.
 */
string FsmParseList::parsesWithoutPrefixAndSuffix() {
    string* analyses = new string[fsmParses.size()];
    bool removePrefix = true, removeSuffix = true;
    if (fsmParses.size() == 1) {
        return fsmParses.at(0).transitionlist().substr(fsmParses.at(0).transitionlist().find("+") + 1);
    }
    for (int i = 0; i < fsmParses.size(); i++) {
        analyses[i] = fsmParses.at(i).transitionlist();
    }
    while (removePrefix) {
        removePrefix = true;
        for (int i = 0; i < fsmParses.size() - 1; i++) {
            if (analyses[i].find("+") == string::npos || analyses[i + 1].find("+") == string::npos ||
                analyses[i].substr(0, analyses[i].find("+") + 1) != analyses[i + 1].substr(0, analyses[i + 1].find("+") + 1)) {
                removePrefix = false;
                break;
            }
        }
        if (removePrefix) {
            for (int i = 0; i < fsmParses.size(); i++) {
                analyses[i] = analyses[i].substr(analyses[i].find("+") + 1);
            }
        }
    }
    while (removeSuffix) {
        removeSuffix = true;
        for (int i = 0; i < fsmParses.size() - 1; i++) {
            if (analyses[i].find("+") == string::npos || analyses[i + 1].find("+") == string::npos ||
                analyses[i].substr(analyses[i].find_last_of("+")) != analyses[i + 1].substr(analyses[i + 1].find_last_of("+"))) {
                removeSuffix = false;
                break;
            }
        }
        if (removeSuffix) {
            for (int i = 0; i < fsmParses.size(); i++) {
                analyses[i] = analyses[i].substr(0, analyses[i].find_last_of("+"));
            }
        }
    }
    for (int i = 0; i < fsmParses.size(); i++) {
        for (int j = i + 1; j < fsmParses.size(); j++) {
            if (analyses[i] > analyses[j]) {
                string tmp = analyses[i];
                analyses[i] = analyses[j];
                analyses[j] = tmp;
            }
        }
    }
    string result = analyses[0];
    for (int i = 1; i < fsmParses.size(); i++) {
        result += "$" + analyses[i];
    }
    return result;
}

/**
 * The overridden toString method loops through the fsmParses {@link ArrayList} and accumulates the items to a result {@link String}.
 *
 * @return result {@link String} that has the items of fsmParses {@link ArrayList}.
 */
string FsmParseList::to_String() {
    string result;
    for (int i = 0; i < fsmParses.size(); i++) {
        result += fsmParses.at(i).to_String() + "\n";
    }
    return result;
}
