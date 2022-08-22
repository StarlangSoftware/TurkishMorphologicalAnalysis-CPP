//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include "catch.hpp"
#include "../src/FsmParseList.h"
#include "../src/FsmMorphologicalAnalyzer.h"

TEST_CASE("FsmParseListTest-testSize") {
    FsmParseList parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9, parse14;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır");
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse4 = fsm.morphologicalAnalysis("değerlendirmede");
    parse5 = fsm.morphologicalAnalysis("soruşturmasının");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    parse7 = fsm.morphologicalAnalysis("esaslarını");
    parse8 = fsm.morphologicalAnalysis("güçleriyle");
    parse9 = fsm.morphologicalAnalysis("bulmayacakları");
    parse14 = fsm.morphologicalAnalysis("sana");
    REQUIRE(2 == parse1.size());
    REQUIRE(2 == parse2.size());
    REQUIRE(6 == parse3.size());
    REQUIRE(4 == parse4.size());
    REQUIRE(5 == parse5.size());
    REQUIRE(12 == parse6.size());
    REQUIRE(8 == parse7.size());
    REQUIRE(6 == parse8.size());
    REQUIRE(5 == parse9.size());
    REQUIRE(4 == parse14.size());
}

TEST_CASE("FsmParseListTest-testRootWords") {
    FsmParseList parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır");
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse4 = fsm.morphologicalAnalysis("değerlendirmede");
    parse5 = fsm.morphologicalAnalysis("soruşturmasının");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    parse7 = fsm.morphologicalAnalysis("esaslarını");
    parse8 = fsm.morphologicalAnalysis("güçleriyle");
    parse9 = fsm.morphologicalAnalysis("bulmayacakları");
    REQUIRE("aç" == parse1.rootWords());
    REQUIRE("kop$kopar" == parse2.rootWords());
    REQUIRE("topla$toplam$toplama" == parse3.rootWords());
    REQUIRE("değer$değerlen$değerlendir$değerlendirme" == parse4.rootWords());
    REQUIRE("sor$soru$soruş$soruştur$soruşturma" == parse5.rootWords());
    REQUIRE("karşı$karşıla$karşılaş$karşılaştır$karşılaştırma$karşılaştırmalı" == parse6.rootWords());
    REQUIRE("esas" == parse7.rootWords());
    REQUIRE("güç" == parse8.rootWords());
    REQUIRE("bul" == parse9.rootWords());
}

TEST_CASE("FsmParseListTest-testGetParseWithLongestRootWord") {
    FsmParseList parse2, parse3, parse4, parse5, parse6;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse4 = fsm.morphologicalAnalysis("değerlendirmede");
    parse5 = fsm.morphologicalAnalysis("soruşturmasının");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    REQUIRE(Word("kopar") == *(parse2.getParseWithLongestRootWord().getWord()));
    REQUIRE(Word("toplama") == *(parse3.getParseWithLongestRootWord().getWord()));
    REQUIRE(Word("değerlendirme") == *(parse4.getParseWithLongestRootWord().getWord()));
    REQUIRE(Word("soruşturma") == *(parse5.getParseWithLongestRootWord().getWord()));
    REQUIRE(Word("karşılaştırmalı") == *(parse6.getParseWithLongestRootWord().getWord()));
}

TEST_CASE("FsmParseListTest-testReduceToParsesWithSameRootAndPos") {
    FsmParseList parse2, parse3, parse6;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    parse2.reduceToParsesWithSameRootAndPos(new Word("kop+VERB"));
    REQUIRE(1 == parse2.size());
    parse3.reduceToParsesWithSameRootAndPos(new Word("topla+VERB"));
    REQUIRE(2 == parse3.size());
    parse6.reduceToParsesWithSameRootAndPos(new Word("karşıla+VERB"));
    REQUIRE(2 == parse6.size());
}

TEST_CASE("FsmParseListTest-testReduceToParsesWithSameRoot") {
    FsmParseList parse2, parse3, parse6, parse7, parse8;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    parse7 = fsm.morphologicalAnalysis("esaslarını");
    parse8 = fsm.morphologicalAnalysis("güçleriyle");
    parse2.reduceToParsesWithSameRoot("kop");
    REQUIRE(1 == parse2.size());
    parse3.reduceToParsesWithSameRoot("topla");
    REQUIRE(3 == parse3.size());
    parse6.reduceToParsesWithSameRoot("karşı");
    REQUIRE(4 == parse6.size());
    parse7.reduceToParsesWithSameRoot("esas");
    REQUIRE(8 == parse7.size());
    parse8.reduceToParsesWithSameRoot("güç");
    REQUIRE(6 == parse8.size());
}

TEST_CASE("FsmParseListTest-testConstructParseListForDifferentRootWithPos") {
    FsmParseList parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse1 = fsm.morphologicalAnalysis("açılır");
    parse2 = fsm.morphologicalAnalysis("koparılarak");
    parse3 = fsm.morphologicalAnalysis("toplama");
    parse4 = fsm.morphologicalAnalysis("değerlendirmede");
    parse5 = fsm.morphologicalAnalysis("soruşturmasının");
    parse6 = fsm.morphologicalAnalysis("karşılaştırmalı");
    parse7 = fsm.morphologicalAnalysis("esaslarını");
    parse8 = fsm.morphologicalAnalysis("güçleriyle");
    parse9 = fsm.morphologicalAnalysis("bulmayacakları");
    REQUIRE(1 == parse1.constructParseListForDifferentRootWithPos().size());
    REQUIRE(2 == parse2.constructParseListForDifferentRootWithPos().size());
    REQUIRE(5 == parse3.constructParseListForDifferentRootWithPos().size());
    REQUIRE(4 == parse4.constructParseListForDifferentRootWithPos().size());
    REQUIRE(5 == parse5.constructParseListForDifferentRootWithPos().size());
    REQUIRE(7 == parse6.constructParseListForDifferentRootWithPos().size());
    REQUIRE(2 == parse7.constructParseListForDifferentRootWithPos().size());
    REQUIRE(2 == parse8.constructParseListForDifferentRootWithPos().size());
    REQUIRE(1 == parse9.constructParseListForDifferentRootWithPos().size());
}

TEST_CASE("FsmParseListTest-testParsesWithoutPrefixAndSuffix") {
    FsmParseList parse10, parse11, parse12, parse13;
    FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();
    parse10 = fsm.morphologicalAnalysis("kitabı");
    parse11 = fsm.morphologicalAnalysis("kitapları");
    parse12 = fsm.morphologicalAnalysis("o");
    parse13 = fsm.morphologicalAnalysis("arabası");
    REQUIRE("P3SG+NOM$PNON+ACC" == parse10.parsesWithoutPrefixAndSuffix());
    REQUIRE("A3PL+P3PL+NOM$A3PL+P3SG+NOM$A3PL+PNON+ACC$A3SG+P3PL+NOM" == parse11.parsesWithoutPrefixAndSuffix());
    REQUIRE("DET$PRON+DEMONSP+A3SG+PNON+NOM$PRON+PERS+A3SG+PNON+NOM" == parse12.parsesWithoutPrefixAndSuffix());
    REQUIRE("NOUN+A3SG+P3SG+NOM$NOUN^DB+ADJ+ALMOST" == parse13.parsesWithoutPrefixAndSuffix());
}