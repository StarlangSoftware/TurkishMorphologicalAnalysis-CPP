//
// Created by Olcay Taner YILDIZ on 3.01.2021.
//

#include "catch.hpp"
#include "../src/FsmMorphologicalAnalyzer.h"

TEST_CASE("TransitionTest") {
    static FsmMorphologicalAnalyzer fsm = FsmMorphologicalAnalyzer();

    SECTION("testNumberWithD") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("3'tü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("1'di").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("2'ydi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("4'tü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("5'ti").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("6'ydı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("7'ydi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("8'di").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("9'du").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("30'du").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("40'tı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("60'tı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("70'ti").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("50'ydi").size() == 0);
    }

    SECTION("testA") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("alkole").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("anormale").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("sakala").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kabala").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("faika").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("halika").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kediye").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("eve").size() == 0);
    }

    SECTION("testNumberWithAccusative") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("2'yi").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("2'i").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("5'i").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("9'u").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("10'u").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("30'u").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("3'ü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("4'ü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("100'ü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("6'yı").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("6'ı").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("40'ı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("60'ı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("90'ı").size() == 0);
    }

    SECTION("testNumberWithDative") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("6'ya").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("6'a").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("9'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("10'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("30'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("40'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("60'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("90'a").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("2'ye").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("2'e").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("8'e").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("5'e").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("4'e").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("1'e").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("3'e").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("7'ye").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("7'e").size());
    }

    SECTION("testPresentTense") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("büyülüyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("bölümlüyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("buğuluyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("bulguluyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("açıklıyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("çalkalıyor").size() == 0);
    }

    SECTION("testC") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("gripçi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("güllaççı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("gülütçü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("gülükçü").size() == 0);
    }

    SECTION("testSH") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("altışar").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("yedişer").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("üçer").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("beşer").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("dörder").size() == 0);
    }

    SECTION("testD") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("koştu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kitaptı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kaçtı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("evdi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("fraktı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("sattı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("aftı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kesti").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ahtı").size() == 0);
    }

    SECTION("testExceptions") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("yaparmışçasına").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("yiyip").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("sana").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("bununla").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("buyla").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("onunla").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("şununla").size() == 0);
        REQUIRE(0 == fsm.morphologicalAnalysis("şuyla").size());
        REQUIRE_FALSE(fsm.morphologicalAnalysis("bana").size() == 0);
    }

    SECTION("testVowelEChangesToIDuringYSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("diyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("yiyor").size() == 0);
    }

    SECTION("testLastIdropsDuringPassiveSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("yoğruldu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("buyruldu").size() == 0);
    }

    SECTION("testShowsSuRegularities") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("karasuyu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("suyu").size() == 0);
    }

    SECTION("testDuplicatesDuringSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("tıbbı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ceddi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("zıddı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("serhaddi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("fenni").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("haddi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("hazzı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("şakkı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("şakı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("halli").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("hali").size() == 0);
    }

    SECTION("testLastIdropsDuringSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("hizbi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kaybı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ahdi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("nesci").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("zehri").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("zikri").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("metni").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("metini").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("katli").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("katili").size() == 0);
    }

    SECTION("TransitionTest-testNounSoftenDuringSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("adabı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("amibi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("armudu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ağacı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("akacı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("arkeoloğu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("filoloğu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ahengi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("küngü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("kitaplığı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("küllüğü").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("adedi").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("adeti").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ağıdı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ağıtı").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("anotu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("anodu").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("Kuzguncuk'u").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("Leylak'ı").size() == 0);
    }

    SECTION("testVerbSoftenDuringSuffixation") {
        REQUIRE_FALSE(fsm.morphologicalAnalysis("cezbediyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("ediyor").size() == 0);
        REQUIRE_FALSE(fsm.morphologicalAnalysis("bahsediyor").size() == 0);
    }
}