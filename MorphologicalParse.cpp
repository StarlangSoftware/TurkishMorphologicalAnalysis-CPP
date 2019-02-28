//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "MorphologicalParse.h"
#include "TurkishLanguage.h"

/**
 * An empty constructor of {@link MorphologicalParse} class.
 */
MorphologicalParse::MorphologicalParse() = default;

/**
 * The no-arg getWord method returns root {@link Word}.
 *
 * @return root {@link Word}.
 */
Word* MorphologicalParse::getWord() {
    return root;
}

/**
 * Another constructor of {@link MorphologicalParse} class which takes a {@link String} parse as an input. First it creates
 * an {@link ArrayList} as iGs for inflectional groups, and while given String contains derivational boundary (^DB+), it
 * adds the substring to the iGs {@link ArrayList} and continue to use given String from 4th index. If it does not contain ^DB+,
 * it directly adds the given String to the iGs {@link ArrayList}. Then, it creates a new {@link ArrayList} as
 * inflectionalGroups and checks for some cases.
 * <p>
 * If the first item of iGs {@link ArrayList} is ++Punc, it creates a new root as +, and by calling
 * {@link InflectionalGroup} method with Punc it initializes the IG {@link ArrayList} by parsing given input
 * String IG by + and calling the getMorphologicalTag method with these substrings. If getMorphologicalTag method returns
 * a tag, it adds this tag to the IG {@link ArrayList} and also to the inflectionalGroups {@link ArrayList}.
 * <p>
 * If the first item of iGs {@link ArrayList} has +, it creates a new word of first item's substring from index 0 to +,
 * and assigns it to root. Then, by calling {@link InflectionalGroup} method with substring from index 0 to +,
 * it initializes the IG {@link ArrayList} by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG {@link ArrayList}
 * and also to the inflectionalGroups {@link ArrayList}.
 * <p>
 * If the first item of iGs {@link ArrayList} does not contain +, it creates a new word with first item and assigns it as root.
 * <p>
 * At the end, it loops through the items of iGs and by calling {@link InflectionalGroup} method with these items
 * it initializes the IG {@link ArrayList} by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG {@link ArrayList}
 * and also to the inflectionalGroups {@link ArrayList}.
 *
 * @param parse String input.
 */
MorphologicalParse::MorphologicalParse(string parse) {
    int i;
    vector<string> iGs;
    string st = move(parse);
    while (st.find("^DB+") != string::npos) {
        iGs.emplace_back(st.substr(0, st.find("^DB+")));
        st = st.substr(st.find("^DB+") + 4, st.size());
    }
    iGs.emplace_back(st);
    if (iGs.at(0) == "++Punc") {
        root = new Word("+");
        inflectionalGroups.emplace_back(InflectionalGroup("Punc"));
    } else {
        if (iGs.at(0).find('+') != string::npos) {
            root = new Word(iGs.at(0).substr(0, iGs.at(0).find('+')));
            inflectionalGroups.emplace_back(InflectionalGroup(iGs.at(0).substr(iGs.at(0).find('+') + 1, iGs.at(0).size())));
        } else {
            root = new Word(iGs.at(0));
        }
        for (i = 1; i < iGs.size(); i++) {
            inflectionalGroups.emplace_back(InflectionalGroup(iGs.at(i)));
        }
    }
}

/**
 * Another constructor of {@link MorphologicalParse} class which takes an {@link vector} inflectionalGroups as an input.
 * First, it initializes inflectionalGroups {@link ArrayList} and if the first item of the {@link vector} has +, it gets
 * the substring from index 0 to + and assigns it as root, and by calling {@link InflectionalGroup} method with substring from index 0 to +,
 * it initializes the IG {@link vector} by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG {@link vector}
 * and also to the inflectionalGroups {@link vector}. However, if the first item does not contain +, it directly prints out
 * indicating that there is no root for that item of this Inflectional Group.
 * <p>
 * At the end, it loops through the items of inflectionalGroups and by calling {@link InflectionalGroup} method with these items
 * it initializes the IG {@link vector} by parsing given input String IG by + and calling the getMorphologicalTag
 * method with these substrings. If getMorphologicalTag method returns a tag, it adds this tag to the IG {@link vector}
 * and also to the inflectionalGroups {@link vector}.
 *
 * @param inflectionalGroups {@link vector} input.
 */
MorphologicalParse::MorphologicalParse(vector<string> inflectionalGroups) {
    int i;
    if (inflectionalGroups.at(0).find('+') != string::npos) {
        root = new Word(inflectionalGroups.at(0).substr(0, inflectionalGroups.at(0).find('+')));
        this->inflectionalGroups.emplace_back(InflectionalGroup(inflectionalGroups.at(0).substr(inflectionalGroups.at(0).find('+') + 1, inflectionalGroups.at(0).size())));
    }
    for (i = 1; i < inflectionalGroups.size(); i++) {
        this->inflectionalGroups.emplace_back(InflectionalGroup(inflectionalGroups.at(i)));
    }
}

/**
 * The getTransitionList method gets the first item of inflectionalGroups {@link ArrayList} as a {@link String}, then loops
 * through the items of inflectionalGroups and concatenates them by using +.
 *
 * @return String that contains transition list.
 */
string MorphologicalParse::getTransitionList() {
    string result = inflectionalGroups.at(0).to_String();
    for (int i = 1; i < inflectionalGroups.size(); i++) {
        result.append("+");
        result.append(inflectionalGroups.at(i).to_String());
    }
    return result;
}

/**
 * The getInflectionalGroupString method takes an {@link Integer} index as an input and if index is 0, it directly returns the
 * root and the first item of inflectionalGroups {@link vector}. If the index is not 0, it then returns the corresponding
 * item of inflectionalGroups {@link vector} as a {@link String}.
 *
 * @param index Integer input.
 * @return corresponding item of inflectionalGroups at given index as a {@link String}.
 */
string MorphologicalParse::getInflectionalGroupString(int index) {
    if (index == 0) {
        return root->getName() + "+" + inflectionalGroups.at(0).to_String();
    } else {
        return inflectionalGroups.at(index).to_String();
    }
}

/**
 * The getInflectionalGroup method takes an {@link Integer} index as an input and it directly returns the {@link InflectionalGroup}
 * at given index.
 *
 * @param index Integer input.
 * @return InflectionalGroup at given index.
 */
InflectionalGroup MorphologicalParse::getInflectionalGroup(int index) {
    return inflectionalGroups.at(index);
}

/**
 * The getLastInflectionalGroup method directly returns the last {@link InflectionalGroup} of inflectionalGroups {@link ArrayList}.
 *
 * @return the last {@link InflectionalGroup} of inflectionalGroups {@link ArrayList}.
 */
InflectionalGroup MorphologicalParse::getLastInflectionalGroup() {
    return getInflectionalGroup(inflectionalGroups.size() - 1);
}

/**
 * The getTag method takes an {@link Integer} index as an input and and if the given index is 0, it directly return the root.
 * then, it loops through the inflectionalGroups {@link ArrayList} it returns the MorphologicalTag of the corresponding inflectional group.
 *
 * @param index Integer input.
 * @return the MorphologicalTag of the corresponding inflectional group, or null of invalid index inputs.
 */
string MorphologicalParse::getTag(int index) {
    int size = 1;
    if (index == 0)
        return root->getName();
    for (InflectionalGroup group : inflectionalGroups) {
        if (index < size + group.size()) {
            return InflectionalGroup::getTag(group.getTag(index - size));
        }
        size += group.size();
    }
    return "";
}

/**
 * The tagSize method loops through the inflectionalGroups {@link ArrayList} and accumulates the sizes of each inflectional group
 * in the inflectionalGroups.
 *
 * @return total size of the inflectionalGroups {@link ArrayList}.
 */
int MorphologicalParse::tagSize() {
    int size = 1;
    for (InflectionalGroup group : inflectionalGroups) {
        size += group.size();
    }
    return size;
}

/**
 * The size method returns the size of the inflectionalGroups {@link ArrayList}.
 *
 * @return the size of the inflectionalGroups {@link ArrayList}.
 */
int MorphologicalParse::size() {
    return inflectionalGroups.size();
}

/**
 * The firstInflectionalGroup method returns the first inflectional group of inflectionalGroups {@link ArrayList}.
 *
 * @return the first inflectional group of inflectionalGroups {@link ArrayList}.
 */
InflectionalGroup MorphologicalParse::firstInflectionalGroup() {
    return inflectionalGroups.at(0);
}

/**
 * The lastInflectionalGroup method returns the last inflectional group of inflectionalGroups {@link ArrayList}.
 *
 * @return the last inflectional group of inflectionalGroups {@link ArrayList}.
 */
InflectionalGroup MorphologicalParse::lastInflectionalGroup() {
    return inflectionalGroups.at(inflectionalGroups.size() - 1);
}

/**
 * The getWordWithPos method returns root with the MorphologicalTag of the first inflectional as a new word.
 *
 * @return root with the MorphologicalTag of the first inflectional as a new word.
 */
Word* MorphologicalParse::getWordWithPos() {
    return new Word(root->getName() + "+" + InflectionalGroup::getTag(firstInflectionalGroup().getTag(0)));
}

/**
 * The getPos method returns the MorphologicalTag of the last inflectional group.
 *
 * @return the MorphologicalTag of the last inflectional group.
 */
string MorphologicalParse::getPos() {
    return InflectionalGroup::getTag(lastInflectionalGroup().getTag(0));
}

/**
 * The getRootPos method returns the MorphologicalTag of the first inflectional group.
 *
 * @return the MorphologicalTag of the first inflectional group.
 */
string MorphologicalParse::getRootPos() {
    return InflectionalGroup::getTag(firstInflectionalGroup().getTag(0));
}

/**
 * The lastIGContainsCase method returns the MorphologicalTag of last inflectional group if it is one of the NOMINATIVE,
 * ACCUSATIVE, DATIVE, LOCATIVE or ABLATIVE cases, null otherwise.
 *
 * @return the MorphologicalTag of last inflectional group if it is one of the NOMINATIVE,
 * ACCUSATIVE, DATIVE, LOCATIVE or ABLATIVE cases, null otherwise.
 */
string MorphologicalParse::lastIGContainsCase() {
    MorphologicalTag caseTag = lastInflectionalGroup().containsCase();
    if (caseTag != MorphologicalTag::NOTAG)
        return InflectionalGroup::getTag(caseTag);
    else
        return "NULL";
}

/**
 * The lastIGContainsTag method takes a MorphologicalTag as an input and returns true if the last inflectional group's
 * MorphologicalTag matches with one of the tags in the IG {@link ArrayList}, falze otherwise.
 *
 * @param tag {@link MorphologicalTag} type input.
 * @return true if the last inflectional group's MorphologicalTag matches with one of the tags in the IG {@link ArrayList}, false otherwise.
 */
bool MorphologicalParse::lastIGContainsTag(MorphologicalTag tag) {
    return lastInflectionalGroup().containsTag(tag);
}

/**
 * lastIGContainsPossessive method returns true if the last inflectional group contains one of the
 * possessives: P1PL, P1SG, P2PL, P2SG, P3PL AND P3SG, false otherwise.
 *
 * @return true if the last inflectional group contains one of the possessives: P1PL, P1SG, P2PL, P2SG, P3PL AND P3SG, false otherwise.
 */
bool MorphologicalParse::lastIGContainsPossessive() {
    return lastInflectionalGroup().containsPossessive();
}

/**
 * The isCapitalWord method returns true if the character at first index o f root is an uppercase letter, false otherwise.
 *
 * @return true if the character at first index o f root is an uppercase letter, false otherwise.
 */
bool MorphologicalParse::isCapitalWord() {
    return TurkishLanguage::isUppercase(Word::charAt(root->getName(), 0));
}

/**
 * The isNoun method returns true if the past of speech is NOUN, false otherwise.
 *
 * @return true if the past of speech is NOUN, false otherwise.
 */
bool MorphologicalParse::isNoun() {
    return getPos() == "NOUN";
}

/**
 * The isVerb method returns true if the past of speech is VERB, false otherwise.
 *
 * @return true if the past of speech is VERB, false otherwise.
 */
bool MorphologicalParse::isVerb() {
    return getPos() == "VERB";
}

/**
 * The isRootVerb method returns true if the past of speech of root is BERV, false otherwise.
 *
 * @return true if the past of speech of root is VERB, false otherwise.
 */
bool MorphologicalParse::isRootVerb() {
    return getRootPos() == "VERB";
}

/**
 * The isAdjective method returns true if the past of speech is ADJ, false otherwise.
 *
 * @return true if the past of speech is ADJ, false otherwise.
 */
bool MorphologicalParse::isAdjective() {
    return getPos() == "ADJ";
}

/**
 * The isProperNoun method returns true if the first inflectional group's MorphologicalTag is a PROPERNOUN, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PROPERNOUN, false otherwise.
 */
bool MorphologicalParse::isProperNoun() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PROPERNOUN);
}

/**
 * The isPunctuation method returns true if the first inflectional group's MorphologicalTag is a PUNCTUATION, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PUNCTUATION, false otherwise.
 */
bool MorphologicalParse::isPunctuation() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PUNCTUATION);
}

/**
 * The isCardinal method returns true if the first inflectional group's MorphologicalTag is a CARDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a CARDINAL, false otherwise.
 */
bool MorphologicalParse::isCardinal() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::CARDINAL);
}

/**
 * The isOrdinal method returns true if the first inflectional group's MorphologicalTag is a ORDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a ORDINAL, false otherwise.
 */
bool MorphologicalParse::isOrdinal() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::ORDINAL);
}

/**
 * The isReal method returns true if the first inflectional group's MorphologicalTag is a REAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a REAL, false otherwise.
 */
bool MorphologicalParse::isReal() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::REAL);
}

/**
 * The isNumber method returns true if the first inflectional group's MorphologicalTag is REAL or CARDINAL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a REAL or CARDINAL, false otherwise.
 */
bool MorphologicalParse::isNumber() {
    return isReal() || isCardinal();
}

/**
 * The isTime method returns true if the first inflectional group's MorphologicalTag is a TIME, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a TIME, false otherwise.
 */
bool MorphologicalParse::isTime() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::TIME);
}

/**
 * The isDate method returns true if the first inflectional group's MorphologicalTag is a DATE, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a DATE, false otherwise.
 */
bool MorphologicalParse::isDate() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::DATE);
}

/**
 * The isHashTag method returns true if the first inflectional group's MorphologicalTag is a HASHTAG, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a HASHTAG, false otherwise.
 */
bool MorphologicalParse::isHashTag() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::HASHTAG);
}

/**
 * The isEmail method returns true if the first inflectional group's MorphologicalTag is a EMAIL, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a EMAIL, false otherwise.
 */
bool MorphologicalParse::isEmail() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::EMAIL);
}

/**
 * The isPercent method returns true if the first inflectional group's MorphologicalTag is a PERCENT, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a PERCENT, false otherwise.
 */
bool MorphologicalParse::isPercent() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::PERCENT);
}

/**
 * The isFraction method returns true if the first inflectional group's MorphologicalTag is a FRACTION, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a FRACTION, false otherwise.
 */
bool MorphologicalParse::isFraction() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::FRACTION);
}

/**
 * The isRange method returns true if the first inflectional group's MorphologicalTag is a RANGE, false otherwise.
 *
 * @return true if the first inflectional group's MorphologicalTag is a RANGE, false otherwise.
 */
bool MorphologicalParse::isRange() {
    return getInflectionalGroup(0).containsTag(MorphologicalTag::RANGE);
}

/**
 * The isPlural method returns true if {@link InflectionalGroup}'s MorphologicalTags are from the agreement plural
 * or possessive plural, i.e A1PL, A2PL, A3PL, P1PL, P2PL or P3PL, and false otherwise.
 *
 * @return true if {@link InflectionalGroup}'s MorphologicalTags are from the agreement plural or possessive plural.
 */
bool MorphologicalParse::isPlural() {
    for (InflectionalGroup inflectionalGroup : inflectionalGroups)
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
bool MorphologicalParse::isAuxiliary() {
    return root->getName() == "et" || root->getName() == "ol" || root->getName() == "yap";
}

/**
 * The containsTag method takes a MorphologicalTag as an input and loops through the inflectionalGroups {@link ArrayList},
 * returns true if the input matches with on of the tags in the IG, false otherwise.
 *
 * @param tag checked tag
 * @return true if the input matches with on of the tags in the IG, false otherwise.
 */
bool MorphologicalParse::containsTag(MorphologicalTag tag) {
    for (InflectionalGroup inflectionalGroup : inflectionalGroups) {
        if (inflectionalGroup.containsTag(tag)) {
            return true;
        }
    }
    return false;
}

/**
 * The overridden toString method gets the root and the first inflectional group as a result {@link String} then concatenates
 * with ^DB+ and the following inflectional groups.
 *
 * @return result {@link String}.
 */
string MorphologicalParse::to_String() {
    string result = root->getName() + "+" + inflectionalGroups.at(0).to_String();
    for (int i = 1; i < inflectionalGroups.size(); i++)
        result = result + "^DB+" + inflectionalGroups.at(i).to_String();
    return result;
}
