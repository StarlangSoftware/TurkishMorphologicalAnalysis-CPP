//
// Created by Olcay Taner YILDIZ on 29.12.2020.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../src/InflectionalGroup.h"

TEST_CASE("InflectionalGroupTest-testGetMorphologicalTag") {
    REQUIRE(InflectionalGroup::getMorphologicalTag("noun") == MorphologicalTag::NOUN);
    REQUIRE(InflectionalGroup::getMorphologicalTag("without") == MorphologicalTag::WITHOUT);
    REQUIRE(InflectionalGroup::getMorphologicalTag("interj") == MorphologicalTag::INTERJECTION);
    REQUIRE(InflectionalGroup::getMorphologicalTag("inf2") == MorphologicalTag::INFINITIVE2);
}

TEST_CASE("InflectionalGroupTest-size") {
    InflectionalGroup inflectionalGroup1 = InflectionalGroup("ADJ");
    REQUIRE(1 == inflectionalGroup1.size());
    InflectionalGroup inflectionalGroup2 = InflectionalGroup("ADJ+JUSTLIKE");
    REQUIRE(2 == inflectionalGroup2.size());
    InflectionalGroup inflectionalGroup3 = InflectionalGroup("ADJ+FUTPART+P1PL");
    REQUIRE(3 == inflectionalGroup3.size());
    InflectionalGroup inflectionalGroup4 = InflectionalGroup("NOUN+A3PL+P1PL+ABL");
    REQUIRE(4 == inflectionalGroup4.size());
    InflectionalGroup inflectionalGroup5 = InflectionalGroup("ADJ+WITH+A3SG+P3SG+ABL");
    REQUIRE(5 == inflectionalGroup5.size());
    InflectionalGroup inflectionalGroup6 = InflectionalGroup("VERB+ABLE+NEG+FUT+A3PL+COP");
    REQUIRE(6 == inflectionalGroup6.size());
    InflectionalGroup inflectionalGroup7 = InflectionalGroup("VERB+ABLE+NEG+AOR+A3SG+COND+A1SG");
    REQUIRE(7 == inflectionalGroup7.size());
}

TEST_CASE("InflectionalGroupTest-containsCase") {
    InflectionalGroup inflectionalGroup1 = InflectionalGroup("NOUN+ACTOF+A3PL+P1PL+NOM");
    REQUIRE(inflectionalGroup1.containsCase() != MorphologicalTag::NOTAG);
    InflectionalGroup inflectionalGroup2 = InflectionalGroup("NOUN+A3PL+P1PL+ACC");
    REQUIRE(inflectionalGroup2.containsCase() != MorphologicalTag::NOTAG);
    InflectionalGroup inflectionalGroup3 = InflectionalGroup("NOUN+ZERO+A3SG+P3PL+DAT");
    REQUIRE(inflectionalGroup3.containsCase() != MorphologicalTag::NOTAG);
    InflectionalGroup inflectionalGroup4 = InflectionalGroup("PRON+QUANTP+A1PL+P1PL+LOC");
    REQUIRE(inflectionalGroup4.containsCase() != MorphologicalTag::NOTAG);
    InflectionalGroup inflectionalGroup5 = InflectionalGroup("NOUN+AGT+A3SG+P2SG+ABL");
    REQUIRE(inflectionalGroup5.containsCase() != MorphologicalTag::NOTAG);
}

TEST_CASE("InflectionalGroupTest-containsPlural") {
    InflectionalGroup inflectionalGroup1 = InflectionalGroup("VERB+NEG+NECES+A1PL");
    REQUIRE_FALSE(!inflectionalGroup1.containsPlural());
    InflectionalGroup inflectionalGroup2 = InflectionalGroup("PRON+PERS+A2PL+PNON+NOM");
    REQUIRE_FALSE(!inflectionalGroup2.containsPlural());
    InflectionalGroup inflectionalGroup3 = InflectionalGroup("NOUN+DIM+A3PL+P2SG+GEN");
    REQUIRE_FALSE(!inflectionalGroup3.containsPlural());
    InflectionalGroup inflectionalGroup4 = InflectionalGroup("NOUN+A3PL+P1PL+GEN");
    REQUIRE_FALSE(!inflectionalGroup4.containsPlural());
    InflectionalGroup inflectionalGroup5 = InflectionalGroup("NOUN+ZERO+A3SG+P2PL+INS");
    REQUIRE_FALSE(!inflectionalGroup5.containsPlural());
    InflectionalGroup inflectionalGroup6 = InflectionalGroup("PRON+QUANTP+A3PL+P3PL+LOC");
    REQUIRE_FALSE(!inflectionalGroup6.containsPlural());
}

TEST_CASE("InflectionalGroupTest-containsTag") {
    InflectionalGroup inflectionalGroup1 = InflectionalGroup("NOUN+ZERO+A3SG+P1SG+NOM");
    REQUIRE_FALSE(!inflectionalGroup1.containsTag(MorphologicalTag::NOUN));
    InflectionalGroup inflectionalGroup2 = InflectionalGroup("NOUN+AGT+A3PL+P2SG+ABL");
    REQUIRE_FALSE(!inflectionalGroup2.containsTag(MorphologicalTag::AGENT));
    InflectionalGroup inflectionalGroup3 = InflectionalGroup("NOUN+INF2+A3PL+P3SG+NOM");
    REQUIRE_FALSE(!inflectionalGroup3.containsTag(MorphologicalTag::NOMINATIVE));
    InflectionalGroup inflectionalGroup4 = InflectionalGroup("NOUN+ZERO+A3SG+P1PL+ACC");
    REQUIRE_FALSE(!inflectionalGroup4.containsTag(MorphologicalTag::ZERO));
    InflectionalGroup inflectionalGroup5 = InflectionalGroup("NOUN+ZERO+A3SG+P2PL+INS");
    REQUIRE_FALSE(!inflectionalGroup5.containsTag(MorphologicalTag::P2PL));
    InflectionalGroup inflectionalGroup6 = InflectionalGroup("PRON+QUANTP+A3PL+P3PL+LOC");
    REQUIRE_FALSE(!inflectionalGroup6.containsTag(MorphologicalTag::QUANTITATIVEPRONOUN));
}

TEST_CASE("InflectionalGroupTest-containsPossessive") {
    InflectionalGroup inflectionalGroup1 = InflectionalGroup("NOUN+ZERO+A3SG+P1SG+NOM");
    REQUIRE_FALSE(!inflectionalGroup1.containsPossessive());
    InflectionalGroup inflectionalGroup2 = InflectionalGroup("NOUN+AGT+A3PL+P2SG+ABL");
    REQUIRE_FALSE(!inflectionalGroup2.containsPossessive());
    InflectionalGroup inflectionalGroup3 = InflectionalGroup("NOUN+INF2+A3PL+P3SG+NOM");
    REQUIRE_FALSE(!inflectionalGroup3.containsPossessive());
    InflectionalGroup inflectionalGroup4 = InflectionalGroup("NOUN+ZERO+A3SG+P1PL+ACC");
    REQUIRE_FALSE(!inflectionalGroup4.containsPossessive());
    InflectionalGroup inflectionalGroup5 = InflectionalGroup("NOUN+ZERO+A3SG+P2PL+INS");
    REQUIRE_FALSE(!inflectionalGroup5.containsPossessive());
    InflectionalGroup inflectionalGroup6 = InflectionalGroup("PRON+QUANTP+A3PL+P3PL+LOC");
    REQUIRE_FALSE(!inflectionalGroup6.containsPossessive());
}