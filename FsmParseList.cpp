//
// Created by olcay on 28.02.2019.
//

#include "FsmParseList.h"

struct fsmParseComparator{
    bool operator() (FsmParse fsmParseA, FsmParse fsmParseB){
        return fsmParseA.getTransitionList() < fsmParseB.getTransitionList();
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
    stable_sort(fsmParses.begin(), fsmParses.end(), fsmParseComparator());
    for (int i = 0; i < fsmParses.size() - 1; i++) {
        if (fsmParses.at(i).getTransitionList() == fsmParses.at(i + 1).getTransitionList()) {
            fsmParses.erase(fsmParses.begin() + i + 1);
            i--;
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
 * The defaultCaseForParseString method takes String rootForm, parseString and partOfSpeech as inputs. And checks defined cases
 * for parseString and returns the strings till the $ sign. For example, if the given parseString is
 * "A3PL+P3PL+NOM$A3PL+P3SG+NOM$A3PL+PNON+ACC$A3SG+P3PL+NOM" it returns "A3PL+P3SG+NOM".
 *
 * @param rootForm     String input.
 * @param parseString  String input.
 * @param partOfSpeech String input.
 * @return String defaultCase.
 */
string FsmParseList::defaultCaseForParseString(string rootForm, string parseString, string partOfSpeech) {
    if (parseString == "P3SG+NOM$PNON+ACC") {
        if (partOfSpeech == "PROP") {
            return "PNON+ACC";
        } else {
            return "P3SG+NOM";
        }
    } else {
        if (parseString == "A2SG+P2SG$A3SG+P3SG") {
            return "A3SG+P3SG";
        } else {
            if (parseString == "A3PL+P3PL+NOM$A3PL+P3SG+NOM$A3PL+PNON+ACC$A3SG+P3PL+NOM") {
                return "A3PL+P3SG+NOM";
            } else {
                if (parseString == "P2SG$P3SG"){
                    return "P3SG";
                } else {
                    if (parseString == "A3PL+PNON+NOM$A3SG+PNON+NOM^DB+VERB+ZERO+PRES+A3PL"){
                        return "A3PL+PNON+NOM";
                    } else {
                        if (parseString == "P2SG+NOM$PNON+GEN"){
                            return "PNON+GEN";
                        } else {
                            if (parseString == "AOR^DB+ADJ+ZERO$AOR+A3SG"){
                                return "AOR+A3SG";
                            } else {
                                if (parseString == "P2SG$PNON"){
                                    return "PNON";
                                } else {
                                    if (parseString == "ADV+SINCE$VERB+ZERO+PRES+COP+A3SG"){
                                        if (rootForm == "yıl" || rootForm == "süre" || rootForm == "zaman" || rootForm == "ay") {
                                            return "ADV+SINCE";
                                        } else {
                                            return "VERB+ZERO+PRES+COP+A3SG";
                                        }
                                    } else {
                                        if (parseString == "CONJ$VERB+POS+IMP+A2SG"){
                                            return "CONJ";
                                        } else {
                                            if (parseString == "NEG+IMP+A2SG$POS^DB+NOUN+INF2+A3SG+PNON+NOM"){
                                                return "POS^DB+NOUN+INF2+A3SG+PNON+NOM";
                                            } else {
                                                if (parseString == "NEG+OPT+A3SG$POS^DB+NOUN+INF2+A3SG+PNON+DAT"){
                                                    return "POS^DB+NOUN+INF2+A3SG+PNON+DAT";
                                                } else {
                                                    if (parseString == "NOUN+A3SG+P3SG+NOM$NOUN^DB+ADJ+ALMOST"){
                                                        return "NOUN+A3SG+P3SG+NOM";
                                                    } else {
                                                        if (parseString == "ADJ$VERB+POS+IMP+A2SG"){
                                                            return "ADJ";
                                                        } else {
                                                            if (parseString == "NOUN+A3SG+PNON+NOM$VERB+POS+IMP+A2SG"){
                                                                return "NOUN+A3SG+PNON+NOM";
                                                            } else {
                                                                if (parseString == "INF2+A3SG+P3SG+NOM$INF2^DB+ADJ+ALMOST$"){
                                                                    return "INF2+A3SG+P3SG+NOM";
                                                                } else {
                                                                    return "";
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * The caseDisambiguator method first calls the parsesWithoutPrefixAndSuffix method and gets the words without prefixes and suffixes.
 * If the size of fsmParses {@link ArrayList} is 1, it directly returns the first item of that {@link ArrayList} and null if
 * the size is 0.
 * <p>
 * Then, it calls defaultCaseForParseString method with the root of first item of fsmParses, result of parsesWithoutPrefixAndSuffix method,
 * and the pos of the first item and assigns it result to the defaultCase {@link String}. If defaultCase is not null,
 * it then loops through the fsmParses and checks whether the current transitionList of {@link FsmParse} contains the defaultCase, if so it returns
 * current {@link FsmParse}, null otherwise.
 *
 * @return FsmParse if it contains defaultCase, null otherwise.
 */
FsmParse FsmParseList::caseDisambiguator() {
    string defaultCase;
    string parseString = parsesWithoutPrefixAndSuffix();
    if (fsmParses.size() == 1) {
        return fsmParses.at(0);
    }
    if (fsmParses.size() == 0) {
        return FsmParse();
    }
    defaultCase = defaultCaseForParseString(fsmParses.at(0).getWord()->getName(), parseString, fsmParses.at(0).getFinalPos());
    if (defaultCase != "") {
        for (int i = 0; i < fsmParses.size(); i++) {
            FsmParse fsmParse = fsmParses.at(i);
            if (fsmParse.getTransitionList().find(defaultCase) != string::npos) {
                return fsmParse;
            }
        }
    }
    return FsmParse();
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
            if (fsmParses.at(i).getWordWithPos() == fsmParses.at(i - 1).getWordWithPos()) {
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
        return fsmParses.at(0).getTransitionList().substr(fsmParses.at(0).getTransitionList().find("+") + 1);
    }
    for (int i = 0; i < fsmParses.size(); i++) {
        analyses[i] = fsmParses.at(i).getTransitionList();
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
