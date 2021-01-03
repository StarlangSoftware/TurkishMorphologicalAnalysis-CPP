//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include "catch.hpp"
#include "../FsmMorphologicalAnalyzer.h"

TEST_CASE("FsmParseTest-testGetLastLemmaWithTag") {
    FsmParse parse1, parse2, parse4, parse5, parse6;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır").getFsmParse(0);
    parse2 = fsm.morphologicalAnalysis("koparılarak").getFsmParse(0);
    parse4 = fsm.morphologicalAnalysis("değerlendirmede").getFsmParse(0);
    parse5 = fsm.morphologicalAnalysis("soruşturmasının").getFsmParse(0);
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı").getFsmParse(0);
    REQUIRE("açıl" == parse1.getLastLemmaWithTag("VERB"));
    REQUIRE("koparıl" == parse2.getLastLemmaWithTag("VERB"));
    REQUIRE("değerlendir" == parse4.getLastLemmaWithTag("VERB"));
    REQUIRE("soruştur" == parse5.getLastLemmaWithTag("VERB"));
    REQUIRE("karşı" == parse6.getLastLemmaWithTag("ADJ"));
}

TEST_CASE("FsmParseTest-testGetLastLemma") {
    FsmParse parse1, parse2, parse4, parse5, parse6;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır").getFsmParse(0);
    parse2 = fsm.morphologicalAnalysis("koparılarak").getFsmParse(0);
    parse4 = fsm.morphologicalAnalysis("değerlendirmede").getFsmParse(0);
    parse5 = fsm.morphologicalAnalysis("soruşturmasının").getFsmParse(0);
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı").getFsmParse(0);
    REQUIRE("açıl" == parse1.getLastLemma());
    REQUIRE("koparılarak" == parse2.getLastLemma());
    REQUIRE("değerlendirme" == parse4.getLastLemma());
    REQUIRE("soruşturma" == parse5.getLastLemma());
    REQUIRE("karşılaştır" == parse6.getLastLemma());
}

TEST_CASE("FsmParseTest-testGetTransitionList") {
    FsmParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır").getFsmParse(0);
    parse2 = fsm.morphologicalAnalysis("koparılarak").getFsmParse(0);
    parse3 = fsm.morphologicalAnalysis("toplama").getFsmParse(0);
    parse4 = fsm.morphologicalAnalysis("değerlendirmede").getFsmParse(0);
    parse5 = fsm.morphologicalAnalysis("soruşturmasının").getFsmParse(0);
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı").getFsmParse(0);
    parse7 = fsm.morphologicalAnalysis("esaslarını").getFsmParse(0);
    parse8 = fsm.morphologicalAnalysis("güçleriyle").getFsmParse(0);
    parse9 = fsm.morphologicalAnalysis("bulmayacakları").getFsmParse(0);
    REQUIRE("aç+VERB^DB+VERB+PASS+POS+AOR+A3SG" == parse1.to_String());
    REQUIRE("kop+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+ADV+BYDOINGSO" == parse2.to_String());
    REQUIRE("topla+NOUN+A3SG+P1SG+DAT" == parse3.to_String());
    REQUIRE("değer+NOUN+A3SG+PNON+NOM^DB+VERB+ACQUIRE^DB+VERB+CAUS+POS^DB+NOUN+INF2+A3SG+PNON+LOC" == parse4.to_String());
    REQUIRE("sor+VERB+RECIP^DB+VERB+CAUS+POS^DB+NOUN+INF2+A3SG+P3SG+GEN" == parse5.to_String());
    REQUIRE("karşı+ADJ^DB+VERB+BECOME^DB+VERB+CAUS+POS+NECES+A3SG" == parse6.to_String());
    REQUIRE("esas+ADJ^DB+NOUN+ZERO+A3PL+P2SG+ACC" == parse7.to_String());
    REQUIRE("güç+ADJ^DB+NOUN+ZERO+A3PL+P3PL+INS" == parse8.to_String());
    REQUIRE("bul+VERB+NEG^DB+ADJ+FUTPART+P3PL" == parse9.to_String());
}

TEST_CASE("FsmParseTest-testWithList") {
    FsmParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır").getFsmParse(0);
    parse2 = fsm.morphologicalAnalysis("koparılarak").getFsmParse(0);
    parse3 = fsm.morphologicalAnalysis("toplama").getFsmParse(0);
    parse4 = fsm.morphologicalAnalysis("değerlendirmede").getFsmParse(0);
    parse5 = fsm.morphologicalAnalysis("soruşturmasının").getFsmParse(0);
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı").getFsmParse(0);
    parse7 = fsm.morphologicalAnalysis("esaslarını").getFsmParse(0);
    parse8 = fsm.morphologicalAnalysis("güçleriyle").getFsmParse(0);
    parse9 = fsm.morphologicalAnalysis("bulmayacakları").getFsmParse(0);
    REQUIRE("aç+Hl+Hr" == parse1.getWithList());
    REQUIRE("kop+Ar+Hl+yArAk" == parse2.getWithList());
    REQUIRE("topla+Hm+yA" == parse3.getWithList());
    REQUIRE("değer+lAn+DHr+mA+DA" == parse4.getWithList());
    REQUIRE("sor+Hs+DHr+mA+sH+nHn" == parse5.getWithList());
    REQUIRE("karşı+lAs+DHr+mAlH" == parse6.getWithList());
    REQUIRE("esas+lAr+Hn+yH" == parse7.getWithList());
    REQUIRE("güç+lArH+ylA" == parse8.getWithList());
    REQUIRE("bul+mA+yAcAk+lArH" == parse9.getWithList());
}

TEST_CASE("FsmParseTest-testSuffixList") {
    FsmParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır").getFsmParse(0);
    parse2 = fsm.morphologicalAnalysis("koparılarak").getFsmParse(0);
    parse3 = fsm.morphologicalAnalysis("toplama").getFsmParse(0);
    parse4 = fsm.morphologicalAnalysis("değerlendirmede").getFsmParse(0);
    parse5 = fsm.morphologicalAnalysis("soruşturmasının").getFsmParse(0);
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı").getFsmParse(0);
    parse7 = fsm.morphologicalAnalysis("esaslarını").getFsmParse(0);
    parse8 = fsm.morphologicalAnalysis("güçleriyle").getFsmParse(0);
    parse9 = fsm.morphologicalAnalysis("bulmayacakları").getFsmParse(0);
    REQUIRE("VerbalRoot(F5PR)(aç)+PassiveHl(açıl)+OtherTense2(açılır)" == parse1.getSuffixList());
    REQUIRE("VerbalRoot(F1P1)(kop)+CausativeAr(kopar)+PassiveHl(koparıl)+Adverb1(koparılarak)" == parse2.getSuffixList());
    REQUIRE("NominalRoot(topla)+Possessive(toplam)+Case1(toplama)" == parse3.getSuffixList());
    REQUIRE("NominalRoot(değer)+VerbalRoot(F5PR)(değerlen)+CausativeDHr(değerlendir)+NominalRoot(değerlendirme)+Case1(değerlendirmede)" == parse4.getSuffixList());
    REQUIRE("VerbalRoot(F5PR)(sor)+Reciprocal(soruş)+CausativeDHr(soruştur)+NominalRoot(soruşturma)+Possessive3(soruşturması)+Case1(soruşturmasının)" == parse5.getSuffixList());
    REQUIRE("AdjectiveRoot(karşı)+VerbalRoot(F5PR)(karşılaş)+CausativeDHr(karşılaştır)+OtherTense(karşılaştırmalı)" == parse6.getSuffixList());
    REQUIRE("AdjectiveRoot(esas)+Plural(esaslar)+Possessive(esasların)+AccusativeNoun(esaslarını)" == parse7.getSuffixList());
    REQUIRE("AdjectiveRoot(güç)+Possesive3(güçleri)+Case1(güçleriyle)" == parse8.getSuffixList());
    REQUIRE("VerbalRoot(F5PW)(bul)+Negativema(bulma)+AdjectiveParticiple(bulmayacak)+Adjective(bulmayacakları)" == parse9.getSuffixList());
}