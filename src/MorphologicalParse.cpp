//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "MorphologicalParse.h"
#include "Language/TurkishLanguage.h"

/**
 * An empty constructor of MorphologicalParse class.
 */
MorphologicalParse::MorphologicalParse() = default;

/**
 * The no-arg getWord method returns root Word.
 *
 * @return root Word.
 */
Word* MorphologicalParse::getWord() const{
    return root;
}

/**
 * Another constructor of MorphologicalParse class which takes a String parse as an input. First it creates
 * an ArrayList as iGs for inflectional groups, and while given String contains derivational boundary (^DB+), it
 * adds the substring to the iGs ArrayList and continue to use given String from 4th index. If it does not contain ^DB+,
 * it directly adds the given String to the iGs ArrayList. Then, it creates a new ArrayList as
 * inflectionalGroups and checks for some cases.
 * <p>
 * If the first item of iGs ArrayList is ++Punc, it creates a new root as +, and by calling
 * InflectionalGroup method with Punc it initializes the IG ArrayList by parsing given input
 * String IG by + and calling the getMorphologicalTag method with these substrings. If getMorphologicalTag method returns
 * a tag, it adds this tag to the IG ArrayList and also to the inflectionalGroups ArrayList.
 * <p>
 * If the first item of iGs ArrayList has +, it creates a new word of first item's substring from index 0 to +,
 * and assigns it to root. Then, by calling InflectionalGroup method with substring from index 0 to +,
 * it initializes the IG ArrayList by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG ArrayList
 * and also to the inflectionalGroups ArrayList.
 * <p>
 * If the first item of iGs ArrayList does not contain +, it creates a new word with first item and assigns it as root.
 * <p>
 * At the end, it loops through the items of iGs and by calling InflectionalGroup method with these items
 * it initializes the IG ArrayList by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG ArrayList
 * and also to the inflectionalGroups ArrayList.
 *
 * @param parse String input.
 */
MorphologicalParse::MorphologicalParse(const string& parse) {
    vector<string> iGs;
    string st = parse;
    while (st.find("^DB+") != string::npos) {
        iGs.emplace_back(st.substr(0, st.find("^DB+")));
        st = st.substr(st.find("^DB+") + 4, st.size());
    }
    iGs.emplace_back(st);
    if (iGs.at(0) == "++Punc") {
        root = new Word("+");
        inflectionalGroups.emplace_back("Punc");
    } else {
        updateRootAndInflectionalGroups(iGs);
    }
}

/**
 * Another constructor of MorphologicalParse class which takes an vector inflectionalGroups as an input.
 *
 * @param inflectionalGroups vector input.
 */
MorphologicalParse::MorphologicalParse(const vector<string>& inflectionalGroups) {
    updateRootAndInflectionalGroups(inflectionalGroups);
}

/**
 * It initializes _inflectionalGroups ArrayList and if the first item of the vector has +, it gets
 * the substring from index 0 to + and assigns it as root, and by calling InflectionalGroup method with substring from index 0 to +,
 * it initializes the IG vector by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG vector
 * and also to the _inflectionalGroups vector. However, if the first item does not contain +, it directly prints out
 * indicating that there is no root for that item of this Inflectional Group.
 * <p>
 * At the end, it loops through the items of _inflectionalGroups and by calling InflectionalGroup method with these items
 * it initializes the IG vector by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG vector
 * and also to the _inflectionalGroups vector.
 *
 * @param _inflectionalGroups vector input.
 */
void MorphologicalParse::updateRootAndInflectionalGroups(const vector<string>& _inflectionalGroups) {
    int i;
    if (_inflectionalGroups.at(0).find('+') != string::npos) {
        root = new Word(_inflectionalGroups.at(0).substr(0, _inflectionalGroups.at(0).find('+')));
        this->inflectionalGroups.emplace_back(_inflectionalGroups.at(0).substr(_inflectionalGroups.at(0).find('+') + 1, _inflectionalGroups.at(0).size()));
    }
    for (i = 1; i < _inflectionalGroups.size(); i++) {
        this->inflectionalGroups.emplace_back(_inflectionalGroups.at(i));
    }
}

/**
 * The getTransitionList method gets the first item of inflectionalGroups ArrayList as a String, then loops
 * through the items of inflectionalGroups and concatenates them by using +.
 *
 * @return String that contains transition list.
 */
string MorphologicalParse::getTransitionList() const{
    string result = inflectionalGroups.at(0).to_String();
    for (int i = 1; i < inflectionalGroups.size(); i++) {
        result.append("+");
        result.append(inflectionalGroups.at(i).to_String());
    }
    return result;
}

/**
 * The getInflectionalGroupString method takes an Integer index as an input and if index is 0, it directly returns the
 * root and the first item of inflectionalGroups vector. If the index is not 0, it then returns the corresponding
 * item of inflectionalGroups vector as a String.
 *
 * @param index Integer input.
 * @return corresponding item of inflectionalGroups at given index as a String.
 */
string MorphologicalParse::getInflectionalGroupString(int index) const{
    if (index == 0) {
        return root->getName() + "+" + inflectionalGroups.at(0).to_String();
    } else {
        return inflectionalGroups.at(index).to_String();
    }
}

/**
 * The getInflectionalGroup method takes an Integer index as an input and it directly returns the InflectionalGroup
 * at given index.
 *
 * @param index Integer input.
 * @return InflectionalGroup at given index.
 */
InflectionalGroup MorphologicalParse::getInflectionalGroup(int index) const{
    return inflectionalGroups.at(index);
}

/**
 * The getLastInflectionalGroup method directly returns the last InflectionalGroup of inflectionalGroups ArrayList.
 *
 * @return the last InflectionalGroup of inflectionalGroups ArrayList.
 */
InflectionalGroup MorphologicalParse::getLastInflectionalGroup() const{
    return getInflectionalGroup(inflectionalGroups.size() - 1);
}

/**
 * The getTag method takes an Integer index as an input and and if the given index is 0, it directly return the root.
 * then, it loops through the inflectionalGroups ArrayList it returns the MorphologicalTag of the corresponding inflectional group.
 *
 * @param index Integer input.
 * @return the MorphologicalTag of the corresponding inflectional group, or null of invalid index inputs.
 */
string MorphologicalParse::getTag(int index) const{
    int size = 1;
    if (index == 0)
        return root->getName();
    for (const InflectionalGroup& group : inflectionalGroups) {
        if (index < size + group.size()) {
            return InflectionalGroup::getTag(group.getTag(index - size));
        }
        size += group.size();
    }
    return "";
}

/**
 * The tagSize method loops through the inflectionalGroups ArrayList and accumulates the sizes of each inflectional group
 * in the inflectionalGroups.
 *
 * @return total size of the inflectionalGroups ArrayList.
 */
int MorphologicalParse::tagSize() const{
    int size = 1;
    for (const InflectionalGroup& group : inflectionalGroups) {
        size += group.size();
    }
    return size;
}

/**
 * The size method returns the size of the inflectionalGroups ArrayList.
 *
 * @return the size of the inflectionalGroups ArrayList.
 */
int MorphologicalParse::size() const{
    return inflectionalGroups.size();
}

/**
 * The firstInflectionalGroup method returns the first inflectional group of inflectionalGroups ArrayList.
 *
 * @return the first inflectional group of inflectionalGroups ArrayList.
 */
InflectionalGroup MorphologicalParse::firstInflectionalGroup() const{
    return inflectionalGroups.at(0);
}

/**
 * The lastInflectionalGroup method returns the last inflectional group of inflectionalGroups ArrayList.
 *
 * @return the last inflectional group of inflectionalGroups ArrayList.
 */
InflectionalGroup MorphologicalParse::lastInflectionalGroup() const{
    return inflectionalGroups.at(inflectionalGroups.size() - 1);
}

/**
 * The getWordWithPos method returns root with the MorphologicalTag of the first inflectional as a new word.
 *
 * @return root with the MorphologicalTag of the first inflectional as a new word.
 */
Word* MorphologicalParse::getWordWithPos() const{
    return new Word(root->getName() + "+" + InflectionalGroup::getTag(firstInflectionalGroup().getTag(0)));
}

/**
 * The getPos method returns the MorphologicalTag of the last inflectional group.
 *
 * @return the MorphologicalTag of the last inflectional group.
 */
string MorphologicalParse::getPos() const{
    return InflectionalGroup::getTag(lastInflectionalGroup().getTag(0));
}

/**
 * The getRootPos method returns the MorphologicalTag of the first inflectional group.
 *
 * @return the MorphologicalTag of the first inflectional group.
 */
string MorphologicalParse::getRootPos() const{
    return InflectionalGroup::getTag(firstInflectionalGroup().getTag(0));
}

/**
 * The lastIGContainsCase method returns the MorphologicalTag of last inflectional group if it is one of the NOMINATIVE,
 * ACCUSATIVE, DATIVE, LOCATIVE or ABLATIVE cases, null otherwise.
 *
 * @return the MorphologicalTag of last inflectional group if it is one of the NOMINATIVE,
 * ACCUSATIVE, DATIVE, LOCATIVE or ABLATIVE cases, null otherwise.
 */
string MorphologicalParse::lastIGContainsCase() const{
    MorphologicalTag caseTag = lastInflectionalGroup().containsCase();
    if (caseTag != MorphologicalTag::NOTAG)
        return InflectionalGroup::getTag(caseTag);
    else
        return "NULL";
}

/**
 * The lastIGContainsTag method takes a MorphologicalTag as an input and returns true if the last inflectional group's
 * MorphologicalTag matches with one of the tags in the IG ArrayList, falze otherwise.
 *
 * @param tag MorphologicalTag type input.
 * @return true if the last inflectional group's MorphologicalTag matches with one of the tags in the IG ArrayList, false otherwise.
 */
bool MorphologicalParse::lastIGContainsTag(MorphologicalTag tag) const{
    return lastInflectionalGroup().containsTag(tag);
}

/**
 * lastIGContainsPossessive method returns true if the last inflectional group contains one of the
 * possessives: P1PL, P1SG, P2PL, P2SG, P3PL AND P3SG, false otherwise.
 *
 * @return true if the last inflectional group contains one of the possessives: P1PL, P1SG, P2PL, P2SG, P3PL AND P3SG, false otherwise.
 */
bool MorphologicalParse::lastIGContainsPossessive() const{
    return lastInflectionalGroup().containsPossessive();
}

/**
 * The isCapitalWord method returns true if the character at first index o f root is an uppercase letter, false otherwise.
 *
 * @return true if the character at first index o f root is an uppercase letter, false otherwise.
 */
bool MorphologicalParse::isCapitalWord() const{
    return TurkishLanguage::isUppercase(Word::charAt(root->getName(), 0));
}

/**
 * The isNoun method returns true if the past of speech is NOUN, false otherwise.
 *
 * @return true if the past of speech is NOUN, false otherwise.
 */
bool MorphologicalParse::isNoun() const{
    return getPos() == "NOUN";
}

/**
 * The isVerb method returns true if the past of speech is VERB, false otherwise.
 *
 * @return true if the past of speech is VERB, false otherwise.
 */
bool MorphologicalParse::isVerb() const{
    return getPos() == "VERB";
}

/**
 * The isRootVerb method returns true if the past of speech of root is BERV, false otherwise.
 *
 * @return true if the past of speech of root is VERB, false otherwise.
 */
bool MorphologicalParse::isRootVerb() const{
    return getRootPos() == "VERB";
}

/**
 * The isAdjective method returns true if the past of speech is ADJ, false otherwise.
 *
 * @return true if the past of speech is ADJ, false otherwise.
 */
bool MorphologicalParse::isAdjective() const{
    return getPos() == "ADJ";
}

/**
 * The isProperNoun method returns true if the first inflectional group's MorphologicalTag is a PROPERNOUN, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PROPERNOUN, false otherwise.
 */
bool MorphologicalParse::isProperNoun() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PROPERNOUN);
}

/**
 * The isPunctuation method returns true if the first inflectional group's MorphologicalTag is a PUNCTUATION, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PUNCTUATION, false otherwise.
 */
bool MorphologicalParse::isPunctuation() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PUNCTUATION);
}

/**
 * The isCardinal method returns true if the first inflectional group's MorphologicalTag is a CARDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a CARDINAL, false otherwise.
 */
bool MorphologicalParse::isCardinal() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::CARDINAL);
}

/**
 * The isOrdinal method returns true if the first inflectional group's MorphologicalTag is a ORDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a ORDINAL, false otherwise.
 */
bool MorphologicalParse::isOrdinal() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::ORDINAL);
}

/**
 * The isReal method returns true if the first inflectional group's MorphologicalTag is a REAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a REAL, false otherwise.
 */
bool MorphologicalParse::isReal() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::REAL);
}

/**
 * The isNumber method returns true if the first inflectional group's MorphologicalTag is REAL or CARDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a REAL or CARDINAL, false otherwise.
 */
bool MorphologicalParse::isNumber() const{
    return isReal() || isCardinal();
}

/**
 * The isTime method returns true if the first inflectional group's MorphologicalTag is a TIME, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a TIME, false otherwise.
 */
bool MorphologicalParse::isTime() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::TIME);
}

/**
 * The isDate method returns true if the first inflectional group's MorphologicalTag is a DATE, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a DATE, false otherwise.
 */
bool MorphologicalParse::isDate() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::DATE);
}

/**
 * The isHashTag method returns true if the first inflectional group's MorphologicalTag is a HASHTAG, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a HASHTAG, false otherwise.
 */
bool MorphologicalParse::isHashTag() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::HASHTAG);
}

/**
 * The isEmail method returns true if the first inflectional group's MorphologicalTag is a EMAIL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a EMAIL, false otherwise.
 */
bool MorphologicalParse::isEmail() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::EMAIL);
}

/**
 * The isPercent method returns true if the first inflectional group's MorphologicalTag is a PERCENT, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PERCENT, false otherwise.
 */
bool MorphologicalParse::isPercent() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PERCENT);
}

/**
 * The isFraction method returns true if the first inflectional group's MorphologicalTag is a FRACTION, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a FRACTION, false otherwise.
 */
bool MorphologicalParse::isFraction() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::FRACTION);
}

/**
 * The isRange method returns true if the first inflectional group's MorphologicalTag is a RANGE, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a RANGE, false otherwise.
 */
bool MorphologicalParse::isRange() const{
    return getInflectionalGroup(0).containsTag(MorphologicalTag::RANGE);
}

/**
 * The isPlural method returns true if InflectionalGroup's MorphologicalTags are from the agreement plural
 * or possessive plural, i.e A1PL, A2PL, A3PL, P1PL, P2PL or P3PL, and false otherwise.
 *
 * @return true if InflectionalGroup's MorphologicalTags are from the agreement plural or possessive plural.
 */
bool MorphologicalParse::isPlural() const{
    for (const InflectionalGroup& inflectionalGroup : inflectionalGroups)
        if (inflectionalGroup.containsPlural()) {
            return true;
        }
    return false;
}

/**
 * The isAuxiliary method returns true if the root equals to the et, ol, or yap, and false otherwise.
 *
 * @return true if the root equals to the et, ol, or yap, and false otherwise.
 */
bool MorphologicalParse::isAuxiliary() const{
    return root->getName() == "et" || root->getName() == "ol" || root->getName() == "yap";
}

/**
 * The containsTag method takes a MorphologicalTag as an input and loops through the inflectionalGroups ArrayList,
 * returns true if the input matches with on of the tags in the IG, false otherwise.
 *
 * @param tag checked tag
 * @return true if the input matches with on of the tags in the IG, false otherwise.
 */
bool MorphologicalParse::containsTag(MorphologicalTag tag) const{
    for (const InflectionalGroup& inflectionalGroup : inflectionalGroups) {
        if (inflectionalGroup.containsTag(tag)) {
            return true;
        }
    }
    return false;
}

/**
 * The getTreePos method returns the tree pos tag of a morphological analysis.
 *
 * @return Tree pos tag of the morphological analysis in string form.
 */
string MorphologicalParse::getTreePos() const{
    if (isProperNoun()){
        return "NP";
    } else {
        if (root->getName() == "değil"){
            return "NEG";
        } else {
            if (isVerb()){
                if (lastIGContainsTag(MorphologicalTag::ZERO)){
                    return "NOMP";
                } else {
                    return "VP";
                }
            } else {
                if (isAdjective()){
                    return "ADJP";
                } else {
                    if (isNoun() || isPercent()){
                        return "NP";
                    } else {
                        if (containsTag(MorphologicalTag::ADVERB)){
                            return "ADVP";
                        } else {
                            if (isNumber() || isFraction()){
                                return "NUM";
                            } else {
                                if (containsTag(MorphologicalTag::POSTPOSITION)){
                                    return "PP";
                                } else {
                                    if (containsTag(MorphologicalTag::CONJUNCTION)){
                                        return "CONJP";
                                    } else {
                                        if (containsTag(MorphologicalTag::DETERMINER)){
                                            return "DP";
                                        } else {
                                            if (containsTag(MorphologicalTag::INTERJECTION)){
                                                return "INTJP";
                                            } else {
                                                if (containsTag(MorphologicalTag::QUESTIONPRONOUN)){
                                                    return "WP";
                                                } else {
                                                    if (containsTag(MorphologicalTag::PRONOUN)){
                                                        return "NP";
                                                    } else {
                                                        if (isPunctuation()){
                                                            if (root->getName() == "!" || root->getName() == "?"){
                                                                return ".";
                                                            } else {
                                                                if (root->getName() == ";" || root->getName() == "-" || root->getName() == "--") {
                                                                    return ":";
                                                                } else {
                                                                    if (root->getName() == "(" ||
                                                                        root->getName() == "-LRB-" ||
                                                                        root->getName() == "-lrb-") {
                                                                        return "-LRB-";
                                                                    } else {
                                                                        if (root->getName() == ")" ||
                                                                            root->getName() == "-RRB-" ||
                                                                            root->getName() == "-rrb-") {
                                                                            return "-rrb-";
                                                                        } else {
                                                                            return root->getName();
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
    }
    return "-XXX-";
}

/**
 * Returns the pronoun type of the parse for universal dependency feature ProType.
 * @return "Art" if the pronoun is also a determiner; "Prs" if the pronoun is personal pronoun; "Rcp" if the
 * pronoun is 'birbiri'; "Ind" if the pronoun is an indeterminate pronoun; "Neg" if the pronoun is 'hiçbiri';
 * "Int" if the pronoun is a question pronoun; "Dem" if the pronoun is a demonstrative pronoun.
 */
string MorphologicalParse::getPronType() const{
    string lemma = root->getName();
    if (containsTag(MorphologicalTag::DETERMINER)){
        return "Art";
    }
    if (lemma == "kendi" || containsTag(MorphologicalTag::PERSONALPRONOUN)){
        return "Prs";
    }
    if (lemma == "birbiri" || lemma == "birbirleri"){
        return "Rcp";
    }
    if (lemma == "birçoğu" || lemma == "hep" || lemma == "kimse"
        || lemma == "bazı" || lemma == "biri" || lemma == "çoğu"
        || lemma == "hepsi" || lemma == "diğeri" || lemma == "tümü"
        || lemma == "herkes" || lemma == "kimi" || lemma == "öbür"
        || lemma == "öteki" || lemma == "birkaçı" || lemma == "topu"
        || lemma == "başkası"){
        return "Ind";
    }
    if (lemma == "hiçbiri"){
        return "Neg";
    }
    if (lemma == "kim" || lemma == "nere" || lemma == "ne"
        || lemma == "hangi" || lemma == "nasıl" || lemma == "kaç"
        || lemma == "mi" || lemma == "mı" || lemma == "mu" || lemma == "mü"){
        return "Int";
    }
    if (containsTag(MorphologicalTag::DEMONSTRATIVEPRONOUN)){
        return "Dem";
    }
    return "";
}

/**
 * Returns the numeral type of the parse for universal dependency feature NumType.
 * @return "Ord" if the parse is Time, Ordinal or the word is '%' or 'kaçıncı'; "Dist" if the word is a
 * distributive number such as 'beşinci'; "Card" if the number is cardinal or any number or the word is 'kaç'.
 */
string MorphologicalParse::getNumType() const{
    string lemma = root->getName();
    if (lemma == "%" || containsTag(MorphologicalTag::TIME)){
        return "Ord";
    }
    if (containsTag(MorphologicalTag::ORDINAL) || lemma == "kaçıncı"){
        return "Ord";
    }
    if (containsTag(MorphologicalTag::DISTRIBUTIVE)){
        return "Dist";
    }
    if (containsTag(MorphologicalTag::CARDINAL) || containsTag(MorphologicalTag::NUMBER) || lemma == "kaç"){
        return "Card";
    }
    return "";
}

/**
 * Returns the value for the dependency feature Reflex.
 * @return "Yes" if the root word is 'kendi', null otherwise.
 */
string MorphologicalParse::getReflex() const{
    string lemma = root->getName();
    if (lemma == "kendi"){
        return "Yes";
    }
    return "";
}

/**
 * Returns the agreement of the parse for the universal dependency feature Number.
 * @return "Sing" if the agreement of the parse is singular (contains A1SG, A2SG, A3SG); "Plur" if the agreement
 * of the parse is plural (contains A1PL, A2PL, A3PL).
 */
string MorphologicalParse::getNumber() const{
    if (lastIGContainsTag(MorphologicalTag::A1SG) || lastIGContainsTag(MorphologicalTag::A2SG) || lastIGContainsTag(MorphologicalTag::A3SG)
        || lastIGContainsTag(MorphologicalTag::P1SG) || lastIGContainsTag(MorphologicalTag::P2SG) || lastIGContainsTag(MorphologicalTag::P3SG)){
        return "Sing";
        }
    if (lastIGContainsTag(MorphologicalTag::A1PL) || lastIGContainsTag(MorphologicalTag::A2PL) || lastIGContainsTag(MorphologicalTag::A3PL)
        || lastIGContainsTag(MorphologicalTag::P1PL) || lastIGContainsTag(MorphologicalTag::P2PL) || lastIGContainsTag(MorphologicalTag::P3PL)){
        return "Plur";
        }
    if (containsTag(MorphologicalTag::A1SG) || containsTag(MorphologicalTag::A2SG) || containsTag(MorphologicalTag::A3SG)
        || containsTag(MorphologicalTag::P1SG) || containsTag(MorphologicalTag::P2SG) || containsTag(MorphologicalTag::P3SG)){
        return "Sing";
    }
    if (containsTag(MorphologicalTag::A1PL) || containsTag(MorphologicalTag::A2PL) || containsTag(MorphologicalTag::A3PL)
        || containsTag(MorphologicalTag::P1PL) || containsTag(MorphologicalTag::P2PL) || containsTag(MorphologicalTag::P3PL)){
        return "Plur";
    }
    return "";
}

/**
 * Returns the possessive agreement of the parse for the universal dependency feature [Pos].
 * @return "Sing" if the possessive agreement of the parse is singular (contains P1SG, P2SG, P3SG); "Plur" if the
 * possessive agreement of the parse is plural (contains P1PL, P2PL, P3PL).
 */
string MorphologicalParse::getPossessiveNumber() const{
    if (lastIGContainsTag(MorphologicalTag::P1SG) || lastIGContainsTag(MorphologicalTag::P2SG) || lastIGContainsTag(MorphologicalTag::P3SG)){
        return "Sing";
    }
    if (lastIGContainsTag(MorphologicalTag::P1PL) || lastIGContainsTag(MorphologicalTag::P2PL) || lastIGContainsTag(MorphologicalTag::P3PL)){
        return "Plur";
    }
    if (containsTag(MorphologicalTag::P1SG) || containsTag(MorphologicalTag::P2SG) || containsTag(MorphologicalTag::P3SG)){
        return "Sing";
    }
    if (containsTag(MorphologicalTag::P1PL) || containsTag(MorphologicalTag::P2PL) || containsTag(MorphologicalTag::P3PL)){
        return "Plur";
    }
    return "";
}

/**
 * Returns the case marking of the parse for the universal dependency feature case.
 * @return "Acc" for accusative marker; "Dat" for dative marker; "Gen" for genitive marker; "Loc" for locative
 * marker; "Ins" for instrumentative marker; "Abl" for ablative marker; "Nom" for nominative marker.
 */
string MorphologicalParse::getCase() const{
    if (containsTag(MorphologicalTag::ACCUSATIVE) || containsTag(MorphologicalTag::PCACCUSATIVE)){
        return "Acc";
    }
    if (containsTag(MorphologicalTag::DATIVE) || containsTag(MorphologicalTag::PCDATIVE)){
        return "Dat";
    }
    if (containsTag(MorphologicalTag::GENITIVE) || containsTag(MorphologicalTag::PCGENITIVE)){
        return "Gen";
    }
    if (containsTag(MorphologicalTag::LOCATIVE)){
        return "Loc";
    }
    if (containsTag(MorphologicalTag::INSTRUMENTAL) || containsTag(MorphologicalTag::PCINSTRUMENTAL)){
        return "Ins";
    }
    if (containsTag(MorphologicalTag::ABLATIVE) || containsTag(MorphologicalTag::PCABLATIVE)){
        return "Abl";
    }
    if (containsTag(MorphologicalTag::EQUATIVE)){
        return "Equ";
    }
    if (containsTag(MorphologicalTag::NOMINATIVE) || containsTag(MorphologicalTag::PCNOMINATIVE)){
        return "Nom";
    }
    return "";
}

/**
 * Returns the definiteness of the parse for the universal dependency feature definite. It applies only for
 * determiners in Turkish.
 * @return "Ind" for 'bir', 'bazı', or 'birkaç'. "Def" for 'her', 'bu', 'şu', 'o', 'bütün'.
 */
string MorphologicalParse::getDefinite() const{
    string lemma = root->getName();
    if (containsTag(MorphologicalTag::DETERMINER)){
        if (lemma == "bir" || lemma == "bazı" || lemma == "birkaç" ||
        lemma == "birçok" || lemma == "kimi"){
            return "Ind";
        }
        if (lemma == "her" || lemma == "bu" || lemma == "şu" ||
        lemma == "o" || lemma == "bütün" || lemma == "hangi"){
            return "Def";
        }
    }
    return "";
}

/**
 * Returns the degree of the parse for the universal dependency feature degree.
 * @return "Cmp" for comparative adverb 'daha'; "Sup" for superlative adjective or adverb 'en'.
 */
string MorphologicalParse::getDegree() const{
    string lemma = root->getName();
    if (lemma == "daha"){
        return "Cmp";
    }
    if (lemma == "en" && !isNoun()){
        return "Sup";
    }
    return "";
}

/**
 * Returns the polarity of the verb for the universal dependency feature polarity.
 * @return "Pos" for positive polarity containing tag POS; "Neg" for negative polarity containing tag NEG.
 */
string MorphologicalParse::getPolarity() const{
    if (root->getName() == "değil"){
        return "Neg";
    }
    if (containsTag(MorphologicalTag::POSITIVE)){
        return "Pos";
    }
    if (containsTag(MorphologicalTag::NEGATIVE)){
        return "Neg";
    }
    return "";
}

/**
 * Returns the person of the agreement of the parse for the universal dependency feature person.
 * @return "1" for first person; "2" for second person; "3" for third person.
 */
string MorphologicalParse::getPerson() const{
    if (lastIGContainsTag(MorphologicalTag::A1SG) || lastIGContainsTag(MorphologicalTag::A1PL)
        || lastIGContainsTag(MorphologicalTag::P1SG) || lastIGContainsTag(MorphologicalTag::P1PL)){
        return "1";
        }
    if (lastIGContainsTag(MorphologicalTag::A2SG) || lastIGContainsTag(MorphologicalTag::A2PL)
        || lastIGContainsTag(MorphologicalTag::P2SG) || lastIGContainsTag(MorphologicalTag::P2PL)){
        return "2";
        }
    if (lastIGContainsTag(MorphologicalTag::A3SG) || lastIGContainsTag(MorphologicalTag::A3PL)
        || lastIGContainsTag(MorphologicalTag::P3SG) || lastIGContainsTag(MorphologicalTag::P3PL)){
        return "3";
        }
    if (containsTag(MorphologicalTag::A1SG) || containsTag(MorphologicalTag::A1PL)
        || containsTag(MorphologicalTag::P1SG) || containsTag(MorphologicalTag::P1PL)){
        return "1";
    }
    if (containsTag(MorphologicalTag::A2SG) || containsTag(MorphologicalTag::A2PL)
        || containsTag(MorphologicalTag::P2SG) || containsTag(MorphologicalTag::P2PL)){
        return "2";
    }
    if (containsTag(MorphologicalTag::A3SG) || containsTag(MorphologicalTag::A3PL)
        || containsTag(MorphologicalTag::P3SG) || containsTag(MorphologicalTag::P3PL)){
        return "3";
    }
    return "";
}

/**
 * Returns the person of the possessive agreement of the parse for the universal dependency feature [pos].
 * @return "1" for first person; "2" for second person; "3" for third person.
 */
string MorphologicalParse::getPossessivePerson() const{
    if (lastIGContainsTag(MorphologicalTag::P1SG) || lastIGContainsTag(MorphologicalTag::P1PL)){
        return "1";
    }
    if (lastIGContainsTag(MorphologicalTag::P2SG) || lastIGContainsTag(MorphologicalTag::P2PL)){
        return "2";
    }
    if (lastIGContainsTag(MorphologicalTag::P3SG) || lastIGContainsTag(MorphologicalTag::P3PL)){
        return "3";
    }
    if (containsTag(MorphologicalTag::P1SG) || containsTag(MorphologicalTag::P1PL)){
        return "1";
    }
    if (containsTag(MorphologicalTag::P2SG) || containsTag(MorphologicalTag::P2PL)){
        return "2";
    }
    if (containsTag(MorphologicalTag::P3SG) || containsTag(MorphologicalTag::P3PL)){
        return "3";
    }
    return "";
}

/**
 * Returns the voice of the verb parse for the universal dependency feature voice.
 * @return "CauPass" if the verb parse is both causative and passive; "Pass" if the verb parse is only passive;
 * "Rcp" if the verb parse is reciprocal; "Cau" if the verb parse is only causative; "Rfl" if the verb parse is
 * reflexive.
 */
string MorphologicalParse::getVoice() const{
    if (containsTag(MorphologicalTag::CAUSATIVE) && containsTag(MorphologicalTag::PASSIVE)){
        return "CauPass";
    }
    if (containsTag(MorphologicalTag::PASSIVE)){
        return "Pass";
    }
    if (containsTag(MorphologicalTag::RECIPROCAL)){
        return "Rcp";
    }
    if (containsTag(MorphologicalTag::CAUSATIVE)){
        return "Cau";
    }
    if (containsTag(MorphologicalTag::REFLEXIVE)){
        return "Rfl";
    }
    return "";
}

/**
 * Returns the aspect of the verb parse for the universal dependency feature aspect.
 * @return "Perf" for past, narrative and future tenses; "Prog" for progressive tenses; "Hab" for Aorist; "Rapid"
 * for parses containing HASTILY tag; "Dur" for parses containing START, STAY or REPEAT tags.
 */
string MorphologicalParse::getAspect() const{
    if (containsTag(MorphologicalTag::PASTTENSE) || containsTag(MorphologicalTag::NARRATIVE) || containsTag(MorphologicalTag::FUTURE)){
        return "Perf";
    }
    if (containsTag(MorphologicalTag::PROGRESSIVE1) || containsTag(MorphologicalTag::PROGRESSIVE2)){
        return "Prog";
    }
    if (containsTag(MorphologicalTag::AORIST)){
        return "Hab";
    }
    if (containsTag(MorphologicalTag::HASTILY)){
        return "Rapid";
    }
    if (containsTag(MorphologicalTag::START) || containsTag(MorphologicalTag::STAY) || containsTag(MorphologicalTag::REPEAT)){
        return "Dur";
    }
    return "";
}

/**
 * Returns the tense of the verb parse for universal dependency feature tense.
 * @return "Past" for simple past tense; "Fut" for future tense; "Pqp" for narrative past tense; "Pres" for other
 * past tenses.
 */
string MorphologicalParse::getTense() const{
    if (containsTag(MorphologicalTag::NARRATIVE) && containsTag(MorphologicalTag::PASTTENSE)){
        return "Pqp";
    }
    if (containsTag(MorphologicalTag::PASTTENSE) || containsTag(MorphologicalTag::NARRATIVE)){
        return "Past";
    }
    if (containsTag(MorphologicalTag::FUTURE)){
        return "Fut";
    }
    if (!containsTag(MorphologicalTag::PASTTENSE) && !containsTag(MorphologicalTag::FUTURE)){
        return "Pres";
    }
    return "";
}

/**
 * Returns the modality of the verb parse for the universal dependency feature mood.
 * @return "GenNecPot" if both necessitative and potential is combined with a suffix of general modality;
 * "CndGenPot" if both conditional and potential is combined with a suffix of general modality;
 * "GenNec" if necessitative is combined with a suffix of general modality;
 * "GenPot" if potential is combined with a suffix of general modality;
 * "NecPot" if necessitative is combined with potential;
 * "DesPot" if desiderative is combined with potential;
 * "CndPot" if conditional is combined with potential;
 * "CndGen" if conditional is combined with a suffix of general modality;
 * "Imp" for imperative; "Cnd" for simple conditional; "Des" for simple desiderative; "Opt" for optative; "Nec" for
 * simple necessitative; "Pot" for simple potential; "Gen" for simple suffix of a general modality.
 */
string MorphologicalParse::getMood() const{
    if ((containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST)) && containsTag(MorphologicalTag::NECESSITY) && containsTag(MorphologicalTag::ABLE)){
        return "GenNecPot";
    }
    if ((containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST)) && containsTag(MorphologicalTag::CONDITIONAL) && containsTag(MorphologicalTag::ABLE)){
        return "CndGenPot";
    }
    if ((containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST)) && containsTag(MorphologicalTag::NECESSITY)){
        return "GenNec";
    }
    if ((containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST)) && containsTag(MorphologicalTag::ABLE)){
        return "GenPot";
    }
    if (containsTag(MorphologicalTag::NECESSITY) && containsTag(MorphologicalTag::ABLE)){
        return "NecPot";
    }
    if (containsTag(MorphologicalTag::DESIRE) && containsTag(MorphologicalTag::ABLE)){
        return "DesPot";
    }
    if (containsTag(MorphologicalTag::CONDITIONAL) && containsTag(MorphologicalTag::ABLE)){
        return "CndPot";
    }
    if (containsTag(MorphologicalTag::CONDITIONAL) && (containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST))){
        return "CndGen";
    }
    if (containsTag(MorphologicalTag::IMPERATIVE)){
        return "Imp";
    }
    if (containsTag(MorphologicalTag::CONDITIONAL)){
        return "Cnd";
    }
    if (containsTag(MorphologicalTag::DESIRE)){
        return "Des";
    }
    if (containsTag(MorphologicalTag::OPTATIVE)){
        return "Opt";
    }
    if (containsTag(MorphologicalTag::NECESSITY)){
        return "Nec";
    }
    if (containsTag(MorphologicalTag::ABLE)){
        return "Pot";
    }
    if (containsTag(MorphologicalTag::PASTTENSE) || containsTag(MorphologicalTag::NARRATIVE) || containsTag(MorphologicalTag::PROGRESSIVE1) || containsTag(MorphologicalTag::PROGRESSIVE2) || containsTag(MorphologicalTag::FUTURE)){
        return "Ind";
    }
    if ((containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::AORIST))){
        return "Gen";
    }
    if (containsTag(MorphologicalTag::ZERO) && !containsTag(MorphologicalTag::A3PL)){
        return "Gen";
    }
    return "";
}

/**
 * Returns the form of the verb parse for the universal dependency feature verbForm.
 * @return "Part" for participles; "Vnoun" for infinitives; "Conv" for parses contaning tags SINCEDOINGSO,
 * WITHOUTHAVINGDONESO, WITHOUTBEINGABLETOHAVEDONESO, BYDOINGSO, AFTERDOINGSO, INFINITIVE3; "Fin" for others.
 */
string MorphologicalParse::getVerbForm() const{
    if (containsTag(MorphologicalTag::PASTPARTICIPLE) || containsTag(MorphologicalTag::FUTUREPARTICIPLE) || containsTag(MorphologicalTag::PRESENTPARTICIPLE)){
        return "Part";
    }
    if (containsTag(MorphologicalTag::INFINITIVE) || containsTag(MorphologicalTag::INFINITIVE2)){
        return "Vnoun";
    }
    if (containsTag(MorphologicalTag::SINCEDOINGSO) || containsTag(MorphologicalTag::WITHOUTHAVINGDONESO) || containsTag(MorphologicalTag::WITHOUTBEINGABLETOHAVEDONESO) || containsTag(MorphologicalTag::BYDOINGSO) || containsTag(MorphologicalTag::AFTERDOINGSO) || containsTag(MorphologicalTag::INFINITIVE3)){
        return "Conv";
    }
    if (containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::ABLE) || containsTag(MorphologicalTag::AORIST) || containsTag(MorphologicalTag::PROGRESSIVE2)
        || containsTag(MorphologicalTag::DESIRE) || containsTag(MorphologicalTag::NECESSITY) || containsTag(MorphologicalTag::CONDITIONAL) || containsTag(MorphologicalTag::IMPERATIVE) || containsTag(MorphologicalTag::OPTATIVE)
        || containsTag(MorphologicalTag::PASTTENSE) || containsTag(MorphologicalTag::NARRATIVE) || containsTag(MorphologicalTag::PROGRESSIVE1) || containsTag(MorphologicalTag::FUTURE)
        || (containsTag(MorphologicalTag::ZERO) && !containsTag(MorphologicalTag::A3PL))){
        return "Fin";
    }
    return "";
}

string MorphologicalParse::getEvident() const{
    if (containsTag(MorphologicalTag::NARRATIVE)){
        return "Nfh";
    } else {
        if (containsTag(MorphologicalTag::COPULA) || containsTag(MorphologicalTag::ABLE) || containsTag(MorphologicalTag::AORIST) || containsTag(MorphologicalTag::PROGRESSIVE2)
            || containsTag(MorphologicalTag::DESIRE) || containsTag(MorphologicalTag::NECESSITY) || containsTag(MorphologicalTag::CONDITIONAL) || containsTag(MorphologicalTag::IMPERATIVE) || containsTag(MorphologicalTag::OPTATIVE)
            || containsTag(MorphologicalTag::PASTTENSE) || containsTag(MorphologicalTag::NARRATIVE) || containsTag(MorphologicalTag::PROGRESSIVE1) || containsTag(MorphologicalTag::FUTURE)) {
            return "Fh";
        }
    }
    return "";
}

/**
 * Construct the universal dependency features as an array of strings. Each element represents a single feature.
 * Every feature is given as featureType = featureValue.
 * @param uPos Universal dependency part of speech tag for the parse.
 * @return An array of universal dependency features for this parse.
 */
vector<string> MorphologicalParse::getUniversalDependencyFeatures(const string& uPos) const{
    vector<string> featureList;
    string pronType = getPronType();
    if (!pronType.empty() && uPos != "NOUN" && uPos != "ADJ"
    && uPos != "VERB" && uPos != "PROPN" && uPos != "CCONJ"){
        featureList.emplace_back("PronType=" + pronType);
    }
    string numType = getNumType();
    if (!numType.empty() && uPos != "VERB" && uPos != "NOUN" && uPos != "ADV"){
        featureList.emplace_back("NumType=" + numType);
    }
    string reflex = getReflex();
    if (!reflex.empty() && uPos != "ADJ" && uPos != "VERB"){
        featureList.emplace_back("Reflex=" + reflex);
    }
    string degree = getDegree();
    if (!degree.empty() && uPos != "ADJ"){
        featureList.emplace_back("Degree=" + degree);
    }
    if (isNoun() || isVerb() || root->getName() == "mi" || (!pronType.empty() && pronType != "Art")){
        string number = getNumber();
        if (!number.empty()){
            featureList.emplace_back("Number=" + number);
        }
        string possessiveNumber = getPossessiveNumber();
        if (!possessiveNumber.empty()){
            featureList.emplace_back("Number[psor]=" + possessiveNumber);
        }
        string person = getPerson();
        if (!person.empty() && uPos != "PROPN"){
            featureList.emplace_back("Person=" + person);
        }
        string possessivePerson = getPossessivePerson();
        if (!possessivePerson.empty() && uPos != "PROPN"){
            featureList.emplace_back("Person[psor]=" + possessivePerson);
        }
    }
    if (isNoun() || (!pronType.empty() && pronType != "Art")) {
        string case_ = getCase();
        if (!case_.empty()){
            featureList.emplace_back("Case=" + case_);
        }
    }
    if (containsTag(MorphologicalTag::DETERMINER)){
        string definite = getDefinite();
        if (!definite.empty()){
            featureList.emplace_back("Definite=" + definite);
        }
    }
    if (isVerb() || root->getName() == "mi"){
        string polarity = getPolarity();
        if (!polarity.empty()){
            featureList.emplace_back("Polarity=" + polarity);
        }
        string voice = getVoice();
        if (!voice.empty() && root->getName() != "mi"){
            featureList.emplace_back("Voice=" + voice);
        }
        string aspect = getAspect();
        if (!aspect.empty() && uPos != "PROPN" && root->getName() != "mi"){
            featureList.emplace_back("Aspect=" + aspect);
        }
        string tense = getTense();
        if (!tense.empty() && uPos != "PROPN"){
            featureList.emplace_back("Tense=" + tense);
        }
        string mood = getMood();
        if (!mood.empty() && uPos != "PROPN" && root->getName() != "mi"){
            featureList.emplace_back("Mood=" + mood);
        }
        string verbForm = getVerbForm();
        if (!verbForm.empty()){
            featureList.emplace_back("VerbForm=" + verbForm);
        }
        string evident = getEvident();
        if (!evident.empty()){
            featureList.emplace_back("Evident=" + evident);
        }
    }
    sort(featureList.begin(), featureList.end());
    return featureList;
}

/**
 * Returns the universal dependency part of speech for this parse.
 * @return "AUX" for word 'değil; "PROPN" for proper nouns; "NOUN for nouns; "ADJ" for adjectives; "ADV" for
 * adverbs; "INTJ" for interjections; "VERB" for verbs; "PUNCT" for punctuation symbols; "DET" for determiners;
 * "NUM" for numerals; "PRON" for pronouns; "ADP" for post participles; "SCONJ" or "CCONJ" for conjunctions.
 */
string MorphologicalParse::getUniversalDependencyPos() const{
    string lemma = root->getName();
    if (lemma == "değil"){
        return "AUX";
    }
    if (isProperNoun()){
        return "PROPN";
    }
    if (isNoun()){
        return "NOUN";
    }
    if (isAdjective()){
        return "ADJ";
    }
    if (getPos() == "ADV"){
        return "ADV";
    }
    if (containsTag(MorphologicalTag::INTERJECTION)){
        return "INTJ";
    }
    if (isVerb()){
        return "VERB";
    }
    if (isPunctuation() || isHashTag()){
        return "PUNCT";
    }
    if (containsTag(MorphologicalTag::DETERMINER)){
        return "DET";
    }
    if (isNumber() || isDate() || isTime() || isOrdinal() || isFraction() || lemma == "%"){
        return "NUM";
    }
    if (getPos() == "PRON"){
        return "PRON";
    }
    if (getPos() == "POSTP"){
        return "ADP";
    }
    if (getPos() == "QUES"){
        return "AUX";
    }
    if (getPos() == "CONJ"){
        if (lemma == "ki" || lemma == "eğer" || lemma == "diye"){
            return "SCONJ";
        } else {
            return "CCONJ";
        }
    }
    return "X";
}

/**
 * The overridden toString method gets the root and the first inflectional group as a result String then concatenates
 * with ^DB+ and the following inflectional groups.
 *
 * @return result String.
 */
string MorphologicalParse::to_string() const{
    string result = root->getName() + "+" + inflectionalGroups.at(0).to_String();
    for (int i = 1; i < inflectionalGroups.size(); i++)
        result += "^DB+" + inflectionalGroups.at(i).to_String();
    return result;
}