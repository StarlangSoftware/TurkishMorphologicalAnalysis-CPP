//
// Created by Olcay Taner Yıldız on 24.02.2019.
//

#ifndef MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H
#define MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H

#include <string>
#include <vector>
#include "MorphologicalTag.h"
#include "Word.h"

using namespace std;

class MetamorphicParse {
private:
    vector<string> metaMorphemeList;
    Word root;
public:
    static const int META_MORPHEME_SIZE = 109;
    static const string metaMorphemes[META_MORPHEME_SIZE];
    static const MorphologicalTag morphotacticTags[META_MORPHEME_SIZE];
    MetamorphicParse();
    static vector<MorphologicalTag> getMetaMorphemeTag(string tag);
    Word getWord();
    explicit MetamorphicParse(string parse);
    int size();
    void addMetaMorphemeList(string newTacticSet);
    void removeMetaMorphemeFromIndex(int index);
    string getMetaMorpheme(int index);
    string to_string();
};

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
#endif //MORPHOLOGICALANALYSIS_METAMORPHICPARSE_H
