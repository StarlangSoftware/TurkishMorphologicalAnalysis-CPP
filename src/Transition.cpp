//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "Transition.h"

#include <StringUtils.h>

#include "Language/TurkishLanguage.h"
#include "MorphotacticEngine.h"

/**
 * A constructor of Transition class which takes  a State, and two Strings as input. Then it
 * initializes toState, with and withName variables with given inputs.
 *
 * @param toState  State input.
 * @param with     String input.
 * @param withName String input.
 */
Transition::Transition(const State& toState, const string& with, const string& withName) {
    this->toState = toState;
    this->with = with;
    this->withName = withName;
    toPos = "";
}

/**
 * Another constructor of Transition class which takes  a State, and three Strings as input. Then it
 * initializes toState, with, withName and toPos variables with given inputs.
 *
 * @param toState  State input.
 * @param with     String input.
 * @param withName String input.
 * @param toPos    String input.
 */
Transition::Transition(const State& toState, const string& with, const string& withName, const string& toPos) {
    this->toState = toState;
    this->with = with;
    this->withName = withName;
    this->toPos = toPos;
}

/**
 * Another constructor of Transition class which only takes a Strings as an input. Then it
 * initializes toState, withName and toPos variables as null and with variable with the given input.
 *
 * @param with String input.
 */
Transition::Transition(const string& with) {
    withName = "";
    toPos = "";
    this->with = with;
}

/**
 * Getter for the toState variable.
 *
 * @return toState variable.
 */
State Transition::getToState() const{
    return toState;
}

/**
 * Getter for the toPos variable.
 *
 * @return toPos variable.
 */
string Transition::getToPos() const{
    return toPos;
}

/**
 * The transitionPossible method takes two String as inputs; currentSurfaceForm and realSurfaceForm. If the
 * length of the given currentSurfaceForm is greater than the given realSurfaceForm, it directly returns true. If not,
 * it takes a substring from given realSurfaceForm with the size of currentSurfaceForm. Then checks for the characters of
 * with variable.
 * <p>
 * If the character of with that makes transition is C, it returns true if the substring contains c or ç.
 * If the character of with that makes transition is D, it returns true if the substring contains d or t.
 * If the character of with that makes transition is A, it returns true if the substring contains a or e.
 * If the character of with that makes transition is K, it returns true if the substring contains k, g or ğ.
 * If the character of with that makes transition is other than the ones above, it returns true if the substring
 * contains the same character as with.
 *
 * @param currentSurfaceForm String input.
 * @param realSurfaceForm    String input.
 * @return true when the transition is possible according to Turkish grammar, false otherwise.
 */
bool Transition::transitionPossible(const string& currentSurfaceForm, const string& realSurfaceForm) const{
    if (Word::size(currentSurfaceForm) == 0 || Word::size(currentSurfaceForm) >= Word::size(realSurfaceForm)) {
        return true;
    }
    string searchString = realSurfaceForm.substr(Word::size(currentSurfaceForm), Word::size(realSurfaceForm));
    string* withChars = Word::allCharacters(with);
    for (int i = 0; i < Word::size(with); i++) {
        string ch = withChars[i];
        if (ch == "C"){
            return searchString.find('c') != string::npos || searchString.find("ç") != string::npos;
        } else {
            if (ch == "D"){
                return searchString.find('d') != string::npos || searchString.find('t') != string::npos;
            } else {
                if (ch == "c" || ch == "e" || ch == "r" || ch == "p" || ch == "l" || ch == "b" || ch == "g" || ch == "o" ||
                    ch == "m" || ch == "v" || ch == "i" || ch == "ü" || ch == "z"){
                    return searchString.find(ch) != string::npos;
                } else {
                    if (ch == "A"){
                        return searchString.find('a') != string::npos || searchString.find('e') != string::npos;
                    } else {
                        if (ch == "k"){
                            return searchString.find('k') != string::npos || searchString.find('g') != string::npos || searchString.find("ğ") != string::npos;
                        }
                    }
                }
            }
        }
    }
    delete[] withChars;
    return true;
}

/**
 * The transitionPossible method takes a current parse as an input. It then checks some special  cases.
 *
 * @param currentFsmParse Parse to be checked
 * @return true if transition is possible false otherwise
 */
bool Transition::transitionPossible(const FsmParse& currentFsmParse) const{
    if (with == "Ar" && StringUtils::endsWith(currentFsmParse.getSurfaceForm(), "l") && currentFsmParse.getWord()->getName() != currentFsmParse.getSurfaceForm()) {
        return false;
    }
    if (!currentFsmParse.getVerbAgreement().empty() && !currentFsmParse.getPossesiveAgreement().empty() && !withName.empty()) {
        if (currentFsmParse.getVerbAgreement() == "A3PL" && withName == "^DB+VERB+ZERO+PRES+A1SG") {
            return false;
        }
        if (currentFsmParse.getVerbAgreement() == "A3SG" && (currentFsmParse.getPossesiveAgreement() == "P1SG" || currentFsmParse.getPossesiveAgreement() == "P2SG") && withName == "^DB+VERB+ZERO+PRES+A1PL") {
            return false;
        }
    }
    return true;
}

/**
 * The transitionPossible method takes root and current parse as inputs. It then checks some special cases.
 *
 * @param root Current root word
 * @param fromState From which state we arrived to this state.
 * @return true if transition is possible false otherwise
 */
bool Transition::transitionPossible(TxtWord* root, const State& fromState) const{
    if (root->isAdjective() && ((root->isNominal() && !root->isExceptional()) || root->isPronoun()) && toState.getName() == "NominalRoot(ADJ)" && with == "0") {
        return false;
    }
    if (root->isAdjective() && root->isNominal() && with == "^DB+VERB+ZERO+PRES+A3PL" && fromState.getName() == "AdjectiveRoot") {
        return false;
    }
    if (root->isAdjective() && root->isNominal() && with == "SH" && fromState.getName() == "AdjectiveRoot") {
        return false;
    }
    if (with == "ki") {
        return root->takesRelativeSuffixKi();
    }
    if (with == "kü") {
        return root->takesRelativeSuffixKu();
    }
    if (with == "DHr") {
        if (toState.getName() == "Adverb") {
            return true;
        } else {
            return root->takesSuffixDIRAsFactitive();
        }
    }
    if (with == "Hr" && (toState.getName() == "AdjectiveRoot(VERB)" || toState.getName() == "OtherTense" || toState.getName() == "OtherTense2")) {
        return root->takesSuffixIRAsAorist();
    }
    return true;
}

/**
 * The withFirstChar method returns the first character of the with variable.
 *
 * @return the first character of the with variable.
 */
string Transition::withFirstChar() const{
    if (with.empty()) {
        return "$";
    }
    if (Word::charAt(with, 0) != "'") {
        return Word::charAt(with, 0);
    } else {
        if (Word::size(with) == 1) {
            return Word::charAt(with, 0);
        } else {
            return Word::charAt(with, 1);
        }
    }
}

/**
 * The startWithVowelorConsonantDrops method checks for some cases. If the first character of with variable is "nsy",
 * and with variable does not equal to one of the Strings; "ylA, ysA, ymHs, yDH, yken", it returns true. If
 * <p>
 * Or, if the first character of with variable is 'A, H: or any other vowels, it returns true.
 *
 * @return true if it starts with vowel or consonant drops, false otherwise.
 */
bool Transition::startWithVowelorConsonantDrops() const{
    if (TurkishLanguage::isConsonantDrop(withFirstChar()) && with != "ylA" && with != "ysA" && with != "ymHs" && with != "yDH" && with != "yken") {
        return true;
    }
    if (withFirstChar() == "A" || withFirstChar() == "H" || TurkishLanguage::isVowel(withFirstChar())) {
        return true;
    }
    return false;
}

/**
 * The softenDuringSuffixation method takes a TxtWord root as an input. It checks two cases; first case returns
 * true if the given root is nominal or adjective and has one of the flags "IS_SD, IS_B_SD, IS_SDD" and with variable
 * equals o one of the Strings "Hm, nDAn, ncA, nDA, yA, yHm, yHz, yH, nH, nA, nHn, H, sH, Hn, HnHz, HmHz".
 * <p>
 * And the second case returns true if the given root is verb and has the "F_SD" flag, also with variable starts with
 * "Hyor" or equals one of the Strings "yHs, yAn, yA, yAcAk, yAsH, yHncA, yHp, yAlH, yArAk, yAdur, yHver, yAgel, yAgor,
 * yAbil, yAyaz, yAkal, yAkoy, yAmA, yHcH, HCH, Hr, Hs, Hn, yHn", yHnHz, Ar, Hl").
 *
 * @param root TxtWord input.
 * @return true if there is softening during suffixation of the given root, false otherwise.
 */
bool Transition::softenDuringSuffixation(TxtWord* root) const{
    if ((root->isNominal() || root->isAdjective()) && root->nounSoftenDuringSuffixation() && (with == "Hm" || with == "nDAn" || with == "ncA" || with == "nDA" || with == "yA" || with == "yHm" || with == "yHz" || with == "yH" || with == "nH" || with == "nA" || with == "nHn" || with == "H" || with == "sH" || with == "Hn" || with == "HnHz" || with == "HmHz")) {
        return true;
    }
    if (root->isVerb() && root->verbSoftenDuringSuffixation() && (StringUtils::startsWith(with, "Hyor") || with == "yHs" || with == "yAn" || with == "yA" || StringUtils::startsWith(with, "yAcAk") || with == "yAsH" || with == "yHncA" || with == "yHp" || with == "yAlH" || with == "yArAk" || with == "yAdur" || with == "yHver" || with == "yAgel" || with == "yAgor" || with == "yAbil" || with == "yAyaz" || with == "yAkal" || with == "yAkoy" || with == "yAmA" || with == "yHcH" || with == "HCH" || StringUtils::startsWith(with, "Hr") || with == "Hs" || with == "Hn" || with == "yHn" || with == "yHnHz" || StringUtils::startsWith(with, "Ar") || with == "Hl")) {
        return true;
    }
    return false;
}

/**
 * The makeTransition method takes a TxtWord root and s String stem as inputs. If given root is a verb,
 * it makes transition with given root and stem with the verbal root state. If given root is not verb, it makes transition
 * with given root and stem and the nominal root state.
 *
 * @param root TxtWord input.
 * @param stem String input.
 * @return String type output that has the transition.
 */
string Transition::makeTransition(TxtWord *root, const string& stem) const{
    if (root->isVerb()) {
        return makeTransition(root, stem, State("VerbalRoot", true, false));
    } else {
        return makeTransition(root, stem, State("NominalRoot", true, false));
    }
}

/**
 * The method is main driving method to accomplish the current transition from one state to another depending on
 * the root form of the word, current value of the word form, and the type of the start state. The method
 * (a) returns the original word form if the transition is an epsilon transition, (b) adds 'nunla' if the current
 * stem is 'bu', 'şu' or 'o', (c) returns 'bana' or 'sana' if the current stem is 'ben' or 'sen' respectively.
 * For other cases, the method first modifies current stem and then adds the transition using special metamorpheme
 * resolving methods. These cases are: (d) Converts 'y' of the first character of the transition to 'i' if the
 * current stem is 'ye' or 'de'. (e) Drops the last two characters and adds last character when the transition is
 * ('Hl' or 'Hn') and last 'I' drops during passive suffixation. (f) Adds 'y' character when the word ends with 'su'
 * and the transition does not start with 'y'. (g) Adds the last character again when the root duplicates during
 * suffixation. (h) Drops the last two characters and adds the last character when last 'i' drops during
 * suffixation. (i) Replaces the last character with a soft one when the root soften during suffixation.
 * @param root Root of the current word form
 * @param stem Current word form
 * @param startState The state from which this Fsm morphological analysis search has started.
 * @return The current value of the word form after this transition is completed in the finite state machine.
 */
string Transition::makeTransition(TxtWord *root, const string& stem, const State& startState) const{
    bool rootWord = root->getName() == stem || (root->getName() + "'") == stem;
    string formation = stem;
    string formationToCheck;
    int i = 0;
    if (with == "0") {
        return stem;
    }
    if ((stem == "bu" || stem == "şu" || stem == "o") && rootWord && with == "ylA") {
        return stem + "nunla";
    }
    if (with == "yA") {
        if (stem == "ben") {
            return "bana";
        }
        if (stem == "sen") {
            return "sana";
        }
    }
    //---vowelEChangesToIDuringYSuffixation---
    //de->d(i)yor, ye->y(i)yor
    if (rootWord && withFirstChar() == "y" && root->vowelEChangesToIDuringYSuffixation() && (Word::charAt(with, 1) != "H" || root->getName() == "ye")) {
        formation = Word::substringExceptLastChar(stem) + 'i';
        formationToCheck = formation;
    } else {
        //---lastIdropsDuringPassiveSuffixation---
        // yoğur->yoğrul, ayır->ayrıl, buyur->buyrul, çağır->çağrıl, çevir->çevril, devir->devril,
        // kavur->kavrul, kayır->kayrıl, kıvır->kıvrıl, savur->savrul, sıyır->sıyrıl, yoğur->yoğrul
        if (rootWord && (with == "Hl" || with == "Hn") && root->lastIdropsDuringPassiveSuffixation()) {
            formation = Word::substringExceptLastTwoChars(stem) + Word::lastChar(stem);
            formationToCheck = stem;
        } else {
            //---showsSuRegularities---
            //karasu->karasuyu, özsu->özsuyu, ağırsu->ağırsuyu, akarsu->akarsuyu, bengisu->bengisuyu
            if (rootWord && root->showsSuRegularities() && startWithVowelorConsonantDrops() && !StringUtils::startsWith(with, "y")) {
                formation = stem + 'y';
                i = 1;
                formationToCheck = formation;
            } else {
                if (rootWord && root->duplicatesDuringSuffixation() && !StringUtils::startsWith(startState.getName(), "VerbalRoot") && TurkishLanguage::isConsonantDrop(Word::charAt(with, 0))) {
                    //---duplicatesDuringSuffixation---
                    if (softenDuringSuffixation(root)) {
                        //--extra softenDuringSuffixation
                        if (Word::lastPhoneme(stem) == "p"){
                            //tıp->tıbbı
                            formation = Word::substringExceptLastChar(stem) + "bb";
                        } else {
                            if (Word::lastPhoneme(stem) == "t"){
                                //cet->ceddi, met->meddi, ret->reddi, serhat->serhaddi, zıt->zıddı, şet->şeddi
                                formation = Word::substringExceptLastChar(stem) + "dd";
                            }
                        }
                    } else {
                        //cer->cerri, emrihak->emrihakkı, fek->fekki, fen->fenni, had->haddi, hat->hattı,
                        // haz->hazzı, his->hissi
                        formation = stem + Word::lastChar(stem);
                    }
                    formationToCheck = formation;
                } else {
                    if (rootWord && root->lastIdropsDuringSuffixation() && !StringUtils::startsWith(startState.getName(), "VerbalRoot") && !StringUtils::startsWith(startState.getName(), "ProperRoot") && startWithVowelorConsonantDrops()) {
                        //---lastIdropsDuringSuffixation---
                        if (softenDuringSuffixation(root)) {
                            //---softenDuringSuffixation---
                            if (Word::lastPhoneme(stem) == "p"){
                                //hizip->hizbi, kayıp->kaybı, kayıt->kaydı, kutup->kutbu
                                formation = Word::substringExceptLastTwoChars(stem) + 'b';
                            } else {
                                if (Word::lastPhoneme(stem) == "t"){
                                    //akit->akdi, ahit->ahdi, lahit->lahdi, nakit->nakdi, vecit->vecdi
                                    formation = Word::substringExceptLastTwoChars(stem) + 'd';
                                } else {
                                    if (Word::lastPhoneme(stem) == "ç"){
                                        //eviç->evci, nesiç->nesci
                                        formation = Word::substringExceptLastTwoChars(stem) + 'c';
                                    }
                                }
                            }
                        } else {
                            //sarıağız->sarıağzı, zehir->zehri, zikir->zikri, nutuk->nutku, omuz->omzu, ömür->ömrü
                            //lütuf->lütfu, metin->metni, kavim->kavmi, kasıt->kastı
                            formation = Word::substringExceptLastTwoChars(stem) + Word::lastChar(stem);
                        }
                        formationToCheck = stem;
                    } else {
                        //---nounSoftenDuringSuffixation or verbSoftenDuringSuffixation
                        if (Word::lastPhoneme(stem) == "p"){
                            //adap->adabı, amip->amibi, azap->azabı, gazap->gazabı
                            if (startWithVowelorConsonantDrops() && rootWord && softenDuringSuffixation(root)) {
                                formation = Word::substringExceptLastChar(stem) + 'b';
                            }
                        } else {
                            if (Word::lastPhoneme(stem) == "t"){
                                //abat->abadı, adet->adedi, akort->akordu, armut->armudu
                                //affet->affedi, yoket->yokedi, sabret->sabredi, rakset->raksedi
                                if (startWithVowelorConsonantDrops() && rootWord && softenDuringSuffixation(root)) {
                                    formation = Word::substringExceptLastChar(stem) + 'd';
                                }
                            } else {
                                if (Word::lastPhoneme(stem) == "ç"){
                                    //ağaç->ağacı, almaç->almacı, akaç->akacı, avuç->avucu
                                    if (startWithVowelorConsonantDrops() && rootWord && softenDuringSuffixation(root)) {
                                        formation = Word::substringExceptLastChar(stem) + 'c';
                                    }
                                } else {
                                    if (Word::lastPhoneme(stem) == "g"){
                                        //arkeolog->arkeoloğu, filolog->filoloğu, minerolog->mineroloğu
                                        if (startWithVowelorConsonantDrops() && rootWord && softenDuringSuffixation(root)) {
                                            formation = Word::substringExceptLastChar(stem) + "ğ";
                                        }
                                    } else {
                                        if (Word::lastPhoneme(stem) == "k"){
                                            //ahenk->ahengi, künk->küngü, renk->rengi, pelesenk->pelesengi
                                            if (startWithVowelorConsonantDrops() && rootWord && root->endingKChangesIntoG() && (!root->isProperNoun() || startState.to_String() != "ProperRoot")) {
                                                formation = Word::substringExceptLastChar(stem) + 'g';
                                            } else {
                                                //ablak->ablağı, küllük->küllüğü, kitaplık->kitaplığı, evcilik->evciliği
                                                if (startWithVowelorConsonantDrops() && (!rootWord || (softenDuringSuffixation(root) && (!root->isProperNoun() || startState.to_String() != "ProperRoot")))) {
                                                    formation = Word::substringExceptLastChar(stem) + "ğ";
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        formationToCheck = formation;
                    }
                }
            }
        }
    }
    string* withChars = Word::allCharacters(with);
    if (TurkishLanguage::isConsonantDrop(withFirstChar()) && !TurkishLanguage::isVowel(Word::lastChar(stem)) && (root->isNumeral() || root->isReal() || root->isFraction() || root->isTime() || root->isDate() || root->isPercent() || root->isRange()) && (StringUtils::endsWith(root->getName(), "1") || StringUtils::endsWith(root->getName(), "3") || StringUtils::endsWith(root->getName(), "4") || StringUtils::endsWith(root->getName(), "5") || StringUtils::endsWith(root->getName(), "8") || StringUtils::endsWith(root->getName(), "9") || StringUtils::endsWith(root->getName(), "10") || StringUtils::endsWith(root->getName(), "30") || StringUtils::endsWith(root->getName(), "40") || StringUtils::endsWith(root->getName(), "60") || StringUtils::endsWith(root->getName(), "70") || StringUtils::endsWith(root->getName(), "80") || StringUtils::endsWith(root->getName(), "90") || StringUtils::endsWith(root->getName(), "00"))) {
        if (withChars[0] == "'") {
            formation = formation + '\'';
            i = 2;
        } else {
            i = 1;
        }
    } else {
        if ((TurkishLanguage::isConsonantDrop(withFirstChar()) && TurkishLanguage::isConsonant(Word::lastPhoneme(stem))) || (rootWord && root->consonantSMayInsertedDuringPossesiveSuffixation())) {
            if (withChars[0] == "'") {
                formation = formation + '\'';
                if (root->isAbbreviation())
                    i = 1;
                else
                    i = 2;
            } else {
                i = 1;
            }
        }
    }
    for (; i < Word::size(with); i++) {
        if (withChars[i] == "D"){
            formation = MorphotacticEngine::resolveD(root, formation, formationToCheck);
        } else {
            if (withChars[i] == "A"){
                formation = MorphotacticEngine::resolveA(root, formation, rootWord, formationToCheck);
            } else {
                if (withChars[i] == "H"){
                    if (withChars[0] != "'") {
                        formation = MorphotacticEngine::resolveH(root, formation, i == 0, StringUtils::startsWith(with, "Hyor"), rootWord, formationToCheck);
                    } else {
                        formation = MorphotacticEngine::resolveH(root, formation, i == 1, false, rootWord, formationToCheck);
                    }
                    //Added for the second H in HnHz and HmHz.
                    rootWord = false;
                } else {
                    if (withChars[i] == "C"){
                        formation = MorphotacticEngine::resolveC(formation, formationToCheck);
                    } else {
                        if (withChars[i] == "S"){
                            formation = MorphotacticEngine::resolveS(formation);
                        } else {
                            if (withChars[i] == "Ş"){
                                formation = MorphotacticEngine::resolveSh(formation);
                            } else {
                                if (i == Word::size(with) - 1 && withChars[i] == "s") {
                                    formation += "ş";
                                } else {
                                    formation += withChars[i];
                                }
                            }
                        }
                    }
                }
            }
        }
        formationToCheck = formation;
    }
    delete[] withChars;
    return formation;
}

/**
 * An overridden toString method which returns the with variable.
 *
 * @return with variable.
 */
string Transition::to_String() const{
    return with;
}

/**
 * The with method returns the withName variable.
 *
 * @return the withName variable.
 */
string Transition::getWith() const{
    return withName;
}