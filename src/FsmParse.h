//
// Created by Olcay Taner Yıldız on 25.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_FSMPARSE_H
#define MORPHOLOGICALANALYSIS_FSMPARSE_H

#include "Dictionary/TxtWord.h"
#include "MorphologicalParse.h"
#include "State.h"

class FsmParse : public MorphologicalParse {
private:
    vector<State> suffixList;
    vector<string> formList;
    vector<string> transitionList;
    vector<string> withList;
    string initialPos;
    string pos;
    string form;
    string verbAgreement = "";
    string possesiveAgreement = "";
public:
    explicit FsmParse(Word* root);
    FsmParse() = default;
    FsmParse(int number, const State& startState);
    FsmParse(double number, const string& stringValue, const State& startState);
    FsmParse(const string& punctuation, const State& startState);
    FsmParse(TxtWord* root, const State& startState);
    void constructInflectionalGroups();
    string getVerbAgreement() const;
    string getPossesiveAgreement() const;
    void setAgreement(const string& transitionName);
    string getLastLemmaWithTag(const string& pos) const;
    string getLastLemma() const;
    void addSuffix(const State& suffix, const string& _form, const string& transition, const string& with, const string& toPos);
    string getSurfaceForm() const;
    State getStartState() const;
    string getFinalPos() const;
    string getInitialPos() const;
    void setForm(const string& name);
    State getFinalSuffix() const;
    FsmParse clone() const;
    string headerTransition() const;
    string pronounTransition() const;
    string transitionlist() const;
    string getSuffixList() const;
    string getWithList() const;
    string replaceRootWord(TxtWord* newRoot) const;
    string to_String() const;
/**
 * The overridden compareTo metgod takes an {@link Object} as an input and if it is an instance of the {@link FsmParse}
 * class it returns the result of comparison of the items of transitionList with input {@link Object}.
 *
 * @param o {@link Object} input to compare.
 * @return comparison of the items of transitionList with input {@link Object}, and returns 0 if input is not an
 * instance of {@link FsmParse} class.
 */
    bool operator==(FsmParse &fsmParse){
        return (to_String() == fsmParse.to_String());
    }
    bool operator<(FsmParse &fsmParse){
        return (to_String() < fsmParse.to_String());
    }
};


#endif //MORPHOLOGICALANALYSIS_FSMPARSE_H
