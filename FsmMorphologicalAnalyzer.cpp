//
// Created by Olcay Taner Yıldız on 2.03.2019.
//
#include <regex>
#include <iostream>
#include "FsmMorphologicalAnalyzer.h"

/**
 * Another constructor of FsmMorphologicalAnalyzer class. It generates a new TxtDictionary type dictionary from
 * given input dictionary, with given inputs fileName and cacheSize.
 *
 * @param fileName   the file to read the finite state machine.
 * @param dictionary the dictionary file that will be used to generate dictionaryTrie.
 * @param cacheSize  the size of the LRUCache.
 */
FsmMorphologicalAnalyzer::FsmMorphologicalAnalyzer(string fileName, TxtDictionary dictionary, int cacheSize) {
    finiteStateMachine = FiniteStateMachine(move(fileName));
    dictionaryTrie = dictionary.prepareTrie();
    dictionary = move(dictionary);
    cache = LRUCache<string, FsmParseList>(cacheSize);
}

/**
 * Another constructor of FsmMorphologicalAnalyzer class. It generates a new TxtDictionary type dictionary from
 * given input dictionary file name and by using turkish_finite_state_machine.xml file.
 *
 * @param fileName           the file to read the finite state machine.
 * @param dictionaryFileName the file to read the dictionary.
 */
FsmMorphologicalAnalyzer::FsmMorphologicalAnalyzer(string dictionaryFileName, string fileName) : FsmMorphologicalAnalyzer(move(fileName), TxtDictionary(move(dictionaryFileName), Comparator::TURKISH)){
}

/**
 * The getDictionary method is used to get TxtDictionary.
 *
 * @return TxtDictionary type dictionary.
 */
TxtDictionary FsmMorphologicalAnalyzer::getDictionary() {
    return dictionary;
}

/**
 * The getFiniteStateMachine method is used to get FiniteStateMachine.
 *
 * @return FiniteStateMachine type finiteStateMachine.
 */
FiniteStateMachine FsmMorphologicalAnalyzer::getFiniteStateMachine() {
    return finiteStateMachine;
}

/**
 * The getPossibleWords method takes {@link MorphologicalParse} and {@link MetamorphicParse} as input.
 * First it determines whether the given morphologicalParse is the root verb and whether it contains a verb tag.
 * Then it creates new transition with -mak and creates a new {@link HashSet} result.
 * <p>
 * It takes the given {@link MetamorphicParse} input as currentWord and if there is a compound word starting with the
 * currentWord, it gets this compoundWord from dictionaryTrie. If there is a compoundWord and the difference of the
 * currentWord and compundWords is less than 3 than compoundWord is added to the result, otherwise currentWord is added.
 * <p>
 * Then it gets the root from parse input as a currentRoot. If it is not null, and morphologicalParse input is verb,
 * it directly adds the verb to result after making transition to currentRoot with currentWord String. Else, it creates a new
 * transition with -lar and make this transition then adds to the result.
 *
 * @param morphologicalParse {@link MorphologicalParse} type input.
 * @param parse              {@link MetamorphicParse} type input.
 * @return {@link HashSet} result.
 */
unordered_set<string>
FsmMorphologicalAnalyzer::getPossibleWords(MorphologicalParse morphologicalParse, MetamorphicParse parse) {
    bool isRootVerb = morphologicalParse.getRootPos() == "VERB";
    bool containsVerb = morphologicalParse.containsTag(MorphologicalTag::VERB);
    Transition verbTransition = Transition("mAk");
    TxtWord* compoundWord;
    TxtWord* currentRoot;
    unordered_set<string> result;
    if (parse.getWord().getName().empty()) {
        return result;
    }
    string verbWord, pluralWord, currentWord = parse.getWord().getName();
    int pluralIndex = -1;
    compoundWord = dictionaryTrie->getCompoundWordStartingWith(currentWord);
    if (!isRootVerb) {
        if (Word::size(compoundWord->getName()) - Word::size(currentWord) < 3) {
            result.emplace(compoundWord->getName());
        }
        result.emplace(currentWord);
    }
    currentRoot = (TxtWord*) dictionary.getWord(parse.getWord().getName());
    if (currentRoot == nullptr && compoundWord != nullptr) {
        currentRoot = compoundWord;
    }
    if (currentRoot != nullptr) {
        if (isRootVerb) {
            verbWord = verbTransition.makeTransition(currentRoot, currentWord);
            result.emplace(verbWord);
        }
        pluralWord = "";
        for (int i = 1; i < parse.size(); i++) {
            Transition transition = Transition(State(), parse.getMetaMorpheme(i), "");
            if (parse.getMetaMorpheme(i) == "lAr") {
                pluralWord = currentWord;
                pluralIndex = i + 1;
            }
            currentWord = transition.makeTransition(currentRoot, currentWord);
            result.emplace(currentWord);
            if (containsVerb) {
                verbWord = verbTransition.makeTransition(currentRoot, currentWord);
                result.emplace(verbWord);
            }
        }
        if (!pluralWord.empty()) {
            currentWord = pluralWord;
            for (int i = pluralIndex; i < parse.size(); i++) {
                Transition transition = Transition(State(), parse.getMetaMorpheme(i), "");
                currentWord = transition.makeTransition(currentRoot, currentWord);
                result.emplace(currentWord);
                if (containsVerb) {
                    verbWord = verbTransition.makeTransition(currentRoot, currentWord);
                    result.emplace(verbWord);
                }
            }
        }
    }
    return result;
}

/**
 * The isPossibleSubstring method first checks whether given short and long strings are equal to root word.
 * Then, compares both short and long strings' chars till the last two chars of short string. In the presence of mismatch,
 * false is returned. On the other hand, it counts the distance between two strings until it becomes greater than 2,
 * which is the MAX_DISTANCE also finds the index of the last char.
 * <p>
 * If the substring is a rootWord and equals to 'ben', which is a special case or root holds the lastIdropsDuringSuffixation or
 * lastIdropsDuringPassiveSuffixation conditions, then it returns true if distance is not greater than MAX_DISTANCE.
 * <p>
 * On the other hand, if the shortStrong ends with one of these chars 'e, a, p, ç, t, k' and 't 's a rootWord with
 * the conditions of rootSoftenDuringSuffixation, vowelEChangesToIDuringYSuffixation, vowelAChangesToIDuringYSuffixation
 * or endingKChangesIntoG then it returns true if the last index is not equal to 2 and distance is not greater than
 * MAX_DISTANCE and false otherwise.
 *
 * @param shortString the possible substring.
 * @param longString  the long string to compare with substring.
 * @param root        the root of the long string.
 * @return true if given substring is the actual substring of the longString, false otherwise.
 */
bool FsmMorphologicalAnalyzer::isPossibleSubstring(string shortString, string longString, TxtWord *root) {
    bool rootWord = (shortString == root->getName() || longString == root->getName());
    int distance = 0, j, last = 1;
    for (j = 0; j < Word::size(shortString); j++) {
        if (Word::charAt(shortString, j) != Word::charAt(longString, j)) {
            if (j < Word::size(shortString) - 2) {
                return false;
            }
            last = Word::size(shortString) - j;
            distance++;
            if (distance > MAX_DISTANCE) {
                break;
            }
        }
    }
    if (rootWord && (root->getName() == "ben" || root->lastIdropsDuringSuffixation() || root->lastIdropsDuringPassiveSuffixation())) {
        return (distance <= MAX_DISTANCE);
    } else {
        if (Word::lastChar(shortString) == "e" || Word::lastChar(shortString) == "a" || Word::lastChar(shortString) == "p" || Word::lastChar(shortString) == "ç" || Word::lastChar(shortString) == "t" || Word::lastChar(shortString) == "k" || (rootWord && (root->rootSoftenDuringSuffixation() || root->vowelEChangesToIDuringYSuffixation() || root->vowelAChangesToIDuringYSuffixation() || root->endingKChangesIntoG()))) {
            return (last != 2 && distance <= MAX_DISTANCE - 1);
        } else {
            return (distance <= MAX_DISTANCE - 2);
        }
    }
}

/**
 * The initializeParseList method initializes the given given fsm ArrayList with given root words by parsing them.
 * <p>
 * It checks many conditions;
 * isPlural; if root holds the condition then it gets the state with the name of NominalRootPlural, then
 * creates a new parsing and adds this to the input fsmParse Arraylist.
 * Ex : Açıktohumlular
 * <p>
 * !isPlural and isPortmanteauEndingWithSI, if root holds the conditions then it gets the state with the
 * name of NominalRootNoPossesive.
 * Ex : Balarısı
 * <p>
 * !isPlural and isPortmanteau, if root holds the conditions then it gets the state with the name of
 * CompoundNounRoot.
 * Ex : Aslanağızı
 * <p>
 * !isPlural, !isPortmanteau and isHeader, if root holds the conditions then it gets the state with the
 * name of HeaderRoot.
 * Ex :  </title>
 * <p>
 * !isPlural, !isPortmanteau and isInterjection, if root holds the conditions then it gets the state
 * with the name of InterjectionRoot.
 * Ex : Hey, Aa
 * <p>
 * !isPlural, !isPortmanteau and isDuplicate, if root holds the conditions then it gets the state
 * with the name of DuplicateRoot.
 * Ex : Allak,
 * <p>
 * !isPlural, !isPortmanteau and isNumeral, if root holds the conditions then it gets the state
 * with the name of CardinalRoot.
 * Ex : Yüz, bin
 * <p>
 * !isPlural, !isPortmanteau and isReal, if root holds the conditions then it gets the state
 * with the name of RealRoot.
 * Ex : 1.2
 * <p>
 * !isPlural, !isPortmanteau and isFraction, if root holds the conditions then it gets the state
 * with the name of FractionRoot.
 * Ex : 1/2
 * <p>
 * !isPlural, !isPortmanteau and isDate, if root holds the conditions then it gets the state
 * with the name of DateRoot.
 * Ex : 11/06/2018
 * <p>
 * !isPlural, !isPortmanteau and isPercent, if root holds the conditions then it gets the state
 * with the name of PercentRoot.
 * Ex : %12.5
 * <p>
 * !isPlural, !isPortmanteau and isRange, if root holds the conditions then it gets the state
 * with the name of RangeRoot.
 * Ex : 3-5
 * <p>
 * !isPlural, !isPortmanteau and isTime, if root holds the conditions then it gets the state
 * with the name of TimeRoot.
 * Ex : 13:16:08
 * <p>
 * !isPlural, !isPortmanteau and isOrdinal, if root holds the conditions then it gets the state
 * with the name of OrdinalRoot.
 * Ex : Altıncı
 * <p>
 * !isPlural, !isPortmanteau, and isVerb if root holds the conditions then it gets the state
 * with the name of VerbalRoot. Or isPassive, then it gets the state with the name of PassiveHn.
 * Ex : Anla (!isPAssive)
 * Ex : Çağrıl (isPassive)
 * <p>
 * !isPlural, !isPortmanteau and isPronoun, if root holds the conditions then it gets the state
 * with the name of PronounRoot. There are 6 different Pronoun state names, REFLEX, QUANT, QUANTPLURAL, DEMONS, PERS, QUES.
 * REFLEX = Reflexive Pronouns Ex : kendi
 * QUANT = Quantitative Pronouns Ex : öbür, hep, kimse, hiçbiri, bazı, kimi, biri
 * QUANTPLURAL = Quantitative Plural Pronouns Ex : tümü, çoğu, hepsi
 * DEMONS = Demonstrative Pronouns Ex : o, bu, şu
 * PERS = Personal Pronouns Ex : ben, sen, o, biz, siz, onlar
 * QUES = Interrogatıve Pronouns Ex : nere, ne, kim, hangi
 * <p>
 * !isPlural, !isPortmanteau and isAdjective, if root holds the conditions then it gets the state
 * with the name of AdjectiveRoot.
 * Ex : Absürt, Abes
 * <p>
 * !isPlural, !isPortmanteau and isPureAdjective, if root holds the conditions then it gets the state
 * with the name of Adjective.
 * Ex : Geçmiş, Cam
 * <p>
 * !isPlural, !isPortmanteau and isNominal, if root holds the conditions then it gets the state
 * with the name of NominalRoot.
 * Ex : Görüş
 * <p>
 * !isPlural, !isPortmanteau and isProper, if root holds the conditions then it gets the state
 * with the name of ProperRoot.
 * Ex : Abdi
 * <p>
 * !isPlural, !isPortmanteau and isQuestion, if root holds the conditions then it gets the state
 * with the name of QuestionRoot.
 * Ex : Mi, mü
 * <p>
 * !isPlural, !isPortmanteau and isDeterminer, if root holds the conditions then it gets the state
 * with the name of DeterminerRoot.
 * Ex : Çok, bir
 * <p>
 * !isPlural, !isPortmanteau and isConjunction, if root holds the conditions then it gets the state
 * with the name of ConjunctionRoot.
 * Ex : Ama , ancak
 * <p>
 * !isPlural, !isPortmanteau and isPostP, if root holds the conditions then it gets the state
 * with the name of PostP.
 * Ex : Ait, dair
 * <p>
 * !isPlural, !isPortmanteau and isAdverb, if root holds the conditions then it gets the state
 * with the name of AdverbRoot.
 * Ex : Acilen
 *
 * @param fsmParse ArrayList to initialize.
 * @param root     word to check properties and add to fsmParse according to them.
 * @param isProper is used to check a word is proper or not.
 */
void FsmMorphologicalAnalyzer::initializeParseList(vector<FsmParse>& fsmParse, TxtWord *root, bool isProper) {
    FsmParse currentFsmParse;
    if (root->isPlural()) {
        currentFsmParse = FsmParse(root, finiteStateMachine.getState("NominalRootPlural"));
        fsmParse.push_back(currentFsmParse);
    } else {
        if (root->isPortmanteauEndingWithSI()) {
            currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()), finiteStateMachine.getState("CompoundNounRoot"));
            fsmParse.push_back(currentFsmParse);
            currentFsmParse = FsmParse(root, finiteStateMachine.getState("NominalRootNoPossesive"));
            fsmParse.push_back(currentFsmParse);
        } else {
            if (root->isPortmanteau()) {
                if (root->isPortmanteauFacedVowelEllipsis()){
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("NominalRootNoPossesive"));
                    fsmParse.push_back(currentFsmParse);
                    currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()) + Word::lastChar(root->getName()) + Word::charAt(root->getName(), Word::size(root->getName()) - 2), finiteStateMachine.getState("CompoundNounRoot"));
                } else {
                    if (root->isPortmanteauFacedSoftening()){
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("NominalRootNoPossesive"));
                        fsmParse.push_back(currentFsmParse);
                        string lastBefore = Word::charAt(root->getName(), Word::size(root->getName()) - 2);
                        if (lastBefore == "b"){
                            currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()) + "p", finiteStateMachine.getState("CompoundNounRoot"));
                        } else {
                            if (lastBefore == "c"){
                                currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()) + "ç", finiteStateMachine.getState("CompoundNounRoot"));
                            } else {
                                if (lastBefore == "d"){
                                    currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()) + "t", finiteStateMachine.getState("CompoundNounRoot"));
                                } else {
                                    if (lastBefore == "ğ"){
                                        currentFsmParse = FsmParse(Word::substringExceptLastTwoChars(root->getName()) + "k", finiteStateMachine.getState("CompoundNounRoot"));
                                    } else {
                                        currentFsmParse = FsmParse(Word::substringExceptLastChar(root->getName()), finiteStateMachine.getState("CompoundNounRoot"));
                                    }
                                }
                            }
                        }
                    } else {
                        currentFsmParse = FsmParse(Word::substringExceptLastChar(root->getName()), finiteStateMachine.getState("CompoundNounRoot"));
                    }
                }
                fsmParse.push_back(currentFsmParse);
            } else {
                if (root->isHeader()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("HeaderRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isInterjection()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("InterjectionRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isDuplicate()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("DuplicateRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isNumeral()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("CardinalRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isReal()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("RealRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isFraction()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("FractionRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isDate()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("DateRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isPercent()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("PercentRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isRange()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("RangeRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isTime()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("TimeRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isOrdinal()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("OrdinalRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isVerb() || root->isPassive()) {
                    if (!root->verbType().empty()) {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("VerbalRoot(" + root->verbType() + ")"));
                    } else {
                        if (!root->isPassive()) {
                            currentFsmParse = FsmParse(root, finiteStateMachine.getState("VerbalRoot"));
                        } else {
                            currentFsmParse = FsmParse(root, finiteStateMachine.getState("PassiveHn"));
                        }
                    }
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isPronoun()) {
                    if (root->getName() == "kendi") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(REFLEX)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                    if (root->getName() == "öbür" || root->getName() == "öteki" || root->getName() == "hep" || root->getName() == "kimse" || root->getName() == "diğeri" || root->getName() == "hiçbiri" || root->getName() == "böylesi" || root->getName() == "birbiri" || root->getName() == "birbirleri" || root->getName() == "biri" || root->getName() == "başkası" || root->getName() == "bazı" || root->getName() == "kimi") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(QUANT)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                    if (root->getName() == "tümü" || root->getName() == "topu" || root->getName() == "herkes" || root->getName() == "cümlesi" || root->getName() == "çoğu" || root->getName() == "birçoğu" || root->getName() == "birkaçı" || root->getName() == "birçokları" || root->getName() == "hepsi") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(QUANTPLURAL)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                    if (root->getName() == "o" || root->getName() == "bu" || root->getName() == "şu") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(DEMONS)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                    if (root->getName() == "ben" || root->getName() == "sen" || root->getName() == "o" || root->getName() == "biz" || root->getName() == "siz" || root->getName() == "onlar") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(PERS)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                    if (root->getName() == "nere" || root->getName() == "ne" || root->getName() == "kaçı" || root->getName() == "kim" || root->getName() == "hangi") {
                        currentFsmParse = FsmParse(root, finiteStateMachine.getState("PronounRoot(QUES)"));
                        fsmParse.push_back(currentFsmParse);
                    }
                }
                if (root->isAdjective()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("AdjectiveRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isPureAdjective()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("Adjective"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isNominal()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("NominalRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isProperNoun() && isProper) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("ProperRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isQuestion()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("QuestionRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isDeterminer()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("DeterminerRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isConjunction()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("ConjunctionRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isPostP()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("PostP"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isAdverb()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("AdverbRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
            }
        }
    }
}

/**
 * The initializeRootList method is used to create an {@link ArrayList} which consists of initial fsm parsings. First,
 * it calls getWordsWithPrefix methods by using input String surfaceForm and generates a {@link HashSet}. Then, traverses
 * this HashSet and uses each word as a root and calls initializeParseList method with this root and ArrayList.
 * <p>
 *
 * @param surfaceForm the String used to generate a HashSet of words.
 * @param isProper    is used to check a word is proper or not.
 * @return initialFsmParse ArrayList.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::initializeRootList(string surfaceForm, bool isProper) {
    TxtWord* root;
    vector<FsmParse> initialFsmParse;
    if (surfaceForm.empty()) {
        return initialFsmParse;
    }
    unordered_set<Word*> words = dictionaryTrie->getWordsWithPrefix(surfaceForm);
    for (Word* word : words) {
        root = (TxtWord*) word;
        initializeParseList(initialFsmParse, root, isProper);
        if (root->obeysAndNotObeysVowelHarmonyDuringAgglutination()){
            TxtWord* newRoot = root->clone();
            newRoot->removeFlag("IS_UU");
            newRoot->removeFlag("IS_UUU");
            initializeParseList(initialFsmParse, newRoot, isProper);
        }
        if (root->rootSoftenAndNotSoftenDuringSuffixation()){
            TxtWord* newRoot = root->clone();
            newRoot->removeFlag("IS_SD");
            newRoot->removeFlag("IS_SDD");
            initializeParseList(initialFsmParse, newRoot, isProper);
        }
        if (root->lastIDropsAndNotDropDuringSuffixation()){
            TxtWord* newRoot = root->clone();
            newRoot->removeFlag("IS_UD");
            newRoot->removeFlag("IS_UDD");
            initializeParseList(initialFsmParse, newRoot, isProper);
        }
        if (root->duplicatesAndNotDuplicatesDuringSuffixation()){
            TxtWord* newRoot = root->clone();
            newRoot->removeFlag("IS_ST");
            newRoot->removeFlag("IS_STT");
            initializeParseList(initialFsmParse, newRoot, isProper);
        }
        if (root->endingKChangesIntoG()){
            TxtWord* newRoot = root->clone();
            newRoot->removeFlag("IS_OA");
            initializeParseList(initialFsmParse, newRoot, isProper);
        }
    }
    return initialFsmParse;
}

/**
 * The addNewParsesFromCurrentParse method initially gets the final suffixes from input currentFsmParse called as currentState,
 * and by using the currentState information it gets the currentSurfaceForm. Then loops through each currentState's transition.
 * If the currentTransition is possible, it makes the transition
 *
 * @param currentFsmParse FsmParse type input.
 * @param fsmParse        an ArrayList of FsmParse.
 * @param surfaceForm     String to use during transition.
 * @param root            TxtWord used to make transition.
 */
void FsmMorphologicalAnalyzer::addNewParsesFromCurrentParse(FsmParse currentFsmParse, vector<FsmParse>& fsmParse,
                                                            string surfaceForm, TxtWord *root) {
    State currentState = currentFsmParse.getFinalSuffix();
    string currentSurfaceForm = currentFsmParse.getSurfaceForm();
    for (Transition currentTransition : finiteStateMachine.getTransitions(currentState)) {
        if (currentTransition.transitionPossible(currentFsmParse.getSurfaceForm(), surfaceForm) && currentTransition.transitionPossible(currentFsmParse) && (currentSurfaceForm != root->getName() || (currentSurfaceForm == root->getName() && currentTransition.transitionPossible(root, currentState)))) {
            string tmp = currentTransition.makeTransition(root, currentSurfaceForm, currentFsmParse.getStartState());
            if ((Word::size(tmp) < Word::size(surfaceForm) && isPossibleSubstring(tmp, surfaceForm, root)) || (Word::size(tmp) == Word::size(surfaceForm) && (root->lastIdropsDuringSuffixation() || (tmp == surfaceForm)))) {
                FsmParse newFsmParse = currentFsmParse.clone();
                newFsmParse.addSuffix(currentTransition.getToState(), tmp, currentTransition.getWith(), currentTransition.to_String(), currentTransition.getToPos());
                newFsmParse.setAgreement(currentTransition.getWith());
                fsmParse.push_back(newFsmParse);
            }
        }
    }
}

/**
 * The parseExists method is used to check the existence of the parse.
 *
 * @param fsmParse    an ArrayList of FsmParse
 * @param surfaceForm String to use during transition.
 * @return true when the currentState is end state and input surfaceForm id equal to currentSurfaceForm, otherwise false.
 */
bool FsmMorphologicalAnalyzer::parseExists(vector<FsmParse>& fsmParse, string surfaceForm) {
    FsmParse currentFsmParse;
    TxtWord* root;
    State currentState;
    string currentSurfaceForm;
    while (!fsmParse.empty()) {
        currentFsmParse = fsmParse.at(0);
        fsmParse.erase(fsmParse.begin());
        root = (TxtWord*) currentFsmParse.getWord();
        currentState = currentFsmParse.getFinalSuffix();
        currentSurfaceForm = currentFsmParse.getSurfaceForm();
        if (currentState.isEndState() && currentSurfaceForm == surfaceForm) {
            return true;
        }
        addNewParsesFromCurrentParse(currentFsmParse, fsmParse, surfaceForm, root);
    }
    return false;
}

/**
 * The parseWord method is used to parse a given fsmParse. It simply adds new parses to the current parse by
 * using addNewParsesFromCurrentParse method.
 *
 * @param fsmParse    an ArrayList of FsmParse
 * @param surfaceForm String to use during transition.
 * @return result {@link ArrayList} which has the currentFsmParse.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::parseWord(vector<FsmParse> fsmParse, string surfaceForm) {
    vector<FsmParse> result;
    FsmParse currentFsmParse;
    TxtWord* root;
    State currentState;
    string currentSurfaceForm;
    int i;
    bool exists;
    while (!fsmParse.empty()) {
        currentFsmParse = fsmParse.at(0);
        fsmParse.erase(fsmParse.begin());
        root = (TxtWord*) currentFsmParse.getWord();
        currentState = currentFsmParse.getFinalSuffix();
        currentSurfaceForm = currentFsmParse.getSurfaceForm();
        if (currentState.isEndState() && currentSurfaceForm == surfaceForm) {
            exists = false;
            for (i = 0; i < result.size(); i++) {
                if (currentFsmParse.getSuffixList() == result.at(i).getSuffixList()) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                result.push_back(currentFsmParse);
                currentFsmParse.constructInflectionalGroups();
            }
        }
        addNewParsesFromCurrentParse(currentFsmParse, fsmParse, surfaceForm, root);
    }
    return result;
}

/**
 * The morphologicalAnalysis with 3 inputs is used to initialize an {@link ArrayList} and add a new FsmParse
 * with given root and state.
 *
 * @param root        TxtWord input.
 * @param surfaceForm String input to use for parsing.
 * @param state       String input.
 * @return parseWord method with newly populated FsmParse ArrayList and input surfaceForm.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::morphologicalAnalysis(TxtWord *root, string surfaceForm, string state) {
    vector<FsmParse> initialFsmParse;
    initialFsmParse.emplace_back(FsmParse(root, finiteStateMachine.getState(move(state))));
    return parseWord(initialFsmParse, move(surfaceForm));
}

/**
 * The morphologicalAnalysis with 2 inputs is used to initialize an {@link ArrayList} and add a new FsmParse
 * with given root. Then it calls initializeParseList method to initialize list with newly created ArrayList, input root,
 * and input surfaceForm.
 *
 * @param root        TxtWord input.
 * @param surfaceForm String input to use for parsing.
 * @return parseWord method with newly populated FsmParse ArrayList and input surfaceForm.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::morphologicalAnalysis(TxtWord *root, string surfaceForm) {
    vector<FsmParse> initialFsmParse;
    initializeParseList(initialFsmParse, root, isProperNoun(surfaceForm));
    return parseWord(initialFsmParse, surfaceForm);
}

/**
 * The analysisExists method checks several cases. If the given surfaceForm is a punctuation or double then it
 * returns true. If it is not a root word, then it initializes the parse list and returns the parseExists method with
 * this newly initialized list and surfaceForm.
 *
 * @param rootWord    TxtWord root.
 * @param surfaceForm String input.
 * @param isProper    boolean variable indicates a word is proper or not.
 * @return true if surfaceForm is punctuation or double, otherwise returns parseExist method with given surfaceForm.
 */
bool FsmMorphologicalAnalyzer::analysisExists(TxtWord *rootWord, string surfaceForm, bool isProper) {
    vector<FsmParse> initialFsmParse;
    if (Word::isPunctuation(surfaceForm)) {
        return true;
    }
    if (isDouble(surfaceForm)) {
        return true;
    }
    if (rootWord != nullptr) {
        initializeParseList(initialFsmParse, rootWord, isProper);
    } else {
        initialFsmParse = initializeRootList(surfaceForm, isProper);
    }
    return parseExists(initialFsmParse, surfaceForm);
}

/**
 * The analysis method is used by the morphologicalAnalysis method. It gets String surfaceForm as an input and checks
 * its type such as punctuation, number or compares with the regex for date, fraction, percent, time, range, hashtag,
 * and mail or checks its variable type as integer or double. After finding the right case for given surfaceForm, it calls
 * constructInflectionalGroups method which creates sub-word units.
 *
 * @param surfaceForm String to analyse.
 * @param isProper    is used to indicate the proper words.
 * @return ArrayList type initialFsmParse which holds the analyses.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::analysis(string surfaceForm, bool isProper) {
    vector<FsmParse> initialFsmParse;
    FsmParse fsmParse;
    if (Word::isPunctuation(surfaceForm) && surfaceForm != "%") {
        fsmParse = FsmParse(surfaceForm, State(("Punctuation"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isNumber(surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("CardinalRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (regex_match(surfaceForm, regex("(\\d\\d|\\d)/(\\d\\d|\\d)/\\d+")) || regex_match(surfaceForm, regex("(\\d\\d|\\d)\\.(\\d\\d|\\d)\\.\\d+"))) {
        fsmParse = FsmParse(surfaceForm, State(("DateRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (regex_match(surfaceForm, regex("\\d+/\\d+"))) {
        fsmParse = FsmParse(surfaceForm, State(("FractionRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        fsmParse = FsmParse(surfaceForm, State(("DateRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (regex_match(surfaceForm, regex("\\d+\\\\/\\d+"))) {
        fsmParse = FsmParse(surfaceForm, State(("FractionRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (surfaceForm == "%" || regex_match(surfaceForm, regex("%(\\d\\d|\\d)")) || regex_match(surfaceForm, regex("%(\\d\\d|\\d)\\.\\d+"))) {
        fsmParse = FsmParse(surfaceForm, State(("PercentRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (regex_match(surfaceForm, regex("(\\d\\d|\\d):(\\d\\d|\\d):(\\d\\d|\\d)")) || regex_match(surfaceForm, regex("(\\d\\d|\\d):(\\d\\d|\\d)"))) {
        fsmParse = FsmParse(surfaceForm, State(("TimeRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (regex_match(surfaceForm, regex("\\d+-\\d+")) || regex_match(surfaceForm, regex("(\\d\\d|\\d):(\\d\\d|\\d)-(\\d\\d|\\d):(\\d\\d|\\d)")) || regex_match(surfaceForm, regex("(\\d\\d|\\d)\\.(\\d\\d|\\d)-(\\d\\d|\\d)\\.(\\d\\d|\\d)"))) {
        fsmParse = FsmParse(surfaceForm, State(("RangeRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (Word::startsWith(surfaceForm, "#")) {
        fsmParse = FsmParse(surfaceForm, State(("Hashtag"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (surfaceForm.find('@') != string::npos) {
        fsmParse = FsmParse(surfaceForm, State(("Email"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (Word::lastChar(surfaceForm) == "." && isInteger(Word::substringExceptLastChar(surfaceForm))) {
        fsmParse = FsmParse(stoi(Word::substringExceptLastChar(surfaceForm)), finiteStateMachine.getState("OrdinalRoot"));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isInteger(surfaceForm)) {
        fsmParse = FsmParse(stoi(surfaceForm), finiteStateMachine.getState("CardinalRoot"));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isDouble(surfaceForm)) {
        fsmParse = FsmParse(stof(surfaceForm), finiteStateMachine.getState("RealRoot"));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    initialFsmParse = initializeRootList(surfaceForm, isProper);
    vector<FsmParse> resultFsmParse = parseWord(initialFsmParse, surfaceForm);
    return resultFsmParse;
}

/**
 * The isProperNoun method takes surfaceForm String as input and checks its each char whether they are in the range
 * of letters between A to Z or one of the Turkish letters such as İ, Ü, Ğ, Ş, Ç, and Ö.
 *
 * @param surfaceForm String to check for proper noun.
 * @return false if surfaceForm is null or length of 0, return true if it is a letter.
 */
bool FsmMorphologicalAnalyzer::isProperNoun(string surfaceForm) {
    if (surfaceForm.empty()) {
        return false;
    }
    return (Word::charAt(surfaceForm, 0) >= "A" && Word::charAt(surfaceForm, 0) <= "Z") || Word::charAt(surfaceForm, 0) == "Ç" || Word::charAt(surfaceForm, 0) == "Ö" || Word::charAt(surfaceForm, 0) == "Ğ" || Word::charAt(surfaceForm, 0) == "Ü" || Word::charAt(surfaceForm, 0) == "Ş" || Word::charAt(surfaceForm, 0) == "İ"; // İ, Ü, Ğ, Ş, Ç, Ö
}

/**
 * The robustMorphologicalAnalysis is used to analyse surfaceForm String. First it gets the currentParse of the surfaceForm
 * then, if the size of the currentParse is 0, and given surfaceForm is a proper noun, it adds the surfaceForm
 * whose state name is ProperRoot to an {@link ArrayList}, of it is not a proper noon, it adds the surfaceForm
 * whose state name is NominalRoot to the {@link ArrayList}.
 *
 * @param surfaceForm String to analyse.
 * @return FsmParseList type currentParse which holds morphological analysis of the surfaceForm.
 */
FsmParseList FsmMorphologicalAnalyzer::robustMorphologicalAnalysis(string surfaceForm) {
    vector<FsmParse> fsmParse;
    FsmParseList currentParse;
    if (surfaceForm.empty()) {
        return FsmParseList();
    }
    currentParse = morphologicalAnalysis(surfaceForm);
    if (currentParse.size() == 0) {
        if (isProperNoun(surfaceForm)) {
            fsmParse.emplace_back(FsmParse(surfaceForm, finiteStateMachine.getState("ProperRoot")));
            return FsmParseList(parseWord(fsmParse, surfaceForm));
        } else {
            fsmParse.emplace_back(FsmParse(surfaceForm, finiteStateMachine.getState("NominalRoot")));
            return FsmParseList(parseWord(fsmParse, surfaceForm));
        }
    } else {
        return currentParse;
    }
}

/**
 * The morphologicalAnalysis is used for debug purposes.
 *
 * @param sentence  to get word from.
 * @param debugMode states whether in the debug mode.
 * @return FsmParseList type result.
 */
FsmParseList *FsmMorphologicalAnalyzer::morphologicalAnalysis(Sentence sentence, bool debugMode) {
    FsmParseList wordFsmParseList;
    auto* result = new FsmParseList[sentence.wordCount()];
    for (int i = 0; i < sentence.wordCount(); i++) {
        wordFsmParseList = morphologicalAnalysis(sentence.getWord(i)->getName());
        if (wordFsmParseList.size() == 0 && debugMode) {
            cout << "Word " + sentence.getWord(i)->getName() + " can not be parsed\n";
        }
        result[i] = wordFsmParseList;
    }
    return result;
}

/**
 * The robustMorphologicalAnalysis method takes just one argument as an input. It gets the name of the words from
 * input sentence then calls robustMorphologicalAnalysis with surfaceForm.
 *
 * @param sentence Sentence type input used to get surfaceForm.
 * @return FsmParseList array which holds the result of the analysis.
 */
FsmParseList *FsmMorphologicalAnalyzer::robustMorphologicalAnalysis(Sentence sentence) {
    FsmParseList fsmParseList;
    auto* result = new FsmParseList[sentence.wordCount()];
    for (int i = 0; i < sentence.wordCount(); i++) {
        fsmParseList = robustMorphologicalAnalysis(sentence.getWord(i)->getName());
        result[i] = fsmParseList;
    }
    return result;
}

/**
 * The isInteger method compares input surfaceForm with regex \+?\d+ and returns the result.
 * Supports positive integer checks only.
 *
 * @param surfaceForm String to check.
 * @return true if surfaceForm matches with the regex.
 */
bool FsmMorphologicalAnalyzer::isInteger(string surfaceForm) {
    if (!regex_match(surfaceForm, regex("\\+?\\d+"))){
        return false;
    }
    int len = Word::size(surfaceForm);
    if (len < 10) {
        return true;        //Most common scenario. Return after a single check.
    } else {
        if (len > 10) {
            return false;
        } else {
            try {
                stoi(surfaceForm);
                return true;
            }
            catch (invalid_argument& e){
                return false;
            }
        }
    }
}

/**
 * The isDouble method compares input surfaceForm with regex \+?(\d+)?\.\d* and returns the result.
 *
 * @param surfaceForm String to check.
 * @return true if surfaceForm matches with the regex.
 */
bool FsmMorphologicalAnalyzer::isDouble(string surfaceForm) {
    return regex_match(surfaceForm, regex("\\+?(\\d+)?\\.\\d*"));
}

/**
 * The isNumber method compares input surfaceForm with the array of written numbers and returns the result.
 *
 * @param surfaceForm String to check.
 * @return true if surfaceForm matches with the regex.
 */
bool FsmMorphologicalAnalyzer::isNumber(string surfaceForm) {
    bool found;
    int count = 0;
    string numbers[] = {"bir", "iki", "üç", "dört", "beş", "altı", "yedi", "sekiz", "dokuz",
                        "on", "yirmi", "otuz", "kırk", "elli", "altmış", "yetmiş", "seksen", "doksan",
                        "yüz", "bin", "milyon", "milyar", "trilyon", "katrilyon"};
    string word = move(surfaceForm);
    while (!word.empty()) {
        found = false;
        for (const string &number : numbers) {
            if (Word::startsWith(word, number)) {
                found = true;
                count++;
                word = Word::substring(word, 0, Word::size(number));
                break;
            }
        }
        if (!found) {
            break;
        }
    }
    return word.empty() && count > 1;
}

/**
 * The morphologicalAnalysisExists method calls analysisExists to check the existence of the analysis with given
 * root and surfaceForm.
 *
 * @param surfaceForm String to check.
 * @param rootWord    TxtWord input root.
 * @return true an analysis exists, otherwise return false.
 */
bool FsmMorphologicalAnalyzer::morphologicalAnalysisExists(TxtWord *rootWord, string surfaceForm) {
    return analysisExists(rootWord, Word::toLowerCase(surfaceForm), true);
}

/**
 * The morphologicalAnalysis method is used to analyse a FsmParseList by comparing with the regex.
 * It creates an {@link ArrayList} fsmParse to hold the result of the analysis method. For each surfaceForm input,
 * it gets a substring and considers it as a possibleRoot. Then compares with the regex.
 * <p>
 * If the surfaceForm input string matches with Turkish chars like Ç, Ş, İ, Ü, Ö, it adds the surfaceForm to Trie with IS_OA tag.
 * If the possibleRoot contains /, then it is added to the Trie with IS_KESIR tag.
 * If the possibleRoot contains \d\d|\d)/(\d\d|\d)/\d+, then it is added to the Trie with IS_DATE tag.
 * If the possibleRoot contains \\d\d|\d, then it is added to the Trie with IS_PERCENT tag.
 * If the possibleRoot contains \d\d|\d):(\d\d|\d):(\d\d|\d), then it is added to the Trie with IS_ZAMAN tag.
 * If the possibleRoot contains \d+-\d+, then it is added to the Trie with IS_RANGE tag.
 * If the possibleRoot is an Integer, then it is added to the Trie with IS_SAYI tag.
 * If the possibleRoot is a Double, then it is added to the Trie with IS_REELSAYI tag.
 *
 * @param surfaceForm String to analyse.
 * @return fsmParseList which holds the analysis.
 */
FsmParseList FsmMorphologicalAnalyzer::morphologicalAnalysis(string surfaceForm) {
    FsmParseList fsmParseList;
    if (cache.contains(surfaceForm)) {
        return cache.get(surfaceForm);
    }
    if (regex_match(surfaceForm, regex("(\\w|Ç|Ş|İ|Ü|Ö)\\."))) {
        dictionaryTrie->addWord(Word::toLowerCase(surfaceForm), new TxtWord(Word::toLowerCase(surfaceForm), "IS_OA"));
    }
    vector<FsmParse> defaultFsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
    if (!defaultFsmParse.empty()) {
        fsmParseList = FsmParseList(defaultFsmParse);
        cache.add(surfaceForm, fsmParseList);
        return fsmParseList;
    }
    vector<FsmParse> fsmParse;
    if (surfaceForm.find('\'') != string::npos) {
        string possibleRoot = surfaceForm.substr(0, surfaceForm.find('\''));
        if (!possibleRoot.empty()) {
            if (possibleRoot.find('/') != string::npos || possibleRoot.find("\\/") != string::npos) {
                dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_KESIR"));
                fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
            } else {
                if (regex_match(possibleRoot, regex("(\\d\\d|\\d)/(\\d\\d|\\d)/\\d+")) || regex_match(possibleRoot, regex("(\\d\\d|\\d)\\.(\\d\\d|\\d)\\.\\d+"))) {
                    dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_DATE"));
                    fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                } else {
                    if (regex_match(possibleRoot, regex("\\d+/\\d+"))) {
                        dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_KESIR"));
                        fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                    } else {
                        if (regex_match(possibleRoot, regex("%(\\d\\d|\\d)")) || regex_match(possibleRoot, regex("%(\\d\\d|\\d)\\.\\d+"))) {
                            dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_PERCENT"));
                            fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                        } else {
                            if (regex_match(possibleRoot, regex("(\\d\\d|\\d):(\\d\\d|\\d):(\\d\\d|\\d)")) || regex_match(possibleRoot, regex("(\\d\\d|\\d):(\\d\\d|\\d)"))) {
                                dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_ZAMAN"));
                                fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                            } else {
                                if (regex_match(possibleRoot, regex("\\d+-\\d+")) || regex_match(possibleRoot, regex("(\\d\\d|\\d):(\\d\\d|\\d)-(\\d\\d|\\d):(\\d\\d|\\d)")) || regex_match(possibleRoot, regex("(\\d\\d|\\d)\\.(\\d\\d|\\d)-(\\d\\d|\\d)\\.(\\d\\d|\\d)"))) {
                                    dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_RANGE"));
                                    fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                                } else {
                                    if (isInteger(possibleRoot)) {
                                        dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_SAYI"));
                                        fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                                    } else {
                                        if (isDouble(possibleRoot)) {
                                            dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_REELSAYI"));
                                            fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                                        } else {
                                            if (Word::isCapital(possibleRoot)) {
                                                TxtWord* newWord = nullptr;
                                                if (dictionary.getWord(Word::toLowerCase(surfaceForm)) != nullptr) {
                                                    ((TxtWord*) dictionary.getWord(Word::toLowerCase(surfaceForm)))->addFlag("IS_OA");
                                                } else {
                                                    newWord = new TxtWord(Word::toLowerCase(surfaceForm), "IS_OA");
                                                    dictionaryTrie->addWord(Word::toLowerCase(surfaceForm), newWord);
                                                }
                                                fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                                                if (fsmParse.empty() && newWord != nullptr) {
                                                    newWord->addFlag("IS_KIS");
                                                    fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
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
    fsmParseList = FsmParseList(fsmParse);
    cache.add(surfaceForm, fsmParseList);
    return fsmParseList;
}
