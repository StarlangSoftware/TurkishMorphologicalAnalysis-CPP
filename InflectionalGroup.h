//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
#define MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H

#include <vector>
#include <string>
#include "MorphologicalTag.h"

using namespace std;

class InflectionalGroup {
private:
    vector<MorphologicalTag> IG;
    static const int TAG_SIZE = 129;
    static const string tags[TAG_SIZE];
    static const MorphologicalTag morphoTags[TAG_SIZE];
public:
    static MorphologicalTag getMorphologicalTag(string tag);
    static string getTag(MorphologicalTag tag);
    explicit InflectionalGroup(string IG);
    MorphologicalTag getTag(int index);
    int size();
    string to_String();
    MorphologicalTag containsCase();
    bool containsPlural();
    bool containsTag(MorphologicalTag tag);
    bool containsPossessive();
};

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
                                                  "Pers", "Fraction", "Hashtag", "Email", "Date"};

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
                                                                  MorphologicalTag::PERSONALPRONOUN, MorphologicalTag::FRACTION, MorphologicalTag::HASHTAG, MorphologicalTag::EMAIL, MorphologicalTag::DATE};

#endif //MORPHOLOGICALANALYSIS_INFLECTIONALGROUP_H
