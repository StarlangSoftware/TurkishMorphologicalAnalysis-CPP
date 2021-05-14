//
// Created by Olcay Taner YILDIZ on 6.01.2021.
//

#include "catch.hpp"
#include "../DisambiguationCorpus.h"

TEST_CASE("DisambiguationCorpusTest-testCorpus") {
    DisambiguationCorpus corpus = DisambiguationCorpus("penntreebank.txt");
    REQUIRE(19108 == corpus.sentenceCount());
    REQUIRE(170211 == corpus.numberOfWords());
}