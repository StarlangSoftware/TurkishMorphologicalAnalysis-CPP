//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#include "FsmParse.h"

#include <utility>
#include "Dictionary/TxtWord.h"
#include "Transition.h"

using namespace std;
/**
 * A constructor of FsmParse class which takes a Word as an input and assigns it to root variable.
 *
 * @param root Word input.
 */
FsmParse::FsmParse(Word* root){
    this->root = root;
}

/**
 * Another constructor of FsmParse class which takes an Integer number and a State as inputs.
 * First, it creates a TxtWord with given number and adds flag to this number as IS_SAYI and initializes root variable with
 * number TxtWord. It also initializes form with root's name, pos and initialPos with given State's POS, creates 4 new
 * ArrayList suffixList, formList, transitionList and withList and adds given State to suffixList, form to
 * formList.
 *
 * @param number     Integer input.
 * @param startState State input.
 */
FsmParse::FsmParse(int number, const State& startState) {
    auto* num = new TxtWord(std::to_string(number));
    num->addFlag("IS_SAYI");
    this->root = num;
    this->form = root->getName();
    this->pos = startState.getPos();
    this->initialPos = startState.getPos();
    suffixList.emplace_back(startState);
    formList.emplace_back(this->form);
}

/**
 * Another constructor of FsmParse class which takes a Double number and a State as inputs.
 * First, it creates a TxtWord with given number and adds flag to this number as IS_SAYI and initializes root variable with
 * number TxtWord. It also initializes form with root's name, pos and initialPos with given State's POS, creates 4 new
 * ArrayList suffixList, formList, transitionList and withList and adds given State to suffixList, form to
 * formList.
 *
 * @param number     Double input.
 * @param startState State input.
 */
FsmParse::FsmParse(double number, const string& stringValue, const State& startState) {
    auto* num = new TxtWord(stringValue);
    num->addFlag("IS_SAYI");
    this->root = num;
    this->form = root->getName();
    this->pos = startState.getPos();
    this->initialPos = startState.getPos();
    suffixList.emplace_back(startState);
    formList.emplace_back(this->form);
}

/**
 * Another constructor of FsmParse class which takes a String punctuation and a State as inputs.
 * First, it creates a TxtWord with given punctuation and initializes root variable with this TxtWord.
 * It also initializes form with root's name, pos and initialPos with given State's POS, creates 4 new
 * ArrayList suffixList, formList, transitionList and withList and adds given State to suffixList, form to
 * formList.
 *
 * @param punctuation String input.
 * @param startState  State input.
 */
FsmParse::FsmParse(const string& punctuation, const State& startState) {
    this->root = new TxtWord(punctuation);
    this->form = root->getName();
    this->pos = startState.getPos();
    this->initialPos = startState.getPos();
    suffixList.emplace_back(startState);
    formList.emplace_back(this->form);
}

/**
 * Another constructor of FsmParse class which takes a TxtWord root and a State as inputs.
 * First, initializes root variable with this TxtWord. It also initializes form with root's name, pos and
 * initialPos with given State's POS, creates 4 new ArrayList suffixList, formList, transitionList
 * and withList and adds given State to suffixList, form to formList.
 *
 * @param root       TxtWord input.
 * @param startState State input.
 */
FsmParse::FsmParse(TxtWord *root, const State& startState) {
    this->root = root;
    this->form = root->getName();
    this->pos = startState.getPos();
    this->initialPos = startState.getPos();
    suffixList.emplace_back(startState);
    formList.emplace_back(this->form);
}

/**
 * The constructInflectionalGroups method initially calls the transitionList method and assigns the resulting String
 * to the parse variable and creates a new ArrayList as iGs. If parse String contains a derivational boundary
 * it adds the substring starting from the 0 to the index of derivational boundary to the iGs. If it does not contain a DB,
 * it directly adds parse to the iGs. Then, creates and initializes new ArrayList as inflectionalGroups and fills with
 * the items of iGs.
 */
void FsmParse::constructInflectionalGroups() {
    string parse = transitionlist();
    int i;
    vector<string> iGs;
    while (parse.find("^DB+") != string::npos) {
        iGs.emplace_back(parse.substr(0, parse.find("^DB+")));
        parse = parse.substr(parse.find("^DB+") + 4, parse.size());
    }
    iGs.emplace_back(parse);
    inflectionalGroups.emplace_back(InflectionalGroup(iGs.at(0).substr(iGs.at(0).find('+') + 1)));
    for (i = 1; i < iGs.size(); i++) {
        inflectionalGroups.emplace_back(InflectionalGroup(iGs.at(i)));
    }
}

/**
 * Getter for the verbAgreement variable.
 *
 * @return the verbAgreement variable.
 */
string FsmParse::getVerbAgreement() const{
    return verbAgreement;
}

/**
 * Getter for the getPossesiveAgreement variable.
 *
 * @return the possesiveAgreement variable.
 */
string FsmParse::getPossesiveAgreement() const{
    return possesiveAgreement;
}

/**
 * The setAgreement method takes a String transitionName as an input and if it is one of the A1SG, A2SG, A3SG,
 * A1PL, A2PL or A3PL it assigns transitionName input to the verbAgreement variable. Or if it is ine of the PNON, P1SG, P2SG,P3SG,
 * P1PL, P2PL or P3PL it assigns transitionName input to the possesiveAgreement variable.
 *
 * @param transitionName String input.
 */
void FsmParse::setAgreement(const string& transitionName) {
    if (!transitionName.empty() && (transitionName == "A1SG" || transitionName == "A2SG" || transitionName == "A3SG" || transitionName == "A1PL" || transitionName == "A2PL" || transitionName == "A3PL")) {
        this->verbAgreement = transitionName;
    }
    if (!transitionName.empty() && (transitionName == "PNON" || transitionName == "P1SG" || transitionName == "P2SG" || transitionName == "P3SG" || transitionName == "P1PL" || transitionName == "P2PL" || transitionName == "P3PL")) {
        this->possesiveAgreement = transitionName;
    }
}

/**
 * The getLastLemmaWithTag method takes a String input _pos as an input. If given _pos is an initial _pos then it assigns
 * root to the lemma, and assign null otherwise.  Then, it loops i times where i ranges from 1 to size of the formList,
 * if the item at i-1 of transitionList is not null and contains a derivational boundary with _pos but not with ZERO,
 * it assigns the ith item of formList to lemma.
 *
 * @param _pos String input.
 * @return String output lemma.
 */
string FsmParse::getLastLemmaWithTag(const string& _pos) const{
    string lemma;
    if (!initialPos.empty() && initialPos == _pos) {
        lemma = root->getName();
    } else {
        lemma = "";
    }
    for (int i = 1; i < formList.size(); i++) {
        if (!transitionList.at(i - 1).empty() && transitionList.at(i - 1).find("^DB+" + _pos) != string::npos && transitionList.at(i - 1).find("^DB+" + _pos + "+ZERO") == string::npos) {
            lemma = formList.at(i);
        }
    }
    return lemma;
}

/**
 * The getLastLemma method initially assigns root as lemma. Then, it loops i times where i ranges from 1 to size of the formList,
 * if the item at i-1 of transitionList is not null and contains a derivational boundary, it assigns the ith item of formList to lemma.
 *
 * @return String output lemma.
 */
string FsmParse::getLastLemma() const{
    string lemma = root->getName();
    for (int i = 1; i < formList.size(); i++) {
        if (!transitionList.at(i - 1).empty() && transitionList.at(i - 1).find("^DB+") != string::npos) {
            lemma = formList.at(i);
        }
    }
    return lemma;
}

/**
 * The addSuffix method takes 5 different inputs; State suffix, String _form, transition, with and toPos.
 * If the pos of given input suffix is not null, it then assigns it to the pos variable. If the pos of the given suffix
 * is null but given toPos is not null than it assigns toPos to pos variable. At the end, it adds suffix to the suffixList,
 * _form to the formList, transition to the transitionList and if given with is not 0, it is also added to withList.
 *
 * @param suffix     State input.
 * @param _form       String input.
 * @param transition String input.
 * @param with       String input.
 * @param toPos      String input.
 */
void FsmParse::addSuffix(const State& suffix, const string& _form, const string& transition, const string& with, const string& toPos) {
    if (!suffix.getPos().empty()) {
        pos = suffix.getPos();
    } else {
        if (!toPos.empty()) {
            pos = toPos;
        }
    }
    suffixList.emplace_back(suffix);
    formList.emplace_back(_form);
    transitionList.emplace_back(transition);
    if (with != "0") {
        withList.emplace_back(with);
    }
    this->form = _form;
}

/**
 * Getter for the form variable.
 *
 * @return the form variable.
 */
string FsmParse::getSurfaceForm() const{
    return form;
}

/**
 * The getStartState method returns the first item of suffixList ArrayList.
 *
 * @return the first item of suffixList ArrayList.
 */
State FsmParse::getStartState() const{
    return suffixList.at(0);
}

/**
 * Getter for the pos variable.
 *
 * @return the pos variable.
 */
string FsmParse::getFinalPos() const{
    return pos;
}

/**
 * Getter for the initialPos variable.
 *
 * @return the initialPos variable.
 */
string FsmParse::getInitialPos() const{
    return initialPos;
}

/**
 * The setForm method takes a String name as an input and assigns it to the form variable, then it removes the first item
 * of formList ArrayList and adds the given name to the formList.
 *
 * @param name String input to set form.
 */
void FsmParse::setForm(const string& name) {
    form = name;
    formList.erase(formList.begin());
    formList.emplace_back(name);
}

/**
 * The getFinalSuffix method returns the last item of suffixList ArrayList.
 *
 * @return the last item of suffixList ArrayList.
 */
State FsmParse::getFinalSuffix() const{
    return suffixList.at(suffixList.size() - 1);
}

/**
 * The overridden clone method creates a new FsmParse abject with root variable and initializes variables form, pos,
 * initialPos, verbAgreement, possesiveAgreement, and also the vectors suffixList, formList, transitionList and withList.
 * Then returns newly created and cloned FsmParse object.
 *
 * @return FsmParse object.
 */
FsmParse FsmParse::clone() const{
    FsmParse p = FsmParse(root);
    p.form = form;
    p.pos = pos;
    p.initialPos = initialPos;
    p.verbAgreement = verbAgreement;
    p.possesiveAgreement = possesiveAgreement;
    p.suffixList = suffixList;
    p.formList = formList;
    p.transitionList = transitionList;
    p.withList = withList;
    return p;
}

/**
 * The headerTransition method gets the first item of formList and checks for cases;
 * <p>
 * If it is &lt;DOC&gt;, it returns &lt;DOC&gt;+BDTAG which indicates the beginning of a document.
 * If it is &lt;/DOC&gt;, it returns &lt;/DOC&gt;+EDTAG which indicates the ending of a document.
 * If it is &lt;TITLE&gt;, it returns &lt;TITLE&gt;+BTTAG which indicates the beginning of a title.
 * If it is &lt;/TITLE&gt;, it returns &lt;/TITLE&gt;+ETTAG which indicates the ending of a title.
 * If it is &lt;S&gt;, it returns &lt;S&gt;+BSTAG which indicates the beginning of a sentence.
 * If it is &lt;/S&gt;, it returns &lt;/S&gt;+ESTAG which indicates the ending of a sentence.
 *
 * @return corresponding tags of the headers and an empty String if any case does not match.
 */
string FsmParse::headerTransition() const{
    if (formList.at(0) == "<DOC>") {
        return "<DOC>+BDTAG";
    }
    if (formList.at(0) == "</DOC>") {
        return "</DOC>+EDTAG";
    }
    if (formList.at(0) == "<TITLE>") {
        return "<TITLE>+BTTAG";
    }
    if (formList.at(0) == "</TITLE>") {
        return "</TITLE>+ETTAG";
    }
    if (formList.at(0) == "<S>") {
        return "<S>+BSTAG";
    }
    if (formList.at(0) == "</S>") {
        return "</S>+ESTAG";
    }
    return "";
}

/**
 * The pronounTransition method gets the first item of formList and checks for cases;
 * <p>
 * If it is "kendi", it returns kendi+PRON+REFLEXP which indicates a reflexive pronoun.
 * If it is one of the "hep, öbür, kimse, hiçbiri, tümü, çoğu, hepsi, biri, birbirleri, birbiri, bazı, kimi", it returns
 * +PRON+QUANTP which indicates a quantitative pronoun.
 * If it is one of the "o, bu, şu" and if it is "o" it also checks the first item of suffixList and if it is a PronounRoot(DEMONS),
 * it returns +PRON+DEMONSP which indicates a demonstrative pronoun.
 * If it is "ben", it returns +PRON+PERS+A1SG+PNON which indicates a 1st person singular agreement.
 * If it is "sen", it returns +PRON+PERS+A2SG+PNON which indicates a 2nd person singular agreement.
 * If it is "o" and the first item of suffixList, if it is a PronounRoot(PERS), it returns +PRON+PERS+A3SG+PNON which
 * indicates a 3rd person singular agreement.
 * If it is "biz", it returns +PRON+PERS+A1PL+PNON which indicates a 1st person plural agreement.
 * If it is "siz", it returns +PRON+PERS+A2PL+PNON which indicates a 2nd person plural agreement.
 * If it is "onlar" and the first item of suffixList, if it is a PronounRoot(PERS), it returns o+PRON+PERS+A3PL+PNON which
 * indicates a 3rd person plural agreement.
 * If it is one of the "nere, ne, kim, hangi", it returns +PRON+QUESP which indicates a question pronoun.
 *
 * @return corresponding transitions of pronouns and an empty String if any case does not match.
 */
string FsmParse::pronounTransition() const{
    if (formList.at(0) == "kendi") {
        return "kendi+PRON+REFLEXP";
    }
    if (formList.at(0) == "hep" || formList.at(0) == "öbür" || formList.at(0) == "topu" || formList.at(0) == "öteki" || formList.at(0) == "kimse" || formList.at(0) == "hiçbiri" || formList.at(0) == "tümü" || formList.at(0) == "çoğu" || formList.at(0) == "hepsi" || formList.at(0) == "herkes" || formList.at(0) == "başkası" || formList.at(0) == "birçoğu" || formList.at(0) == "birçokları" || formList.at(0) == "birbiri" || formList.at(0) == "birbirleri" || formList.at(0) == "biri" || formList.at(0) == "birkaçı" || formList.at(0) == "böylesi" || formList.at(0) == "diğeri" || formList.at(0) == "cümlesi" || formList.at(0) == "bazı" || formList.at(0) == "kimi") {
        return formList.at(0) + "+PRON+QUANTP";
    }
    if ((formList.at(0) == "o" && suffixList.at(0).getName() == "PronounRoot(DEMONS)") || formList.at(0) == "bu" || formList.at(0) == "şu") {
        return formList.at(0) + "+PRON+DEMONSP";
    }
    if (formList.at(0) == "ben") {
        return formList.at(0) + "+PRON+PERS+A1SG+PNON";
    }
    if (formList.at(0) == "sen") {
        return formList.at(0) + "+PRON+PERS+A2SG+PNON";
    }
    if (formList.at(0) == "o" && suffixList.at(0).getName() == "PronounRoot(PERS)") {
        return formList.at(0) + "+PRON+PERS+A3SG+PNON";
    }
    if (formList.at(0) == "biz") {
        return formList.at(0) + "+PRON+PERS+A1PL+PNON";
    }
    if (formList.at(0) == "siz") {
        return formList.at(0) + "+PRON+PERS+A2PL+PNON";
    }
    if (formList.at(0) == "onlar") {
        return "o+PRON+PERS+A3PL+PNON";
    }
    if (formList.at(0) == "nere" || formList.at(0) == "ne" || formList.at(0) == "kaçı" || formList.at(0) == "kim" || formList.at(0) == "hangi") {
        return formList.at(0) + "+PRON+QUESP";
    }
    return "";
}

/**
 * The getTransitionList method first creates an empty String result, then gets the first item of suffixList and checks for cases;
 * <p>
 * If it is one of the "NominalRoot, NominalRootNoPossesive, CompoundNounRoot, NominalRootPlural", it assigns concatenation of first
 * item of formList and +NOUN to the result String.
 * Ex : Birincilik
 * <p>
 * If it is one of the "VerbalRoot, PassiveHn", it assigns concatenation of first item of formList and +VERB to the result String.
 * Ex : Başkalaştı
 * <p>
 * If it is "CardinalRoot", it assigns concatenation of first item of formList and +NUM+CARD to the result String.
 * Ex : Onuncu
 * <p>
 * If it is "FractionRoot", it assigns concatenation of first item of formList and NUM+FRACTION to the result String.
 * Ex : 1/2
 * <p>
 * If it is "TimeRoot", it assigns concatenation of first item of formList and +TIME to the result String.
 * Ex : 14:28
 * <p>
 * If it is "RealRoot", it assigns concatenation of first item of formList and +NUM+REAL to the result String.
 * Ex : 1.2
 * <p>
 * If it is "Punctuation", it assigns concatenation of first item of formList and +PUNC to the result String.
 * Ex : ,
 * <p>
 * If it is "Hashtag", it assigns concatenation of first item of formList and +HASHTAG to the result String.
 * Ex : #
 * <p>
 * If it is "DateRoot", it assigns concatenation of first item of formList and +DATE to the result String.
 * Ex : 11/06/2018
 * <p>
 * If it is "RangeRoot", it assigns concatenation of first item of formList and +RANGE to the result String.
 * Ex : 3-5
 * <p>
 * If it is "Email", it assigns concatenation of first item of formList and +EMAIL to the result String.
 * Ex : abc@
 * <p>
 * If it is "PercentRoot", it assigns concatenation of first item of formList and +PERCENT to the result String.
 * Ex : %12.5
 * <p>
 * If it is "DeterminerRoot", it assigns concatenation of first item of formList and +DET to the result String.
 * Ex : Birtakım
 * <p>
 * If it is "ConjunctionRoot", it assigns concatenation of first item of formList and +CONJ to the result String.
 * Ex : Ama
 * <p>
 * If it is "AdverbRoot", it assigns concatenation of first item of formList and +ADV to the result String.
 * Ex : Acilen
 * <p>
 * If it is "ProperRoot", it assigns concatenation of first item of formList and +NOUN+PROP to the result String.
 * Ex : Ahmet
 * <p>
 * If it is "HeaderRoot", it assigns the result of the headerTransition method to the result String.
 * Ex : &lt;DOC&gt;
 * <p>
 * If it is "InterjectionRoot", it assigns concatenation of first item of formList and +INTERJ to the result String.
 * Ex : Hey
 * <p>
 * If it is "DuplicateRoot", it assigns concatenation of first item of formList and +DUP to the result String.
 * Ex : Allak
 * <p>
 * If it is "CodeRoot", it assigns concatenation of first item of formList and +CODE to the result String.
 * Ex : 5000-WX
 * <p>
 * If it is "MetricRoot", it assigns concatenation of first item of formList and +METRIC to the result String.
 * Ex : 6cmx12cm
 * <p>
 * If it is "QuestionRoot", it assigns concatenation of first item of formList and +QUES to the result String.
 * Ex : Mı
 * <p>
 * If it is "PostP", and the first item of formList is one of the "karşı, ilişkin, göre, kadar, ait, yönelik, rağmen, değin,
 * dek, doğru, karşın, dair, atfen, binaen, hitaben, istinaden, mahsuben, mukabil, nazaran", it assigns concatenation of first
 * item of formList and +POSTP+PCDAT to the result String.
 * Ex : İlişkin
 * <p>
 * If it is "PostP", and the first item of formList is one of the "sonra, önce, beri, fazla, dolayı, itibaren, başka,
 * çok, evvel, ötürü, yana, öte, aşağı, yukarı, dışarı, az, gayrı", it assigns concatenation of first
 * item of formList and +POSTP+PCABL to the result String.
 * Ex : Başka
 * <p>
 * If it is "PostP", and the first item of formList is "yanısıra", it assigns concatenation of first
 * item of formList and +POSTP+PCGEN to the result String.
 * Ex : Yanısıra
 * <p>
 * If it is "PostP", and the first item of formList is one of the "birlikte, beraber", it assigns concatenation of first
 * item of formList and +PPOSTP+PCINS to the result String.
 * Ex : Birlikte
 * <p>
 * If it is "PostP", and the first item of formList is one of the "aşkın, takiben", it assigns concatenation of first
 * item of formList and +POSTP+PCACC to the result String.
 * Ex : Takiben
 * <p>
 * If it is "PostP", it assigns concatenation of first item of formList and +POSTP+PCNOM to the result String.
 * <p>
 * If it is "PronounRoot", it assigns result of the pronounTransition method to the result String.
 * Ex : Ben
 * <p>
 * If it is "OrdinalRoot", it assigns concatenation of first item of formList and +NUM+ORD to the result String.
 * Ex : Altıncı
 * <p>
 * If it starts with "Adjective", it assigns concatenation of first item of formList and +ADJ to the result String.
 * Ex : Güzel
 * <p>
 * At the end, it loops through the formList and concatenates each item with result String.
 *
 * @return String result accumulated with items of formList.
 */
string FsmParse::transitionlist() const{
    string result;
    if (suffixList.at(0).getName() == "NominalRoot" || suffixList.at(0).getName() == "NominalRootNoPossesive" || suffixList.at(0).getName() == "CompoundNounRoot" || suffixList.at(0).getName() == "NominalRootPlural") {
        result = formList.at(0) + "+NOUN";
    } else {
        if (Word::startsWith(suffixList.at(0).getName(), "VerbalRoot") || suffixList.at(0).getName() == "PassiveHn") {
            result = formList.at(0) + "+VERB";
        } else {
            if (suffixList.at(0).getName() == "CardinalRoot") {
                result = formList.at(0) + "+NUM+CARD";
            } else {
                if (suffixList.at(0).getName() == "FractionRoot") {
                    result = formList.at(0) + "+NUM+FRACTION";
                } else {
                    if (suffixList.at(0).getName() == "TimeRoot") {
                        result = formList.at(0) + "+TIME";
                    } else {
                        if (suffixList.at(0).getName() == "RealRoot") {
                            result = formList.at(0) + "+NUM+REAL";
                        } else {
                            if (suffixList.at(0).getName() == "Punctuation") {
                                result = formList.at(0) + "+PUNC";
                            } else {
                                if (suffixList.at(0).getName() == "Hashtag") {
                                    result = formList.at(0) + "+HASHTAG";
                                } else {
                                    if (suffixList.at(0).getName() == "DateRoot") {
                                        result = formList.at(0) + "+DATE";
                                    } else {
                                        if (suffixList.at(0).getName() == "RangeRoot") {
                                            result = formList.at(0) + "+RANGE";
                                        } else {
                                            if (suffixList.at(0).getName() == "Email") {
                                                result = formList.at(0) + "+EMAIL";
                                            } else {
                                                if (suffixList.at(0).getName() == "PercentRoot") {
                                                    result = formList.at(0) + "+PERCENT";
                                                } else {
                                                    if (suffixList.at(0).getName() == "DeterminerRoot") {
                                                        result = formList.at(0) + "+DET";
                                                    } else {
                                                        if (suffixList.at(0).getName() == "ConjunctionRoot") {
                                                            result = formList.at(0) + "+CONJ";
                                                        } else {
                                                            if (suffixList.at(0).getName() == "AdverbRoot") {
                                                                result = formList.at(0) + "+ADV";
                                                            } else {
                                                                if (suffixList.at(0).getName() == "ProperRoot") {
                                                                    result = formList.at(0) + "+NOUN+PROP";
                                                                } else {
                                                                    if (suffixList.at(0).getName() == "HeaderRoot") {
                                                                        result = headerTransition();
                                                                    } else {
                                                                        if (suffixList.at(0).getName() == "InterjectionRoot") {
                                                                            result = formList.at(0) + "+INTERJ";
                                                                        } else {
                                                                            if (suffixList.at(0).getName() == "DuplicateRoot") {
                                                                                result = formList.at(0) + "+DUP";
                                                                            } else {
                                                                                if (suffixList.at(0).getName() == "CodeRoot"){
                                                                                    result = formList.at(0) + "CODE";
                                                                                } else {
                                                                                    if (suffixList.at(0).getName() == "MetricRoot"){
                                                                                        result = formList.at(0) + "METRIC";
                                                                                    } else {
                                                                                        if (suffixList.at(0).getName() == "QuestionRoot") {
                                                                                            result = "mi+QUES";
                                                                                        } else {
                                                                                            if (suffixList.at(0).getName() == "PostP") {
                                                                                                if (formList.at(0) == "karşı" || formList.at(0) == "ilişkin" || formList.at(0) == "göre" || formList.at(0) == "kadar" || formList.at(0) == "ait" || formList.at(0) == "yönelik" || formList.at(0) == "rağmen" || formList.at(0) == "değin" || formList.at(0) == "dek" || formList.at(0) == "doğru" || formList.at(0) == "karşın" || formList.at(0) == "dair" || formList.at(0) == "atfen" || formList.at(0) == "binaen" || formList.at(0) == "hitaben" || formList.at(0) == "istinaden" || formList.at(0) == "mahsuben" || formList.at(0) == "mukabil" || formList.at(0) == "nazaran") {
                                                                                                    result = formList.at(0) + "+POSTP+PCDAT";
                                                                                                } else {
                                                                                                    if (formList.at(0) == "sonra" || formList.at(0) == "önce" || formList.at(0) == "beri" || formList.at(0) == "fazla" || formList.at(0) == "dolayı" || formList.at(0) == "itibaren" || formList.at(0) == "başka" || formList.at(0) == "çok" || formList.at(0) == "evvel" || formList.at(0) == "ötürü" || formList.at(0) == "yana" || formList.at(0) == "öte" || formList.at(0) == "aşağı" || formList.at(0) == "yukarı" || formList.at(0) == "dışarı" || formList.at(0) == "az" || formList.at(0) == "gayrı") {
                                                                                                        result = formList.at(0) + "+POSTP+PCABL";
                                                                                                    } else {
                                                                                                        if (formList.at(0) == "yanısıra") {
                                                                                                            result = formList.at(0) + "+POSTP+PCGEN";
                                                                                                        } else {
                                                                                                            if (formList.at(0) == "birlikte" || formList.at(0) == "beraber") {
                                                                                                                result = formList.at(0) + "+POSTP+PCINS";
                                                                                                            } else {
                                                                                                                if (formList.at(0) == "aşkın" || formList.at(0) == "takiben") {
                                                                                                                    result = formList.at(0) + "+POSTP+PCACC";
                                                                                                                } else {
                                                                                                                    result = formList.at(0) + "+POSTP+PCNOM";
                                                                                                                }
                                                                                                            }
                                                                                                        }
                                                                                                    }
                                                                                                }
                                                                                            } else {
                                                                                                if (Word::startsWith(suffixList.at(0).getName(), "PronounRoot")) {
                                                                                                    result = pronounTransition();
                                                                                                } else {
                                                                                                    if (suffixList.at(0).getName() == "OrdinalRoot") {
                                                                                                        result = formList.at(0) + "+NUM+ORD";
                                                                                                    } else {
                                                                                                        if (Word::startsWith(suffixList.at(0).getName(), "Adjective")) {
                                                                                                            result = formList.at(0) + "+ADJ";
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
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (const string &transition : transitionList) {
        if (!transition.empty()) {
            if (!Word::startsWith(transition, "^")) {
                result.append("+");
                result.append(transition);
            } else {
                result.append(transition);
            }
        }
    }
    return result;
}

/**
 * The suffixList method gets the first items of suffixList and formList and concatenates them with parenthesis and
 * assigns a String result. Then, loops through the formList and it the current ith item is not equal to previous
 * item it accumulates ith items of formList and suffixList to the result String.
 *
 * @return result String accumulated with the items of formList and suffixList.
 */
string FsmParse::getSuffixList() const{
    string result = suffixList.at(0).getName() + '(' + formList.at(0) + ')';
    for (int i = 1; i < formList.size(); i++) {
        if (formList.at(i) != formList.at(i - 1)) {
            result += "+" + suffixList.at(i).getName() + '(' + formList.at(i) + ')';
        }
    }
    return result;
}

/**
 * The withList method gets the root as a result String then loops through the withList and concatenates each item
 * with result String.
 *
 * @return result String accumulated with items of withList.
 */
string FsmParse::getWithList() const{
    string result = root->getName();
    for (const string& aWith : withList) {
        result += "+" + aWith;
    }
    return result;
}

/**
 * Replace root word of the current parse with the new root word and returns the new word.
 * @param newRoot Replaced root word
 * @return Root word of the parse will be replaced with the newRoot and the resulting surface form is returned.
 */
string FsmParse::replaceRootWord(TxtWord* newRoot) const{
    string result = newRoot->getName();
    for (const string& aWith : withList){
        Transition transition = Transition(aWith);
        result = transition.makeTransition(newRoot, result);
    }
    return result;
}

/**
 * The overridden toString method which returns transitionList method.
 *
 * @return returns transitionList method.
 */
string FsmParse::to_String() const{
    return transitionlist();
}
