//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include "catch.hpp"
#include "../MorphologicalParse.h"

TEST_CASE("MorphologicalParseTest-testGetTransitionList") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse("iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE("NOUN+A3SG+PNON+NOM" == parse1.getTransitionList());
    REQUIRE("VERB+POS+ADJ+PRESPART" == parse2.getTransitionList());
    REQUIRE("ADJ" == parse3.getTransitionList());
    REQUIRE("VERB+VERB+PASS+VERB+ABLE+NEG+AOR+A3SG" == parse4.getTransitionList());
    REQUIRE("VERB+VERB+CAUS+VERB+PASS+POS+NOUN+INF2+A3SG+P3SG+NOM" == parse5.getTransitionList());
    REQUIRE("VERB+VERB+CAUS+VERB+PASS+POS+VERB+ABLE+AOR+ADJ+ZERO" == parse6.getTransitionList());
    REQUIRE("ADJ+VERB+BECOME+VERB+CAUS+VERB+PASS+POS+VERB+ABLE+NOUN+INF2+A3PL+P3PL+ABL" == parse7.getTransitionList());
    REQUIRE("ADJ+VERB+ZERO+PAST+A3SG" == parse8.getTransitionList());
}

TEST_CASE("MorphologicalParseTest-testGetTag") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse("iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE("A3SG" == parse1.getTag(2));
    REQUIRE("PRESPART" == parse2.getTag(4));
    REQUIRE("serbest" == parse3.getTag(0));
    REQUIRE("AOR" == parse4.getTag(7));
    REQUIRE("P3SG" == parse5.getTag(10));
    REQUIRE("ABLE" == parse6.getTag(8));
    REQUIRE("ABL" == parse7.getTag(15));
}

TEST_CASE("MorphologicalParseTest-testGetTagSize") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE(5 == parse1.tagSize());
    REQUIRE(5 == parse2.tagSize());
    REQUIRE(2 == parse3.tagSize());
    REQUIRE(9 == parse4.tagSize());
    REQUIRE(12 == parse5.tagSize());
    REQUIRE(12 == parse6.tagSize());
    REQUIRE(16 == parse7.tagSize());
    REQUIRE(6 == parse8.tagSize());
}

TEST_CASE("MorphologicalParseTest-testSize") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE(1 == parse1.size());
    REQUIRE(2 == parse2.size());
    REQUIRE(1 == parse3.size());
    REQUIRE(3 == parse4.size());
    REQUIRE(4 == parse5.size());
    REQUIRE(5 == parse6.size());
    REQUIRE(6 == parse7.size());
    REQUIRE(2 == parse8.size());
}

TEST_CASE("MorphologicalParseTest-testGetRootPos") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE("NOUN" == parse1.getRootPos());
    REQUIRE("VERB" == parse2.getRootPos());
    REQUIRE("ADJ" == parse3.getRootPos());
    REQUIRE("VERB" == parse4.getRootPos());
    REQUIRE("VERB" == parse5.getRootPos());
    REQUIRE("VERB" == parse6.getRootPos());
    REQUIRE("ADJ" == parse7.getRootPos());
    REQUIRE("ADJ" == parse8.getRootPos());
}

TEST_CASE("MorphologicalParseTest-testGetPos") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE("NOUN" == parse1.getPos());
    REQUIRE("ADJ" == parse2.getPos());
    REQUIRE("ADJ" == parse3.getPos());
    REQUIRE("VERB" == parse4.getPos());
    REQUIRE("NOUN" == parse5.getPos());
    REQUIRE("ADJ" == parse6.getPos());
    REQUIRE("NOUN" == parse7.getPos());
    REQUIRE("VERB" == parse8.getPos());
}

TEST_CASE("MorphologicalParseTest-testGetWordWithPos") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE("bayan+NOUN" == parse1.getWordWithPos()->getName());
    REQUIRE("yaşa+VERB" == parse2.getWordWithPos()->getName());
    REQUIRE("serbest+ADJ" == parse3.getWordWithPos()->getName());
    REQUIRE("et+VERB" == parse4.getWordWithPos()->getName());
    REQUIRE("sür+VERB" == parse5.getWordWithPos()->getName());
    REQUIRE("değiş+VERB" == parse6.getWordWithPos()->getName());
    REQUIRE("iyi+ADJ" == parse7.getWordWithPos()->getName());
    REQUIRE("değil+ADJ" == parse8.getWordWithPos()->getName());
}

TEST_CASE("MorphologicalParseTest-testLastIGContainsCase") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE("NOM" == parse1.lastIGContainsCase());
    REQUIRE("NULL" == parse2.lastIGContainsCase());
    REQUIRE("NULL" == parse3.lastIGContainsCase());
    REQUIRE("NULL" == parse4.lastIGContainsCase());
    REQUIRE("NOM" == parse5.lastIGContainsCase());
    REQUIRE("NULL" == parse6.lastIGContainsCase());
    REQUIRE("ABL" == parse7.lastIGContainsCase());
}

TEST_CASE("MorphologicalParseTest-testLastIGContainsPossessive") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE_FALSE(parse1.lastIGContainsPossessive());
    REQUIRE_FALSE(parse2.lastIGContainsPossessive());
    REQUIRE_FALSE(parse3.lastIGContainsPossessive());
    REQUIRE_FALSE(parse4.lastIGContainsPossessive());
    REQUIRE_FALSE(!parse5.lastIGContainsPossessive());
    REQUIRE_FALSE(parse6.lastIGContainsPossessive());
    REQUIRE_FALSE(!parse7.lastIGContainsPossessive());
}

TEST_CASE("MorphologicalParseTest-testIsPlural") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE_FALSE(parse1.isPlural());
    REQUIRE_FALSE(parse2.isPlural());
    REQUIRE_FALSE(parse3.isPlural());
    REQUIRE_FALSE(parse4.isPlural());
    REQUIRE_FALSE(parse5.isPlural());
    REQUIRE_FALSE(parse6.isPlural());
    REQUIRE_FALSE(!parse7.isPlural());
}

TEST_CASE("MorphologicalParseTest-testIsAuxiliary") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE_FALSE(parse1.isAuxiliary());
    REQUIRE_FALSE(parse2.isAuxiliary());
    REQUIRE_FALSE(parse3.isAuxiliary());
    REQUIRE_FALSE(!parse4.isAuxiliary());
    REQUIRE_FALSE(parse5.isAuxiliary());
    REQUIRE_FALSE(parse6.isAuxiliary());
    REQUIRE_FALSE(parse7.isAuxiliary());
}

TEST_CASE("MorphologicalParseTest-testIsNoun") {
    MorphologicalParse parse1, parse5, parse7;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    REQUIRE_FALSE(!parse1.isNoun());
    REQUIRE_FALSE(!parse5.isNoun());
    REQUIRE_FALSE(!parse7.isNoun());
}

TEST_CASE("MorphologicalParseTest-testIsAdjective") {
    MorphologicalParse parse2, parse3, parse6;
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    REQUIRE_FALSE(!parse2.isAdjective());
    REQUIRE_FALSE(!parse3.isAdjective());
    REQUIRE_FALSE(!parse6.isAdjective());
}

TEST_CASE("MorphologicalParseTest-testIsVerb") {
    MorphologicalParse parse4, parse8;
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE_FALSE(!parse4.isVerb());
    REQUIRE_FALSE(!parse8.isVerb());
}

TEST_CASE("MorphologicalParseTest-testIsRootVerb") {
    MorphologicalParse parse2, parse4, parse5, parse6;
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    REQUIRE_FALSE(!parse2.isRootVerb());
    REQUIRE_FALSE(!parse4.isRootVerb());
    REQUIRE_FALSE(!parse5.isRootVerb());
    REQUIRE_FALSE(!parse6.isRootVerb());
}

TEST_CASE("MorphologicalParseTest-testGetTreePos") {
    MorphologicalParse parse1, parse2, parse3, parse4, parse5, parse6, parse7, parse8, parse9;
    parse1 = MorphologicalParse("bayan+NOUN+A3SG+PNON+NOM");
    parse2 = MorphologicalParse("yaşa+VERB+POS^DB+ADJ+PRESPART");
    parse3 = MorphologicalParse("serbest+ADJ");
    parse4 = MorphologicalParse("et+VERB^DB+VERB+PASS^DB+VERB+ABLE+NEG+AOR+A3SG");
    parse5 = MorphologicalParse("sür+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+NOUN+INF2+A3SG+P3SG+NOM");
    parse6 = MorphologicalParse("değiş+VERB^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE+AOR^DB+ADJ+ZERO");
    parse7 = MorphologicalParse(
            "iyi+ADJ^DB+VERB+BECOME^DB+VERB+CAUS^DB+VERB+PASS+POS^DB+VERB+ABLE^DB+NOUN+INF2+A3PL+P3PL+ABL");
    parse8 = MorphologicalParse("değil+ADJ^DB+VERB+ZERO+PAST+A3SG");
    parse9 = MorphologicalParse("hazır+ADJ^DB+VERB+ZERO+PAST+A3SG");
    REQUIRE("NP" == parse1.getTreePos());
    REQUIRE("ADJP" == parse2.getTreePos());
    REQUIRE("ADJP" == parse3.getTreePos());
    REQUIRE("VP" == parse4.getTreePos());
    REQUIRE("NP" == parse5.getTreePos());
    REQUIRE("ADJP" == parse6.getTreePos());
    REQUIRE("NP" == parse7.getTreePos());
    REQUIRE("NEG" == parse8.getTreePos());
    REQUIRE("NOMP" == parse9.getTreePos());
}