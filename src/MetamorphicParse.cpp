//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#include "MetamorphicParse.h"

/**
 * metaMorphemes that can be used.
 */
const string MetamorphicParse::metaMorphemes[META_MORPHEME_SIZE] = {"Ar", "Ar", "CA", "CA",
                                                                    "CA", "cAsHnA", "CH", "CHk",
                                                                    "DA", "DAn", "DH", "DHk",
                                                                    "DHkCA", "DHr", "DHr", "DHr",
                                                                    "H", "Hl", "Hm", "Hn",
                                                                    "Hn", "Hn", "HmHz", "HncH",
                                                                    "HnHz", "Hr", "Hr", "Hs",
                                                                    "Ht", "Hyor", "Hz", "k",
                                                                    "ki", "kü", "lAn", "lAr",
                                                                    "lArDHr", "lArH", "lArH'", "lAs",
                                                                    "lH", "lHk", "lHm", "m",
                                                                    "mA", "mA", "mAcA", "mAdAn",
                                                                    "mAk", "mAksHzHn", "mAktA", "mAlH",
                                                                    "mAzlHk", "mHs", "n", "n",
                                                                    "nA", "ncA", "nDA", "nDAn",
                                                                    "nH", "nHn", "nHz", "nlAr",
                                                                    "SA", "SAl", "sH", "SH",
                                                                    "SH", "SHn", "SHnHz", "SHnlAr",
                                                                    "SHz", "ŞAr", "t", "yA",
                                                                    "yA", "yAbil", "yAcAk", "yAcAk",
                                                                    "yAdur", "yAgel", "yAlH", "yAmA",
                                                                    "yAmAdAn", "yAn", "yArAk", "yAsH",
                                                                    "yDH", "yH", "yHcH", "yHm",
                                                                    "yHn", "yHncA", "yHp", "yHs",
                                                                    "yHver", "yHz", "yken", "ylA",
                                                                    "ymHs", "ysA", "z", "zsHn",
                                                                    "zsHnHz", "zlAr", "yAkal", "yAkoy",
                                                                    "yAgor"};

const MorphologicalTag MetamorphicParse::morphotacticTags[META_MORPHEME_SIZE] = {
/**
 * Aorist Tense : Her hafta sonunda futbol oynarlar.
*/
        MorphologicalTag::AORIST,
/**
 * Causative Form : Pişirmek
*/
        MorphologicalTag::CAUSATIVE,
/**
 * As if : Yaşarmışcasına
*/
        MorphologicalTag::ASIF,
/**
 * -LY : Akıllıca
*/
        MorphologicalTag::LY,
/**
 * Equative : Öylece
*/
        MorphologicalTag::EQUATIVE,
/**
 * As if
*/
        MorphologicalTag::ASIF,
/**
 * Agent : Toplayıcı
*/
        MorphologicalTag::AGENT,
/**
 * Dimension : Küçücük
*/
        MorphologicalTag::DIMENSION,
/**
 * Locative : Aşağıda
*/
        MorphologicalTag::LOCATIVE,
/**
 * Ablative : Okuldan
*/
        MorphologicalTag::ABLATIVE,
/**
 * Past tense : Yaşandı
*/
        MorphologicalTag::PASTTENSE,
/**
 * Past participle : Kırılmış
*/
        MorphologicalTag::PASTPARTICIPLE,
/**
 * As long as : Yaşadıkça
*/
        MorphologicalTag::ASLONGAS,
/**
 * Copula : Mavidir
*/
        MorphologicalTag::COPULA,
/**
 * Since : Yıllardır
*/
        MorphologicalTag::SINCE,
/**
 * Causitive
*/
        MorphologicalTag::CAUSATIVE,
/**
 * 3rd person singular possessive : Onun
*/
        MorphologicalTag::P3SG,
/**
 * Passive : Açıldı
*/
        MorphologicalTag::PASSIVE,
/**
 * 1st person singular possessive : Benim
*/
        MorphologicalTag::P1SG,
/**
 * Reflexive : Kendi
*/
        MorphologicalTag::REFLEXIVE,
/**
 * Passive
*/
        MorphologicalTag::PASSIVE,
/**
 * 2nd person singular possessive :Senin
*/
        MorphologicalTag::P2SG,
/**
 * 1st person plural possessive :  Bizim
*/
        MorphologicalTag::P1PL,
/**
 * Ordinal Number : Altıncı
*/
        MorphologicalTag::ORDINAL,
/**
 * 2nd person plural possessive : Sizin
*/
        MorphologicalTag::P2PL,
/**
 * Aorist
*/
        MorphologicalTag::AORIST,
/**
 * Causitive
*/
        MorphologicalTag::CAUSATIVE,
/**
 * Reciprocal verb : Görüşmek
*/
        MorphologicalTag::RECIPROCAL,
/**
 * Causitive
*/
        MorphologicalTag::CAUSATIVE,
/**
 * Progressive1 : Görüyor
*/
        MorphologicalTag::PROGRESSIVE1,
/**
 * 1st person plural agreement : Biz gideriz
*/
        MorphologicalTag::A1PL,
/**
 * 1st person plural agreement
*/
        MorphologicalTag::A1PL,
/**
 * Relative : Gelenin
*/
        MorphologicalTag::RELATIVE,
/**
 * Relative
*/
        MorphologicalTag::RELATIVE,
/**
 * Acquire : Kazanılan
*/
        MorphologicalTag::ACQUIRE,
/**
 * 3rd person plural agreement : Onlar giderler
*/
        MorphologicalTag::A3PL,
/**
 * Since
*/
        MorphologicalTag::SINCE,
/**
 * 3rd person plural possessive : Onların
*/
        MorphologicalTag::P3PL,
/**
 * 3rd person plural possessive
*/
        MorphologicalTag::P3PL,
/**
 * Become : Abideleş
*/
        MorphologicalTag::BECOME,
/**
 * With : Kalemle
*/
        MorphologicalTag::WITH,
/**
 * Ness : Ağırbaşlılık
*/
        MorphologicalTag::NESS,
/**
 * 1st person plural agreement
*/
        MorphologicalTag::A1PL,
/**
 * 1st person singular agreement : Ben giderim
*/
        MorphologicalTag::A1SG,
/**
 * Infinitive2 : Yapma
*/
        MorphologicalTag::INFINITIVE2,
/**
 * Negative : Yapama
*/
        MorphologicalTag::NEGATIVE,
/**
 * Act of : Aldatmaca
*/
        MorphologicalTag::ACTOF,
/**
 * Without having done so : Çaktırmadan
*/
        MorphologicalTag::WITHOUTHAVINGDONESO,
/**
 * Infinitive : Yapmak
*/
        MorphologicalTag::INFINITIVE,
/**
 * Without having done so
*/
        MorphologicalTag::WITHOUTHAVINGDONESO,
/**
 * Progressive2 : Görmekte
*/
        MorphologicalTag::PROGRESSIVE2,
/**
 * Necessity : Yapmalı
*/
        MorphologicalTag::NECESSITY,
/**
 * Notable state : Anlaşılmazlık
*/
        MorphologicalTag::NOTABLESTATE,
/**
 * Narrative Narrative Past Tense : Oluşmuş
*/
        MorphologicalTag::NARRATIVE,
/**
 * 2nd person singuular agreement : Sen gelirsin
*/
        MorphologicalTag::A2SG,
/**
 * Passive
*/
        MorphologicalTag::PASSIVE,
/**
 * Dative case : Bana
*/
        MorphologicalTag::DATIVE,
/**
 * Equative
*/
        MorphologicalTag::EQUATIVE,
/**
 * Locative
*/
        MorphologicalTag::LOCATIVE,
/**
 * Ablative
*/
        MorphologicalTag::ABLATIVE,
/**
 * Accusatıve : Beni
*/
        MorphologicalTag::ACCUSATIVE,
/**
 * Genitive : Benim
*/
        MorphologicalTag::GENITIVE,
/**
 * 2nd person plural agreement : Siz gelirsiniz
*/
        MorphologicalTag::A2PL,
/**
 * 3rd person plural agreement
*/
        MorphologicalTag::A3PL,
/**
 * Desire/Past Auxiliary : Çıkarsa
*/
        MorphologicalTag::DESIRE,
/**
 * Related to : Davranışsal
*/
        MorphologicalTag::RELATED,
/**
 * 3rd person singular possessive
*/
        MorphologicalTag::P3SG,
/**
 * Just like : Destansı
*/
        MorphologicalTag::JUSTLIKE,
/**
 * Almost : Dikensi
*/
        MorphologicalTag::ALMOST,
/**
 * 2nd person singuular agreement
*/
        MorphologicalTag::A2SG,
/**
 * 2nd person plural agreement
*/
        MorphologicalTag::A2PL,
/**
 * 3rd person plural agreement
*/
        MorphologicalTag::A3PL,
/**
 * Without : Dikişsiz
*/
        MorphologicalTag::WITHOUT,
/**
 * Distributive : altışar
*/
        MorphologicalTag::DISTRIBUTIVE,
/**
 * Causitive form
*/
        MorphologicalTag::CAUSATIVE,
/**
 * Dative case
*/
        MorphologicalTag::DATIVE,
/**
 * Optative : Doğanaya
*/
        MorphologicalTag::OPTATIVE,
/**
 * Ability, possibility : Olabilir
*/
        MorphologicalTag::ABLE,
/**
 * Future participle : Gülecek
*/
        MorphologicalTag::FUTUREPARTICIPLE,
/**
 * Future : Yağacak
*/
        MorphologicalTag::FUTURE,
/**
 * Continuous : Yapadur
*/
        MorphologicalTag::REPEAT,
/**
 * Ever since : Çıkagel
*/
        MorphologicalTag::EVERSINCE,
/**
 * Since doing so : Amasyalı
*/
        MorphologicalTag::SINCEDOINGSO,
/**
 * Not able state : Anlaşılmazlık
*/
        MorphologicalTag::NOTABLESTATE,
/**
 * Wıthout beıng able to have done so: kararlamadan
*/
        MorphologicalTag::WITHOUTBEINGABLETOHAVEDONESO,
/**
 * Present partıcıple : Sarılan
*/
        MorphologicalTag::PRESENTPARTICIPLE,
/**
 * By doing so : Zıplayarak
*/
        MorphologicalTag::BYDOINGSO,
/**
 * Projection : Öpülesi
*/
        MorphologicalTag::FEELLIKE,
/**
 * Past tense : Gitti
*/
        MorphologicalTag::PASTTENSE,
/**
 * Accusative
*/
        MorphologicalTag::ACCUSATIVE,
/**
 * Agent
*/
        MorphologicalTag::AGENT,
/**
 * 1st person singuular agreement
*/
        MorphologicalTag::A1SG,
/**
 * 2nd person plural agreement
*/
        MorphologicalTag::A2PL,
/**
 * When : Okuyunca
*/
        MorphologicalTag::WHEN,
/**
 * After doing so : Yapıp
*/
        MorphologicalTag::AFTERDOINGSO,
/**
 * Infinitive : Yapış
*/
        MorphologicalTag::INFINITIVE3,
/**
 * Hastility : Yapıver
*/
        MorphologicalTag::HASTILY,
/**
 * 1st person plural agreement
*/
        MorphologicalTag::A1PL,
/**
 * While : Gelirken
*/
        MorphologicalTag::WHILE,
/**
 * Instrumental : Kışın, arabayla
*/
        MorphologicalTag::INSTRUMENTAL,
/**
 * Narrative
*/
        MorphologicalTag::NARRATIVE,
/**
 * Conditional : Gelirse
*/
        MorphologicalTag::CONDITIONAL,
/**
 * 3rd person singuular agreement : O gelir
*/
        MorphologicalTag::A3SG,
/**
 * 2nd person singuular agreement
*/
        MorphologicalTag::A2SG,
/**
 * 2nd person plural agreement
*/
        MorphologicalTag::A2PL,
/**
 * 3rd person plural agreement
*/
        MorphologicalTag::A3PL,
/**
 * Stay : Bakakal
*/
        MorphologicalTag::STAY,
/**
 * Start : Alıkoy
*/
        MorphologicalTag::START,
/**
 * Repeat : Yapagör
*/
        MorphologicalTag::REPEAT
};

/**
 * The getMetaMorphemeTag method takes a String tag as an input and takes the first char of the tag. If first char
 * is a punctuation it gets a substring from the tag. And gets the meta morphemes of this tag then adds to the
 * result {@link vector}.
 *
 * @param tag String to get meta morphemes from.
 * @return vector type result which holds meta morphemes.
 */
vector<MorphologicalTag> MetamorphicParse::getMetaMorphemeTag(const string& tag) {
    vector<MorphologicalTag> result;
    string s = Word::charAt(tag, 0);
    string _tag = tag;
    if (Word::isPunctuation(s)) {
        _tag = tag.substr(1, tag.size());
    }
    for (int j = 0; j < META_MORPHEME_SIZE; j++) {
        if (_tag == MetamorphicParse::metaMorphemes[j]) {
            result.emplace_back(morphotacticTags[j]);
        }
    }
    return result;
}

/**
 * Another getMetaMorphemeTag method which also takes parse as an input. It also checks the morphotactic tags.
 *
 * @param parse MorphologicalParse type input.
 * @param tag   String to get meta morphemes from.
 * @return ArrayList type result which holds meta morphemes.
 */
vector<MorphologicalTag> MetamorphicParse::getMetaMorphemeTag(const MorphologicalParse& parse, const string& tag){
    vector<MorphologicalTag> result;
    string s = Word::charAt(tag, 0);
    string _tag = tag;
    if (Word::isPunctuation(s)) {
        _tag = tag.substr(1, tag.size());
    }
    for (int j = 0; j < META_MORPHEME_SIZE; j++) {
        if (_tag == MetamorphicParse::metaMorphemes[j] && parse.containsTag(morphotacticTags[j])) {
            result.emplace_back(morphotacticTags[j]);
        }
    }
    return result;
}

/**
 * The getter method for Private Word root.
 *
 * @return Word type root.
 */
Word MetamorphicParse::getWord() const{
    return root;
}

/**
 * An empty constructor of {@link MetamorphicParse} class.
 */
MetamorphicParse::MetamorphicParse() = default;

/**
 * A constructor of {@link MetamorphicParse} class which creates an {@link vector} metaMorphemeList which has split words
 * according to +.
 *
 * @param parse String to parse.
 */
MetamorphicParse::MetamorphicParse(const string& parse){
    int i;
    if (parse == "+") {
        root = Word("+");
    } else {
        vector<string> words = Word::split(parse, "+");
        root = Word(words[0]);
        for (i = 1; i < words.size(); i++)
            metaMorphemeList.emplace_back(words[i]);
    }
}

/**
 * The size method returns the size of the metaMorphemeList.
 *
 * @return the size of the metaMorphemeList.
 */
int MetamorphicParse::size() const{
    return metaMorphemeList.size() + 1;
}

/**
 * The addMetaMorphemeList method splits input String by + and add to the metaMorphemeList.
 *
 * @param newTacticSet String to add the metaMorphemeList.
 */
void MetamorphicParse::addMetaMorphemeList(const string& newTacticSet) {
    vector<string> tactics = Word::split(newTacticSet, "+");
    metaMorphemeList.insert(metaMorphemeList.end(), tactics.begin(), tactics.end());
}

/**
 * The removeMetaMorphemeFromIndex method removes the meta morpheme at given index from metaMorphemeList.
 *
 * @param index to remove from metaMorphemeList.
 */
void MetamorphicParse::removeMetaMorphemeFromIndex(int index) {
    metaMorphemeList.erase(metaMorphemeList.begin() + index - 1, metaMorphemeList.end());
}

/**
 * The getMetaMorpheme method gets the meta morpheme at given index.
 *
 * @param index is used to get the meta morpheme.
 * @return metaMorphemeList's corresponding meta morpheme.
 */
string MetamorphicParse::getMetaMorpheme(int index) const{
    if (index == 0) {
        return root.getName();
    } else {
        return metaMorphemeList.at(index - 1);
    }
}

/**
 * Overridden toString method to return resulting meta morphemes in metaMorphemeList.
 *
 * @return String result.
 */
string MetamorphicParse::to_string() const{
    string result = root.getName();
    for (const string& metaMorpheme : metaMorphemeList) {
        result += "+" + metaMorpheme;
    }
    return result;
}
