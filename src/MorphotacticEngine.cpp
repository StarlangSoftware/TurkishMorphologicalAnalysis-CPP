//
// Created by Olcay Taner YILDIZ on 20.04.2022.
//

#include "MorphotacticEngine.h"
#include "Language/TurkishLanguage.h"

string MorphotacticEngine::resolveD(TxtWord* root, string formation, string formationToCheck) {
    if (root->isAbbreviation()) {
        return formation + 'd';
    }
    if (Word::lastPhoneme(formationToCheck) >= "0" && Word::lastPhoneme(formationToCheck) <= "9") {
        if (Word::lastPhoneme(formationToCheck) == "3" ||
            Word::lastPhoneme(formationToCheck) == "4" ||
            Word::lastPhoneme(formationToCheck) == "5"){
            //3->3'tü, 5->5'ti, 4->4'tü
            return formation + 't';
        } else {
            if (Word::lastPhoneme(formationToCheck) == "0"){
                if (Word::endsWith(root->getName(), "40") ||
                    Word::endsWith(root->getName(), "60") ||
                    Word::endsWith(root->getName(), "70"))
                    //40->40'tı, 60->60'tı, 70->70'ti
                    return formation + 't';
                else
                    //30->30'du, 50->50'ydi, 80->80'di
                    return formation + 'd';
            } else {
                return formation + 'd';
            }
        }
    } else {
        if (TurkishLanguage::isSertSessiz(Word::lastPhoneme(formationToCheck))) {
            //yap+DH->yaptı
            return formation + 't';
        } else {
            //sar+DH->sardı
            return formation + 'd';
        }
    }
}

string MorphotacticEngine::resolveA(TxtWord *root, string formation, bool rootWord, string formationToCheck) {
    if (root->isAbbreviation()) {
        return formation + 'e';
    }
    if (Word::lastVowel(formationToCheck) >= "0" && Word::lastVowel(formationToCheck) <= "9") {
        if (Word::lastVowel(formationToCheck) == "6" || Word::lastVowel(formationToCheck) == "9"){
            //6'ya, 9'a
            return formation + 'a';
        } else {
            if (Word::lastVowel(formationToCheck) == "0"){
                if (Word::endsWith(root->getName(), "10") ||
                    Word::endsWith(root->getName(), "30") ||
                    Word::endsWith(root->getName(), "40") ||
                    Word::endsWith(root->getName(), "60") ||
                    Word::endsWith(root->getName(), "90"))
                    //10'a, 30'a, 40'a, 60'a, 90'a
                    return formation + 'a';
                else
                    //20'ye, 50'ye, 80'e, 70'e
                    return formation + 'e';
            } else {
                //3'e, 8'e, 4'e, 2'ye
                return formation + 'e';
            }
        }
    }
    if (TurkishLanguage::isBackVowel(Word::lastVowel(formationToCheck))) {
        if (root->notObeysVowelHarmonyDuringAgglutination() && rootWord) {
            //alkole, anormale, ampule, tümamirali, spirali, sosyali
            return formation + 'e';
        } else {
            //sakala, kabala, eve, kediye
            return formation + 'a';
        }
    }
    if (TurkishLanguage::isFrontVowel(Word::lastVowel(formationToCheck))) {
        if (root->notObeysVowelHarmonyDuringAgglutination() && rootWord) {
            //sakala, kabala, eve, kediye
            return formation + 'a';
        } else {
            //alkole, anormale, ampule, tümamirali, spirali, sosyali
            return formation + 'e';
        }
    }
    if (root->isNumeral() || root->isFraction() || root->isReal()) {
        if (Word::endsWith(root->getName(), "6") ||
            Word::endsWith(root->getName(), "9") ||
            Word::endsWith(root->getName(), "10") ||
            Word::endsWith(root->getName(), "30") ||
            Word::endsWith(root->getName(), "40") ||
            Word::endsWith(root->getName(), "60") ||
            Word::endsWith(root->getName(), "90")) {
            return formation + 'a';
        } else {
            return formation + 'e';
        }
    }
    return formation;
}

string MorphotacticEngine::resolveH(TxtWord *root, string formation, bool beginningOfSuffix, bool specialCaseTenseSuffix,
                            bool rootWord, string formationToCheck) {
    if (root->isAbbreviation())
        return formation + 'i';
    if (beginningOfSuffix && TurkishLanguage::isVowel(Word::lastPhoneme(formationToCheck)) && !specialCaseTenseSuffix) {
        return formation;
    }
    if (specialCaseTenseSuffix) {
        //eğer ek Hyor eki ise,
        if (rootWord) {
            if (root->vowelAChangesToIDuringYSuffixation()) {
                if (TurkishLanguage::isFrontRoundedVowel(Word::beforeLastVowel(formationToCheck))) {
                    //büyülüyor, bölümlüyor, çözümlüyor, döşüyor
                    return Word::substringExceptLastChar(formation) + "ü";
                }
                if (TurkishLanguage::isFrontUnroundedVowel(Word::beforeLastVowel(formationToCheck))) {
                    //adresliyor, alevliyor, ateşliyor, bekliyor
                    return Word::substringExceptLastChar(formation) + 'i';
                }
                if (TurkishLanguage::isBackRoundedVowel(Word::beforeLastVowel(formationToCheck))) {
                    //buğuluyor, bulguluyor, çamurluyor, aforozluyor
                    return Word::substringExceptLastChar(formation) + 'u';
                }
                if (TurkishLanguage::isBackUnroundedVowel(Word::beforeLastVowel(formationToCheck))) {
                    //açıklıyor, çalkalıyor, gazlıyor, gıcırdıyor
                    return Word::substringExceptLastChar(formation) + "ı";
                }
            }
        }
        if (TurkishLanguage::isVowel(Word::lastPhoneme(formationToCheck))) {
            if (TurkishLanguage::isFrontRoundedVowel(Word::beforeLastVowel(formationToCheck))) {
                return Word::substringExceptLastChar(formation) + "ü";
            }
            if (TurkishLanguage::isFrontUnroundedVowel(Word::beforeLastVowel(formationToCheck))) {
                return Word::substringExceptLastChar(formation) + 'i';
            }
            if (TurkishLanguage::isBackRoundedVowel(Word::beforeLastVowel(formationToCheck))) {
                return Word::substringExceptLastChar(formation) + 'u';
            }
            if (TurkishLanguage::isBackUnroundedVowel(Word::beforeLastVowel(formationToCheck))) {
                return Word::substringExceptLastChar(formation) + "ı";
            }
        }
    }
    if (TurkishLanguage::isFrontRoundedVowel(Word::lastVowel(formationToCheck)) || (TurkishLanguage::isBackRoundedVowel(Word::lastVowel(formationToCheck)) && root->notObeysVowelHarmonyDuringAgglutination())) {
        return formation + "ü";
    }
    if (TurkishLanguage::isFrontUnroundedVowel(Word::lastVowel(formationToCheck)) || (Word::lastVowel(formationToCheck) == "a" && root->notObeysVowelHarmonyDuringAgglutination())) {
        return formation + 'i';
    }
    if (TurkishLanguage::isBackRoundedVowel(Word::lastVowel(formationToCheck))) {
        return formation + 'u';
    }
    if (TurkishLanguage::isBackUnroundedVowel(Word::lastVowel(formationToCheck))) {
        return formation + "ı";
    }
    if (root->isNumeral() || root->isFraction() || root->isReal()) {
        if (Word::endsWith(root->getName(), "6") ||
            Word::endsWith(root->getName(), "40") ||
            Word::endsWith(root->getName(), "60") ||
            Word::endsWith(root->getName(), "90")) {
            //6'yı, 40'ı, 60'ı
            return formation + "ı";
        } else {
            if (Word::endsWith(root->getName(), "3") ||
                Word::endsWith(root->getName(), "4") ||
                Word::endsWith(root->getName(), "00")) {
                //3'ü, 4'ü, 100'ü
                return formation + "ü";
            } else {
                if (Word::endsWith(root->getName(), "9") ||
                    Word::endsWith(root->getName(), "10") ||
                    Word::endsWith(root->getName(), "30")) {
                    //9'u, 10'u, 30'u
                    return formation + 'u';
                } else {
                    //2'yi, 5'i, 8'i
                    return formation + 'i';
                }
            }
        }
    }
    return formation;
}

/**
 * The resolveC method takes a {@link String} formation as an input. If the last phoneme is on of the "çfhkpsşt", it
 * concatenates given formation with 'ç', if not it concatenates given formation with 'c'.
 *
 * @param formation {@link String} input.
 * @return resolved String.
 */
string MorphotacticEngine::resolveC(string formation, string formationToCheck) {
    if (TurkishLanguage::isSertSessiz(Word::lastPhoneme(formationToCheck))) {
        return formation + "ç";
    } else {
        return formation + 'c';
    }
}

/**
 * The resolveS method takes a {@link String} formation as an input. It then concatenates given formation with 's'.
 *
 * @param formation {@link String} input.
 * @return resolved String.
 */
string MorphotacticEngine::resolveS(string formation) {
    return formation + 's';
}

/**
 * The resolveSh method takes a {@link String} formation as an input. If the last character is a vowel, it concatenates
 * given formation with ş, if the last character is not a vowel, and not 't' it directly returns given formation, but if it
 * is equal to 't', it transforms it to 'd'.
 *
 * @param formation {@link String} input.
 * @return resolved String.
 */
string MorphotacticEngine::resolveSh(string formation) {
    if (TurkishLanguage::isVowel(Word::lastChar(formation))) {
        return formation + "ş";
    } else {
        if (Word::lastChar(formation) != "t")
            return formation;
        else
            return Word::substringExceptLastChar(formation) + 'd';
    }
}