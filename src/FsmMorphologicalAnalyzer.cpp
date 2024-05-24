//
// Created by Olcay Taner Yıldız on 2.03.2019.
//
#include <regex>
#include <iostream>
#include <fstream>
#include <queue>
#include "FsmMorphologicalAnalyzer.h"

using namespace std;

/**
 * Another constructor of FsmMorphologicalAnalyzer class. It generates a new TxtDictionary type dictionary from
 * given input dictionary, with given inputs fileName and cacheSize.
 *
 * @param fileName   the file to read the finite state machine.
 * @param dictionary the dictionary file that will be used to generate dictionaryTrie.
 * @param cacheSize  the size of the LRUCache.
 */
FsmMorphologicalAnalyzer::FsmMorphologicalAnalyzer(const string& fileName, TxtDictionary* dictionary, int cacheSize) {
    finiteStateMachine = FiniteStateMachine(fileName);
    dictionaryTrie = dictionary->prepareTrie();
    prepareSuffixTrie();
    this->dictionary = dictionary;
    cache = LRUCache<string, FsmParseList>(cacheSize);
}

/**
 * Another constructor of FsmMorphologicalAnalyzer class. It generates a new TxtDictionary type dictionary from
 * given input dictionary file name and by using turkish_finite_state_machine.xml file.
 *
 * @param fileName           the file to read the finite state machine.
 * @param dictionaryFileName the file to read the dictionary.
 */
FsmMorphologicalAnalyzer::FsmMorphologicalAnalyzer(const string& dictionaryFileName, const string& fileName) : FsmMorphologicalAnalyzer(fileName, new TxtDictionary(dictionaryFileName, "turkish_misspellings.txt")){
}

/**
 * Constructs and returns the reverse string of a given string.
 * @param s String to be reversed.
 * @return Reverse of a given string.
 */
string FsmMorphologicalAnalyzer::reverseString(const string& s) const{
    string result;
    for (int i = s.size() - 1; i >= 0; i--){
        result += Word::charAt(s, i);
    }
    return result;
}

/**
 * Constructs the suffix trie from the input file suffixes.txt. suffixes.txt contains the most frequent 6000
 * suffixes that a verb or a noun can take. The suffix trie is a trie that stores these suffixes in reverse form,
 * which can be then used to match a given word for its possible suffix content.
 */
void FsmMorphologicalAnalyzer::prepareSuffixTrie() {
    ifstream inputFile;
    string suffix;
    suffixTrie = new Trie();
    inputFile.open("suffixes.txt", ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, suffix);
        string reverseSuffix = reverseString(suffix);
        suffixTrie->addWord(reverseSuffix, new Word(reverseSuffix));
    }
    inputFile.close();
}

/**
 * Reads the file for correct surface forms and their most frequent root forms, in other words, the surface forms
 * which have at least one morphological analysis in  Turkish.
 * @param fileName Input file containing analyzable surface forms and their root forms.
 */
void FsmMorphologicalAnalyzer::addSurfaceForms(const string& fileName) {
    ifstream inputFile;
    string line;
    inputFile.open(fileName, ifstream :: in);
    while (inputFile.good()) {
        getline(inputFile, line);
        vector<string> items = TxtWord::split(line);
        parsedSurfaceForms.emplace(items[0], items[1]);
    }
    inputFile.close();
}

/**
 * The getDictionary method is used to get TxtDictionary.
 *
 * @return TxtDictionary type dictionary.
 */
TxtDictionary* FsmMorphologicalAnalyzer::getDictionary() const{
    return dictionary;
}

/**
 * The getFiniteStateMachine method is used to get FiniteStateMachine.
 *
 * @return FiniteStateMachine type finiteStateMachine.
 */
FiniteStateMachine FsmMorphologicalAnalyzer::getFiniteStateMachine() const{
    return finiteStateMachine;
}

/**
 * The getPossibleWords method takes MorphologicalParse and MetamorphicParse as input.
 * First it determines whether the given morphologicalParse is the root verb and whether it contains a verb tag.
 * Then it creates new transition with -mak and creates a new HashSet result.
 * <p>
 * It takes the given MetamorphicParse input as currentWord and if there is a compound word starting with the
 * currentWord, it gets this compoundWord from dictionaryTrie. If there is a compoundWord and the difference of the
 * currentWord and compundWords is less than 3 than compoundWord is added to the result, otherwise currentWord is added.
 * <p>
 * Then it gets the root from parse input as a currentRoot. If it is not null, and morphologicalParse input is verb,
 * it directly adds the verb to result after making transition to currentRoot with currentWord String. Else, it creates a new
 * transition with -lar and make this transition then adds to the result.
 *
 * @param morphologicalParse MorphologicalParse type input.
 * @param parse              MetamorphicParse type input.
 * @return HashSet result.
 */
unordered_set<string>
FsmMorphologicalAnalyzer::getPossibleWords(const MorphologicalParse& morphologicalParse, const MetamorphicParse& parse) {
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
        if (compoundWord != nullptr && Word::size(compoundWord->getName()) - Word::size(currentWord) < 3) {
            result.emplace(compoundWord->getName());
        }
        result.emplace(currentWord);
    }
    currentRoot = (TxtWord*) dictionary->getWord(parse.getWord().getName());
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
bool FsmMorphologicalAnalyzer::isPossibleSubstring(const string& shortString, const string& longString, TxtWord *root) const{
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
    if (rootWord && (root->getName() == "ben" || root->getName() == "sen" || root->lastIdropsDuringSuffixation() || root->lastIdropsDuringPassiveSuffixation())) {
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
 * !isPlural, !isPortmanteau and isCode, if root holds the conditions then it gets the state
 * with the name of CodeRoot.
 * Ex : 9400f,
 * <p>
 * !isPlural, !isPortmanteau and isMetric, if root holds the conditions then it gets the state
 * with the name of MetricRoot.
 * Ex : 11x8x12,
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
void FsmMorphologicalAnalyzer::initializeParseList(vector<FsmParse>& fsmParse, TxtWord *root, bool isProper) const{
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
                if (root->isCode()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("CodeRoot"));
                    fsmParse.push_back(currentFsmParse);
                }
                if (root->isMetric()) {
                    currentFsmParse = FsmParse(root, finiteStateMachine.getState("MetricRoot"));
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
                if (root->isAbbreviation()) {
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
 * The initializeParseListFromRoot method is used to create an ArrayList which consists of initial fsm parsings. First, traverses
 * this HashSet and uses each word as a root and calls initializeParseList method with this root and ArrayList.
 * <p>
 *
 * @param parseList ArrayList to initialize.
 * @param root the root form to generate initial parse list.
 * @param isProper    is used to check a word is proper or not.
 */
void FsmMorphologicalAnalyzer::initializeParseListFromRoot(vector<FsmParse>& parseList, TxtWord *root, bool isProper) const{
    initializeParseList(parseList, root, isProper);
    if (root->obeysAndNotObeysVowelHarmonyDuringAgglutination()){
        TxtWord* newRoot = root->clone();
        newRoot->removeFlag("IS_UU");
        newRoot->removeFlag("IS_UUU");
        initializeParseList(parseList, newRoot, isProper);
    }
    if (root->rootSoftenAndNotSoftenDuringSuffixation()){
        TxtWord* newRoot = root->clone();
        newRoot->removeFlag("IS_SD");
        newRoot->removeFlag("IS_SDD");
        initializeParseList(parseList, newRoot, isProper);
    }
    if (root->lastIDropsAndNotDropDuringSuffixation()){
        TxtWord* newRoot = root->clone();
        newRoot->removeFlag("IS_UD");
        newRoot->removeFlag("IS_UDD");
        initializeParseList(parseList, newRoot, isProper);
    }
    if (root->duplicatesAndNotDuplicatesDuringSuffixation()){
        TxtWord* newRoot = root->clone();
        newRoot->removeFlag("IS_ST");
        newRoot->removeFlag("IS_STT");
        initializeParseList(parseList, newRoot, isProper);
    }
    if (root->endingKChangesIntoG() && root->containsFlag("IS_OA")){
        TxtWord* newRoot = root->clone();
        newRoot->removeFlag("IS_OA");
        initializeParseList(parseList, newRoot, isProper);
    }
}

/**
 * The initializeRootList method is used to create an ArrayList which consists of initial fsm parsings. First,
 * it calls getWordsWithPrefix methods by using input String surfaceForm and generates a HashSet. Then, traverses
 * this HashSet and uses each word as a root and calls initializeParseList method with this root and ArrayList.
 * <p>
 *
 * @param surfaceForm the String used to generate a HashSet of words.
 * @param isProper    is used to check a word is proper or not.
 * @return initialFsmParse ArrayList.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::initializeParseListFromSurfaceForm(const string& surfaceForm, bool isProper) {
    TxtWord* root;
    vector<FsmParse> initialFsmParse;
    if (surfaceForm.empty()) {
        return initialFsmParse;
    }
    unordered_set<Word*> words = dictionaryTrie->getWordsWithPrefix(surfaceForm);
    for (Word* word : words) {
        root = (TxtWord*) word;
        initializeParseListFromRoot(initialFsmParse, root, isProper);
    }
    return initialFsmParse;
}

/**
 * The addNewParsesFromCurrentParse method initially gets the final suffixes from input currentFsmParse called as currentState,
 * and by using the currentState information it gets the new analysis. Then loops through each currentState's transition.
 * If the currentTransition is possible, it makes the transition
 *
 * @param currentFsmParse FsmParse type input.
 * @param fsmParse        an ArrayList of FsmParse.
 * @param surfaceForm     String to use during transition.
 * @param root            TxtWord used to make transition.
 */
void FsmMorphologicalAnalyzer::addNewParsesFromCurrentParse(const FsmParse& currentFsmParse, deque<FsmParse>& fsmParse,
                                                            int maxLength, TxtWord *root) const{
    State currentState = currentFsmParse.getFinalSuffix();
    string currentSurfaceForm = currentFsmParse.getSurfaceForm();
    for (const Transition& currentTransition : finiteStateMachine.getTransitions(currentState)) {
        if (currentTransition.transitionPossible(currentFsmParse) && (currentSurfaceForm != root->getName() || (currentSurfaceForm == root->getName() && currentTransition.transitionPossible(root, currentState)))) {
            string tmp = currentTransition.makeTransition(root, currentSurfaceForm, currentFsmParse.getStartState());
            if (Word::size(tmp) <= maxLength) {
                FsmParse newFsmParse = currentFsmParse.clone();
                newFsmParse.addSuffix(currentTransition.getToState(), tmp, currentTransition.getWith(), currentTransition.to_String(), currentTransition.getToPos());
                newFsmParse.setAgreement(currentTransition.getWith());
                fsmParse.push_back(newFsmParse);
            }
        }
    }
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
void FsmMorphologicalAnalyzer::addNewParsesFromCurrentParse(const FsmParse& currentFsmParse, deque<FsmParse>& fsmParse,
                                                            const string& surfaceForm, TxtWord *root) const{
    State currentState = currentFsmParse.getFinalSuffix();
    string currentSurfaceForm = currentFsmParse.getSurfaceForm();
    for (const Transition& currentTransition : finiteStateMachine.getTransitions(currentState)) {
        if (currentTransition.transitionPossible(currentFsmParse.getSurfaceForm(), surfaceForm) && currentTransition.transitionPossible(currentFsmParse) && (currentSurfaceForm != root->getName() || (currentSurfaceForm == root->getName() && currentTransition.transitionPossible(root, currentState)))) {
            string tmp = currentTransition.makeTransition(root, currentSurfaceForm, currentFsmParse.getStartState());
            if ((Word::size(tmp) < Word::size(surfaceForm) && isPossibleSubstring(tmp, surfaceForm, root)) || (Word::size(tmp) == Word::size(surfaceForm) && (root->lastIdropsDuringSuffixation() || tmp == surfaceForm))) {
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
bool FsmMorphologicalAnalyzer::parseExists(vector<FsmParse>& fsmParse, const string& surfaceForm) const{
    FsmParse currentFsmParse;
    TxtWord* root;
    State currentState;
    string currentSurfaceForm;
    deque<FsmParse> parseQueue = deque(fsmParse.begin(), fsmParse.end());
    while (!parseQueue.empty()) {
        currentFsmParse = parseQueue.front();
        parseQueue.pop_front();
        root = (TxtWord*) currentFsmParse.getWord();
        currentState = currentFsmParse.getFinalSuffix();
        currentSurfaceForm = currentFsmParse.getSurfaceForm();
        if (currentState.isEndState() && currentSurfaceForm == surfaceForm) {
            return true;
        }
        addNewParsesFromCurrentParse(currentFsmParse, parseQueue, surfaceForm, root);
    }
    return false;
}

/**
 * The parseWord method is used to parse a given fsmParse. It simply adds new parses to the current parse by
 * using addNewParsesFromCurrentParse method.
 *
 * @param fsmParse    an ArrayList of FsmParse
 * @param maxLength maximum length of the surfaceform.
 * @return result ArrayList which has the currentFsmParse.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::parseWord(vector<FsmParse> fsmParse, int maxLength) const{
    vector<FsmParse> result;
    vector<string> resultSuffixList;
    FsmParse currentFsmParse;
    TxtWord* root;
    State currentState;
    string currentSurfaceForm;
    string currentSuffixList;
    deque<FsmParse> parseQueue = deque(fsmParse.begin(), fsmParse.end());
    while (!parseQueue.empty()) {
        currentFsmParse = parseQueue.front();
        parseQueue.pop_front();
        root = (TxtWord*) currentFsmParse.getWord();
        currentState = currentFsmParse.getFinalSuffix();
        currentSurfaceForm = currentFsmParse.getSurfaceForm();
        if (currentState.isEndState() && Word::size(currentSurfaceForm) <= maxLength) {
            currentSuffixList = currentFsmParse.getSuffixList();
            if (find(resultSuffixList.begin(), resultSuffixList.end(), currentSuffixList) == resultSuffixList.end()) {
                currentFsmParse.constructInflectionalGroups();
                result.push_back(currentFsmParse);
                resultSuffixList.push_back(currentSuffixList);
            }
        }
        addNewParsesFromCurrentParse(currentFsmParse, parseQueue, maxLength, root);
    }
    return result;
}

/**
 * The parseWord method is used to parse a given fsmParse. It simply adds new parses to the current parse by
 * using addNewParsesFromCurrentParse method.
 *
 * @param fsmParse    an ArrayList of FsmParse
 * @param surfaceForm String to use during transition.
 * @return result ArrayList which has the currentFsmParse.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::parseWord(vector<FsmParse> fsmParse, const string& surfaceForm) const{
    vector<FsmParse> result;
    vector<string> resultSuffixList;
    FsmParse currentFsmParse;
    TxtWord* root;
    State currentState;
    string currentSurfaceForm;
    string currentSuffixList;
    deque<FsmParse> parseQueue = deque(fsmParse.begin(), fsmParse.end());
    while (!parseQueue.empty()) {
        currentFsmParse = parseQueue.front();
        parseQueue.pop_front();
        root = (TxtWord*) currentFsmParse.getWord();
        currentState = currentFsmParse.getFinalSuffix();
        currentSurfaceForm = currentFsmParse.getSurfaceForm();
        if (currentState.isEndState() && currentSurfaceForm == surfaceForm) {
            currentSuffixList = currentFsmParse.getSuffixList();
            if (find(resultSuffixList.begin(), resultSuffixList.end(), currentSuffixList) == resultSuffixList.end()) {
                currentFsmParse.constructInflectionalGroups();
                result.push_back(currentFsmParse);
                resultSuffixList.push_back(currentSuffixList);
            }
        }
        addNewParsesFromCurrentParse(currentFsmParse, parseQueue, surfaceForm, root);
    }
    return result;
}

/**
 * The morphologicalAnalysis with 3 inputs is used to initialize an ArrayList and add a new FsmParse
 * with given root and state.
 *
 * @param root        TxtWord input.
 * @param surfaceForm String input to use for parsing.
 * @param state       String input.
 * @return parseWord method with newly populated FsmParse ArrayList and input surfaceForm.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::morphologicalAnalysis(TxtWord *root, const string& surfaceForm, const string& state) {
    vector<FsmParse> initialFsmParse;
    initialFsmParse.emplace_back(FsmParse(root, finiteStateMachine.getState(state)));
    return parseWord(initialFsmParse, surfaceForm);
}

/**
 * The generateAllParses with 2 inputs is used to generate all parses with given root. Then it calls initializeParseListFromRoot method to initialize list with newly created ArrayList, input root,
 * and maximum length.
 *
 * @param root        TxtWord input.
 * @param maxLength Maximum length of the surface form.
 * @return parseWord method with newly populated FsmParse ArrayList and maximum length.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::generateAllParses(TxtWord *root, int maxLength) {
    vector<FsmParse> initialFsmParse;
    if (root->isProperNoun()){
        initializeParseListFromRoot(initialFsmParse, root, true);
    }
    initializeParseListFromRoot(initialFsmParse, root, false);
    return parseWord(initialFsmParse, maxLength);
}

/**
 * The morphologicalAnalysis with 2 inputs is used to initialize an ArrayList and add a new FsmParse
 * with given root. Then it calls initializeParseList method to initialize list with newly created ArrayList, input root,
 * and input surfaceForm.
 *
 * @param root        TxtWord input.
 * @param surfaceForm String input to use for parsing.
 * @return parseWord method with newly populated FsmParse ArrayList and input surfaceForm.
 */
vector<FsmParse> FsmMorphologicalAnalyzer::morphologicalAnalysis(TxtWord *root, const string& surfaceForm) {
    vector<FsmParse> initialFsmParse;
    initializeParseListFromRoot(initialFsmParse, root, isProperNoun(surfaceForm));
    return parseWord(initialFsmParse, surfaceForm);
}

/**
 * Replaces previous lemma in the sentence with the new lemma. Both lemma can contain multiple words.
 * @param original Original sentence to be replaced with.
 * @param previousWord Root word in the original sentence
 * @param newWord New word to be replaced.
 * @return Newly generated sentence by replacing the previous word in the original sentence with the new word.
 */
Sentence* FsmMorphologicalAnalyzer::replaceWord(Sentence* original, const string& previousWord, const string& newWord){
    int i;
    vector<string> previousWordSplitted, newWordSplitted;
    auto* result = new Sentence();
    string replacedWord, lastWord, newRootWord;
    bool previousWordMultiple = previousWord.find(' ') != std::string::npos;
    bool newWordMultiple = newWord.find(' ') != std::string::npos;
    if (previousWordMultiple){
        previousWordSplitted = Word::split(previousWord);
        lastWord = previousWordSplitted[previousWordSplitted.size() - 1];
    } else {
        lastWord = previousWord;
    }
    if (newWordMultiple){
        newWordSplitted = Word::split(newWord);
        newRootWord = newWordSplitted[newWordSplitted.size() - 1];
    } else {
        newRootWord = newWord;
    }
    auto* newRootTxtWord = (TxtWord*) dictionary->getWord(newRootWord);
    FsmParseList* parseList = morphologicalAnalysis(*original);
    for (i = 0; i < original->wordCount(); i++){
        bool replaced = false;
        for (int j = 0; j < parseList[i].size(); j++){
            if (parseList[i].getFsmParse(j).getWord()->getName() == lastWord && newRootTxtWord != nullptr){
                replaced = true;
                replacedWord = parseList[i].getFsmParse(j).replaceRootWord(newRootTxtWord);
            }
        }
        if (replaced && !replacedWord.empty()){
            if (previousWordMultiple){
                for (int k = 0; k < i - previousWordSplitted.size() + 1; k++){
                    result->addWord(original->getWord(k));
                }
            }
            if (newWordMultiple){
                for (int k = 0; k < newWordSplitted.size() - 1; k++){
                    if (result->wordCount() == 0){
                        result->addWord(new Word(Word::toUpperCase(Word::charAt(newWordSplitted[k], 0)) + Word::substring(newWordSplitted[k], 1)));
                    } else {
                        result->addWord(new Word(newWordSplitted[k]));
                    }
                }
            }
            if (result->wordCount() == 0){
                replacedWord = Word::toUpperCase(Word::charAt(replacedWord, 0)) + Word::substring(replacedWord, 1);
            }
            result->addWord(new Word(replacedWord));
            if (previousWordMultiple){
                i++;
                break;
            }
        } else {
            if (!previousWordMultiple){
                result->addWord(original->getWord(i));
            }
        }
    }
    if (previousWordMultiple){
        for (; i < original->wordCount(); i++){
            result->addWord(original->getWord(i));
        }
    }
    return result;
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
bool FsmMorphologicalAnalyzer::analysisExists(TxtWord *rootWord, const string& surfaceForm, bool isProper) {
    vector<FsmParse> initialFsmParse;
    if (Word::isPunctuation(surfaceForm)) {
        return true;
    }
    if (isDouble(surfaceForm)) {
        return true;
    }
    if (rootWord != nullptr) {
        initializeParseListFromRoot(initialFsmParse, rootWord, isProper);
    } else {
        initialFsmParse = initializeParseListFromSurfaceForm(surfaceForm, isProper);
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
vector<FsmParse> FsmMorphologicalAnalyzer::analysis(const string& surfaceForm, bool isProper) {
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
    if (patternMatches("\\d+/\\d+", surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("FractionRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        fsmParse = FsmParse(surfaceForm, State(("DateRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isDate(surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("DateRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (patternMatches(R"(\d+\\/\d+)", surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("FractionRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (surfaceForm == "%" || isPercent(surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("PercentRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isTime(surfaceForm)) {
        fsmParse = FsmParse(surfaceForm, State(("TimeRoot"), true, true));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    if (isRange(surfaceForm)) {
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
        fsmParse = FsmParse(stod(surfaceForm), surfaceForm, finiteStateMachine.getState("RealRoot"));
        fsmParse.constructInflectionalGroups();
        initialFsmParse.push_back(fsmParse);
        return initialFsmParse;
    }
    initialFsmParse = initializeParseListFromSurfaceForm(surfaceForm, isProper);
    vector<FsmParse> resultFsmParse = parseWord(initialFsmParse, surfaceForm);
    return resultFsmParse;
}

/**
 * This method uses cache idea to speed up pattern matching in Fsm. mostUsedPatterns stores the compiled forms of
 * the previously used patterns. When Fsm tries to match a string to a pattern, first we check if it exists in
 * mostUsedPatterns. If it exists, we directly use the compiled pattern to match the string. Otherwise, new pattern
 * is compiled and put in the mostUsedPatterns.
 * @param expr Pattern to check
 * @param value String to match the pattern
 * @return True if the string matches the pattern, false otherwise.
 */
bool FsmMorphologicalAnalyzer::patternMatches(const string& expr, const string& value){
    regex r;
    if (!mostUsedPatterns.contains(expr)){
        r = regex(expr);
        mostUsedPatterns.emplace(expr, r);
    } else {
        r = mostUsedPatterns.find(expr)->second;
    }
    return regex_match(value, r);
}

/**
 * The isProperNoun method takes surfaceForm String as input and checks its each char whether they are in the range
 * of letters between A to Z or one of the Turkish letters such as İ, Ü, Ğ, Ş, Ç, and Ö.
 *
 * @param surfaceForm String to check for proper noun.
 * @return false if surfaceForm is null or length of 0, return true if it is a letter.
 */
bool FsmMorphologicalAnalyzer::isProperNoun(const string& surfaceForm) const{
    if (surfaceForm.empty()) {
        return false;
    }
    return (Word::charAt(surfaceForm, 0) >= "A" && Word::charAt(surfaceForm, 0) <= "Z") || Word::charAt(surfaceForm, 0) == "Ç" || Word::charAt(surfaceForm, 0) == "Ö" || Word::charAt(surfaceForm, 0) == "Ğ" || Word::charAt(surfaceForm, 0) == "Ü" || Word::charAt(surfaceForm, 0) == "Ş" || Word::charAt(surfaceForm, 0) == "İ"; // İ, Ü, Ğ, Ş, Ç, Ö
}

/**
 * The isCode method takes surfaceForm String as input and checks if it consists of both letters and numbers
 *
 * @param surfaceForm String to check for code-like word.
 * @return True if it is a code-like word, return false otherwise.
 */
bool FsmMorphologicalAnalyzer::isCode(const string &surfaceForm) {
    if (surfaceForm.empty()) {
        return false;
    }
    return patternMatches(".*[0-9].*", surfaceForm) && patternMatches(".*[a-zA-ZçöğüşıÇÖĞÜŞİ].*", surfaceForm);
}


/**
 * Identifies a possible new root word for a given surface form. It also adds the new root form to the dictionary
 * for further usage. The method first searches the suffix trie for the reverse string of the surface form. This
 * way, it can identify if the word has a suffix that is in the most frequently used suffix list. Since a word can
 * have multiple possible suffixes, the method identifies the longest suffix and returns the substring of the
 * surface form tht does not contain the suffix. Let say the word is 'googlelaştırdık', it will identify 'tık' as
 * a suffix and will return 'googlelaştır' as a possible root form. Another example will be 'homelesslerimizle', it
 * will identify 'lerimizle' as suffix and will return 'homeless' as a possible root form. If the root word ends
 * with 'ğ', it is replacesd with 'k'. 'morfolojikliğini' will return 'morfolojikliğ' then which will be replaced
 * with 'morfolojiklik'.
 * @param surfaceForm Surface form for which we will identify a possible new root form.
 * @return Possible new root form.
 */
TxtWord *FsmMorphologicalAnalyzer::rootOfPossiblyNewWord(const string& surfaceForm) const{
    unordered_set<Word*> words = suffixTrie->getWordsWithPrefix(reverseString(surfaceForm));
    int maxLength = 0;
    string longestWord;
    for (Word* word : words){
        if (Word::size(word->getName()) > maxLength){
            longestWord = Word::substring(surfaceForm, 0, Word::size(surfaceForm) - Word::size(word->getName()));
            maxLength = Word::size(word->getName());
        }
    }
    if (maxLength != 0){
        TxtWord* newWord;
        if (Word::endsWith(longestWord, "ğ")){
            longestWord = Word::substring(longestWord, 0, Word::size(longestWord) - 1) + "k";
            newWord = new TxtWord(longestWord, "CL_ISIM");
            newWord->addFlag("IS_SD");
        } else {
            newWord = new TxtWord(longestWord, "CL_ISIM");
            newWord->addFlag("CL_FIIL");
        }
        dictionaryTrie->addWord(longestWord, newWord);
        return newWord;
    }
    return nullptr;
}

/**
 * The robustMorphologicalAnalysis is used to analyse surfaceForm String. First it gets the currentParse of the surfaceForm
 * then, if the size of the currentParse is 0, and given surfaceForm is a proper noun, it adds the surfaceForm
 * whose state name is ProperRoot to an ArrayList, of it is not a proper noon, it adds the surfaceForm
 * whose state name is NominalRoot to the ArrayList.
 *
 * @param surfaceForm String to analyse.
 * @return FsmParseList type currentParse which holds morphological analysis of the surfaceForm.
 */
FsmParseList FsmMorphologicalAnalyzer::robustMorphologicalAnalysis(const string& surfaceForm) {
    vector<FsmParse> fsmParse;
    FsmParseList currentParse;
    if (surfaceForm.empty()) {
        return FsmParseList();
    }
    currentParse = morphologicalAnalysis(surfaceForm);
    if (currentParse.size() == 0) {
        if (isProperNoun(surfaceForm)) {
            fsmParse.emplace_back(FsmParse(surfaceForm, finiteStateMachine.getState("ProperRoot")));
        } else {
            if (isCode(surfaceForm)){
                fsmParse.emplace_back(FsmParse(surfaceForm, finiteStateMachine.getState("CodeRoot")));
            } else {
                TxtWord* newRoot = rootOfPossiblyNewWord(surfaceForm);
                if (newRoot != nullptr){
                    fsmParse.emplace_back(FsmParse(newRoot, finiteStateMachine.getState("VerbalRoot")));
                    fsmParse.emplace_back(FsmParse(newRoot, finiteStateMachine.getState("NominalRoot")));
                } else {
                    fsmParse.emplace_back(FsmParse(surfaceForm, finiteStateMachine.getState("NominalRoot")));
                }
            }
        }
        return FsmParseList(parseWord(fsmParse, surfaceForm));
    } else {
        return currentParse;
    }
}

/**
 * The morphologicalAnalysis is used for debug purposes.
 *
 * @param sentence  to get word from.
 * @return FsmParseList type result.
 */
FsmParseList *FsmMorphologicalAnalyzer::morphologicalAnalysis(Sentence& sentence) {
    FsmParseList wordFsmParseList;
    auto* result = new FsmParseList[sentence.wordCount()];
    for (int i = 0; i < sentence.wordCount(); i++) {
        string originalForm = sentence.getWord(i)->getName();
        string spellCorrectedForm = dictionary->getCorrectForm(originalForm);
        if (spellCorrectedForm.empty()){
            spellCorrectedForm = originalForm;
        }
        wordFsmParseList = morphologicalAnalysis(spellCorrectedForm);
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
FsmParseList *FsmMorphologicalAnalyzer::robustMorphologicalAnalysis(Sentence& sentence) {
    FsmParseList fsmParseList;
    auto* result = new FsmParseList[sentence.wordCount()];
    for (int i = 0; i < sentence.wordCount(); i++) {
        string originalForm = sentence.getWord(i)->getName();
        string spellCorrectedForm = dictionary->getCorrectForm(originalForm);
        if (spellCorrectedForm.empty()){
            spellCorrectedForm = originalForm;
        }
        fsmParseList = robustMorphologicalAnalysis(spellCorrectedForm);
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
bool FsmMorphologicalAnalyzer::isInteger(const string& surfaceForm){
    if (!patternMatches("[-+]?\\d+", surfaceForm)){
        return false;
    }
    int len = Word::size(surfaceForm);
    if (len < 10) {
        return true;
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
bool FsmMorphologicalAnalyzer::isDouble(const string& surfaceForm) {
    return patternMatches(R"((\+|-)?(\d+)?\.\d*)", surfaceForm);
}

/**
 * The isNumber method compares input surfaceForm with the array of written numbers and returns the result.
 *
 * @param surfaceForm String to check.
 * @return true if surfaceForm matches with the regex.
 */
bool FsmMorphologicalAnalyzer::isNumber(const string& surfaceForm) const{
    bool found;
    int count = 0;
    string numbers[] = {"bir", "iki", "üç", "dört", "beş", "altı", "yedi", "sekiz", "dokuz",
                        "on", "yirmi", "otuz", "kırk", "elli", "altmış", "yetmiş", "seksen", "doksan",
                        "yüz", "bin", "milyon", "milyar", "trilyon", "katrilyon"};
    string word = surfaceForm;
    while (!word.empty()) {
        found = false;
        for (const string &number : numbers) {
            if (Word::startsWith(word, number)) {
                found = true;
                count++;
                word = Word::substring(word, Word::size(number));
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
 * Checks if a given surface form matches to a percent value. It should be something like %4, %45, %4.3 or %56.786
 * @param surfaceForm Surface form to be checked.
 * @return True if the surface form is in percent form
 */
bool FsmMorphologicalAnalyzer::isPercent(const string& surfaceForm){
    return patternMatches(R"(%(\d\d|\d))", surfaceForm) || patternMatches(R"(%(\d\d|\d)\.\d+)", surfaceForm);
}

/**
 * Checks if a given surface form matches to a time form. It should be something like 3:34, 12:56 etc.
 * @param surfaceForm Surface form to be checked.
 * @return True if the surface form is in time form
 */
bool FsmMorphologicalAnalyzer::isTime(const string& surfaceForm) {
    return patternMatches(R"((\d\d|\d):(\d\d|\d):(\d\d|\d))", surfaceForm) || patternMatches(R"((\d\d|\d):(\d\d|\d))", surfaceForm);
}

/**
 * Checks if a given surface form matches to a range form. It should be something like 123-1400 or 12:34-15:78 or
 * 3.45-4.67.
 * @param surfaceForm Surface form to be checked.
 * @return True if the surface form is in range form
 */
bool FsmMorphologicalAnalyzer::isRange(const string& surfaceForm) {
    return patternMatches("\\d+-\\d+", surfaceForm) || patternMatches(R"((\d\d|\d):(\d\d|\d)-(\d\d|\d):(\d\d|\d))", surfaceForm) || patternMatches(R"((\d\d|\d)\.(\d\d|\d)-(\d\d|\d)\.(\d\d|\d))", surfaceForm);
}

/**
 * Checks if a given surface form matches to a date form. It should be something like 3/10/2023 or 2.3.2012
 * @param surfaceForm Surface form to be checked.
 * @return True if the surface form is in date form
 */
bool FsmMorphologicalAnalyzer::isDate(const string& surfaceForm) {
    return patternMatches(R"((\d\d|\d)/(\d\d|\d)/\d+)", surfaceForm) || patternMatches(R"((\d\d|\d)\.(\d\d|\d)\.\d+)", surfaceForm);
}

/**
 * The morphologicalAnalysisExists method calls analysisExists to check the existence of the analysis with given
 * root and surfaceForm.
 *
 * @param surfaceForm String to check.
 * @param rootWord    TxtWord input root.
 * @return true an analysis exists, otherwise return false.
 */
bool FsmMorphologicalAnalyzer::morphologicalAnalysisExists(TxtWord *rootWord, const string& surfaceForm) {
    return analysisExists(rootWord, Word::toLowerCase(surfaceForm), true);
}

/**
 * The morphologicalAnalysis method is used to analyse a FsmParseList by comparing with the regex.
 * It creates an ArrayList fsmParse to hold the result of the analysis method. For each surfaceForm input,
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
FsmParseList FsmMorphologicalAnalyzer::morphologicalAnalysis(const string& surfaceForm) {
    FsmParseList fsmParseList;
    vector<FsmParse> parses;
    if (!parsedSurfaceForms.empty() && parsedSurfaceForms.find(Word::toLowerCase(surfaceForm)) != parsedSurfaceForms.end() && !isInteger(surfaceForm) && !isDouble(surfaceForm) && !isPercent(surfaceForm) && !isTime(surfaceForm) && !isRange(surfaceForm) && !isDate(surfaceForm)){
        parses.emplace_back(FsmParse(new Word(parsedSurfaceForms.find(Word::toLowerCase(surfaceForm))->second)));
        return FsmParseList(parses);
    }
    if (cache.getCacheSize() > 0 && cache.contains(surfaceForm)) {
        return cache.get(surfaceForm);
    }
    if (patternMatches("(\\w|Ç|Ş|İ|Ü|Ö)\\.", surfaceForm)) {
        dictionaryTrie->addWord(Word::toLowerCase(surfaceForm), new TxtWord(Word::toLowerCase(surfaceForm), "IS_OA"));
    }
    vector<FsmParse> defaultFsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
    if (!defaultFsmParse.empty()) {
        fsmParseList = FsmParseList(defaultFsmParse);
        if (cache.getCacheSize() > 0){
            cache.add(surfaceForm, fsmParseList);
        }
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
                if (isDate(possibleRoot)) {
                    dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_DATE"));
                    fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                } else {
                    if (patternMatches("\\d+/\\d+", possibleRoot)) {
                        dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_KESIR"));
                        fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                    } else {
                        if (isPercent(possibleRoot)) {
                            dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_PERCENT"));
                            fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                        } else {
                            if (isTime(possibleRoot)) {
                                dictionaryTrie->addWord(possibleRoot, new TxtWord(possibleRoot, "IS_ZAMAN"));
                                fsmParse = analysis(Word::toLowerCase(surfaceForm), isProperNoun(surfaceForm));
                            } else {
                                if (isRange(possibleRoot)) {
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
                                                string lowerCase = Word::toLowerCase(possibleRoot);
                                                if (dictionary->getWord(lowerCase) != nullptr) {
                                                    ((TxtWord*) dictionary->getWord(lowerCase))->addFlag("IS_OA");
                                                } else {
                                                    newWord = new TxtWord(lowerCase, "IS_OA");
                                                    dictionaryTrie->addWord(lowerCase, newWord);
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
    if (cache.getCacheSize() > 0 && fsmParseList.size() > 0){
        cache.add(surfaceForm, fsmParseList);
    }
    return fsmParseList;
}
