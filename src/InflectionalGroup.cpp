//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#include "InflectionalGroup.h"

const string InflectionalGroup::tags[TAG_SIZE] = {"Noun", "Adv", "Adj", "Verb", "A1sg",
                                                  "A2sg", "A3sg", "A1Pl", "A2pl", "A3pl",
                                                  "P1sg", "P2sg", "P3sg", "P1Pl", "P2pl",
                                                  "P3pl", "Prop", "Pnon", "Nom", "With",
                                                  "Without", "Acc", "Dat", "Gen", "Abl",
                                                  "Zero", "Able", "Neg", "Past",
                                                  "Conj", "Det", "Dup", "Interj", "Num",
                                                  "PostP", "Punc", "Ques", "Agt", "ByDoingSo",
                                                  "Card", "Caus", "DemonsP", "Distrib", "FitFor",
                                                  "FutPart", "Inf", "Ness", "Ord", "Pass",
                                                  "PastPart", "PresPart", "QuesP", "QuantP", "Range",
                                                  "Ratio", "Real", "Recip", "Reflex", "ReflexP",
                                                  "Time", "When", "While", "WithoutHavingDoneSo", "PCAbl",
                                                  "PCAcc", "PCDat", "PCGen", "PCIns", "PCNom",
                                                  "Acquire", "ActOf", "AfterDoingSo", "Almost", "As",
                                                  "AsIf", "Become", "EverSince", "FeelLike", "Hastily",
                                                  "InBetween", "JustLike", "Ly", "NotAbleState", "Related",
                                                  "Repeat", "Since", "SinceDoingSo", "Start", "Stay",
                                                  "Equ", "Ins", "Aor", "Desr", "Fut",
                                                  "Imp", "Narr", "Neces", "Opt", "Past",
                                                  "Pres", "Prog1", "Prog2", "Cond", "Cop",
                                                  "Pos", "Pron", "Loc", "Rel", "Demons",
                                                  "Inf2", "Inf3", "BSTag", "ESTag", "BTTag",
                                                  "ETTag", "BDTag", "EDTag", "Inf1", "AsLongAs",
                                                  "Dist", "Adamantly", "Percent", "WithoutBeingAbleToHaveDoneSo", "Dim",
                                                  "Pers", "Fraction", "Hashtag", "Email", "Date", "Code", "Metric"};

const MorphologicalTag InflectionalGroup::morphoTags[TAG_SIZE] = {MorphologicalTag::NOUN, MorphologicalTag::ADVERB, MorphologicalTag::ADJECTIVE,
                                                                  MorphologicalTag::VERB, MorphologicalTag::A1SG, MorphologicalTag::A2SG, MorphologicalTag::A3SG, MorphologicalTag::A1PL,
                                                                  MorphologicalTag::A2PL, MorphologicalTag::A3PL, MorphologicalTag::P1SG, MorphologicalTag::P2SG, MorphologicalTag::P3SG, MorphologicalTag::P1PL,
                                                                  MorphologicalTag::P2PL, MorphologicalTag::P3PL, MorphologicalTag::PROPERNOUN, MorphologicalTag::PNON, MorphologicalTag::NOMINATIVE,
                                                                  MorphologicalTag::WITH, MorphologicalTag::WITHOUT, MorphologicalTag::ACCUSATIVE, MorphologicalTag::DATIVE, MorphologicalTag::GENITIVE,
                                                                  MorphologicalTag::ABLATIVE, MorphologicalTag::ZERO, MorphologicalTag::ABLE, MorphologicalTag::NEGATIVE, MorphologicalTag::PASTTENSE,
                                                                  MorphologicalTag::CONJUNCTION, MorphologicalTag::DETERMINER, MorphologicalTag::DUPLICATION, MorphologicalTag::INTERJECTION, MorphologicalTag::NUMBER,
                                                                  MorphologicalTag::POSTPOSITION, MorphologicalTag::PUNCTUATION, MorphologicalTag::QUESTION, MorphologicalTag::AGENT, MorphologicalTag::BYDOINGSO,
                                                                  MorphologicalTag::CARDINAL, MorphologicalTag::CAUSATIVE, MorphologicalTag::DEMONSTRATIVEPRONOUN, MorphologicalTag::DISTRIBUTIVE, MorphologicalTag::FITFOR,
                                                                  MorphologicalTag::FUTUREPARTICIPLE, MorphologicalTag::INFINITIVE, MorphologicalTag::NESS, MorphologicalTag::ORDINAL, MorphologicalTag::PASSIVE,
                                                                  MorphologicalTag::PASTPARTICIPLE, MorphologicalTag::PRESENTPARTICIPLE, MorphologicalTag::QUESTIONPRONOUN, MorphologicalTag::QUANTITATIVEPRONOUN, MorphologicalTag::RANGE,
                                                                  MorphologicalTag::RATIO, MorphologicalTag::REAL, MorphologicalTag::RECIPROCAL, MorphologicalTag::REFLEXIVE, MorphologicalTag::REFLEXIVEPRONOUN,
                                                                  MorphologicalTag::TIME, MorphologicalTag::WHEN, MorphologicalTag::WHILE, MorphologicalTag::WITHOUTHAVINGDONESO, MorphologicalTag::PCABLATIVE,
                                                                  MorphologicalTag::PCACCUSATIVE, MorphologicalTag::PCDATIVE, MorphologicalTag::PCGENITIVE, MorphologicalTag::PCINSTRUMENTAL, MorphologicalTag::PCNOMINATIVE,
                                                                  MorphologicalTag::ACQUIRE, MorphologicalTag::ACTOF, MorphologicalTag::AFTERDOINGSO, MorphologicalTag::ALMOST, MorphologicalTag::AS,
                                                                  MorphologicalTag::ASIF, MorphologicalTag::BECOME, MorphologicalTag::EVERSINCE, MorphologicalTag::FEELLIKE, MorphologicalTag::HASTILY,
                                                                  MorphologicalTag::INBETWEEN, MorphologicalTag::JUSTLIKE, MorphologicalTag::LY, MorphologicalTag::NOTABLESTATE, MorphologicalTag::RELATED,
                                                                  MorphologicalTag::REPEAT, MorphologicalTag::SINCE, MorphologicalTag::SINCEDOINGSO, MorphologicalTag::START, MorphologicalTag::STAY,
                                                                  MorphologicalTag::EQUATIVE, MorphologicalTag::INSTRUMENTAL, MorphologicalTag::AORIST, MorphologicalTag::DESIRE, MorphologicalTag::FUTURE,
                                                                  MorphologicalTag::IMPERATIVE, MorphologicalTag::NARRATIVE, MorphologicalTag::NECESSITY, MorphologicalTag::OPTATIVE, MorphologicalTag::PAST,
                                                                  MorphologicalTag::PRESENT, MorphologicalTag::PROGRESSIVE1, MorphologicalTag::PROGRESSIVE2, MorphologicalTag::CONDITIONAL, MorphologicalTag::COPULA,
                                                                  MorphologicalTag::POSITIVE, MorphologicalTag::PRONOUN, MorphologicalTag::LOCATIVE, MorphologicalTag::RELATIVE, MorphologicalTag::DEMONSTRATIVE,
                                                                  MorphologicalTag::INFINITIVE2, MorphologicalTag::INFINITIVE3, MorphologicalTag::BEGINNINGOFSENTENCE, MorphologicalTag::ENDOFSENTENCE, MorphologicalTag::BEGINNINGOFTITLE,
                                                                  MorphologicalTag::ENDOFTITLE, MorphologicalTag::BEGINNINGOFDOCUMENT, MorphologicalTag::ENDOFDOCUMENT, MorphologicalTag::INFINITIVE, MorphologicalTag::ASLONGAS,
                                                                  MorphologicalTag::DISTRIBUTIVE, MorphologicalTag::ADAMANTLY, MorphologicalTag::PERCENT, MorphologicalTag::WITHOUTBEINGABLETOHAVEDONESO, MorphologicalTag::DIMENSION,
                                                                  MorphologicalTag::PERSONALPRONOUN, MorphologicalTag::FRACTION, MorphologicalTag::HASHTAG, MorphologicalTag::EMAIL, MorphologicalTag::DATE,
                                                                  MorphologicalTag::CODE, MorphologicalTag::METRIC};

/**
 * The getMorphologicalTag method takes a String tag as an input and if the input matches with one of the elements of
 * tags array, it then gets the morphoTags of this tag and returns it.
 *
 * @param tag String to get morphoTags from.
 * @return morphoTags if found, null otherwise.
 */
MorphologicalTag InflectionalGroup::getMorphologicalTag(const string& tag) {
    string _tag = tag;
    transform(_tag.begin(),
              _tag.end(),
              _tag.begin(),
                   ::toupper);
    for (int j = 0; j < TAG_SIZE; j++) {
        string upperCase = tags[j];
        transform(upperCase.begin(),
                  upperCase.end(),
                  upperCase.begin(),
                       ::toupper);
        if (_tag == upperCase) {
            return morphoTags[j];
        }
    }
    return MorphologicalTag::NOTAG;
}

/**
 * The getTag method takes a MorphologicalTag type tag as an input and returns its corresponding tag from tags array.
 *
 * @param tag MorphologicalTag type input to find tag from.
 * @return tag if found, null otherwise.
 */
string InflectionalGroup::getTag(MorphologicalTag tag) {
    for (int j = 0; j < TAG_SIZE; j++) {
        if (tag == morphoTags[j]) {
            string result = tags[j];
            transform(result.begin(),
                      result.end(),
                      result.begin(),
                      ::toupper);
            return result;
        }
    }
    return "";
}

/**
 * A constructor of {@link InflectionalGroup} class which initializes the IG {@link vector} by parsing given input
 * String IG by + and calling the getMorphologicalTag method with these substrings. If getMorphologicalTag method returns
 * a tag, it adds this tag to the IG {@link vector}.
 *
 * @param IG String input.
 */
InflectionalGroup::InflectionalGroup(const string& IG) {
    MorphologicalTag tag;
    string morphologicalTag;
    string st = IG;
    while (st.find_first_of('+') != -1) {
        morphologicalTag = st.substr(0, st.find_first_of('+'));
        tag = getMorphologicalTag(morphologicalTag);
        this->IG.emplace_back(tag);
        st = st.substr(st.find_first_of('+') + 1);
    }
    morphologicalTag = st;
    tag = getMorphologicalTag(morphologicalTag);
    this->IG.emplace_back(tag);
}

/**
 * Another getTag method which takes index as an input and returns the corresponding tag from IG {@link vector}.
 *
 * @param index to get tag.
 * @return tag at input index.
 */
MorphologicalTag InflectionalGroup::getTag(int index) const{
    return IG.at(index);
}

/**
 * The size method returns the size of the G {@link vector}.
 *
 * @return the size of the G {@link vector}.
 */
int InflectionalGroup::size() const{
    return IG.size();
}

/**
 * Overridden toString method to return resulting tags in IG {@link vector}.
 *
 * @return String result.
 */
string InflectionalGroup::to_String() const{
    string result = getTag(IG.at(0));
    for (int i = 1; i < IG.size(); i++) {
        result += "+" + getTag(IG.at(i));
    }
    return result;
}

/**
 * The containsCase method loops through the tags in IG {@link ArrayList} and finds out the tags of the NOMINATIVE,
 * ACCUSATIVE, DATIVE, LOCATIVE or ABLATIVE cases.
 *
 * @return tag which holds the condition.
 */
MorphologicalTag InflectionalGroup::containsCase() const{
    for (MorphologicalTag tag : IG) {
        if (tag == MorphologicalTag::NOMINATIVE || tag == MorphologicalTag::ACCUSATIVE || tag == MorphologicalTag::DATIVE || tag == MorphologicalTag::LOCATIVE || tag == MorphologicalTag::ABLATIVE) {
            return tag;
        }
    }
    return MorphologicalTag::NOTAG;
}

/**
 * The containsPlural method loops through the tags in IG {@link vector} and checks whether the tags are from
 * the agreement plural or possessive plural, i.e A1PL, A2PL, A3PL, P1PL, P2PL and P3PL.
 *
 * @return true if the tag is plural, false otherwise.
 */
bool InflectionalGroup::containsPlural() const{
    for (MorphologicalTag tag : IG) {
        if (tag == MorphologicalTag::A1PL || tag == MorphologicalTag::A2PL || tag == MorphologicalTag::A3PL || tag == MorphologicalTag::P1PL || tag == MorphologicalTag::P2PL || tag == MorphologicalTag::P3PL) {
            return true;
        }
    }
    return false;
}

/**
 * The containsTag method takes a MorphologicalTag type tag as an input and loops through the tags in
 * IG {@link vector} and returns true if the input matches with on of the tags in the IG.
 *
 * @param tag MorphologicalTag type input to search for.
 * @return true if tag matches with the tag in IG, false otherwise.
 */
bool InflectionalGroup::containsTag(MorphologicalTag tag) const{
    for (MorphologicalTag currentTag : IG) {
        if (currentTag == tag) {
            return true;
        }
    }
    return false;
}

/**
 * The containsPossessive method loops through the tags in IG {@link ArrayList} and returns true if the tag in IG is
 * one of the possessives: P1PL, P1SG, P2PL, P2SG, P3PL AND P3SG.
 *
 * @return true if it contains possessive tag, false otherwise.
 */
bool InflectionalGroup::containsPossessive() const{
    for (MorphologicalTag tag : IG) {
        if (tag == MorphologicalTag::P1PL || tag == MorphologicalTag::P1SG || tag == MorphologicalTag::P2PL || tag == MorphologicalTag::P2SG || tag == MorphologicalTag::P3PL || tag == MorphologicalTag::P3SG) {
            return true;
        }
    }
    return false;
}
