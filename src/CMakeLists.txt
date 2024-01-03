cmake_minimum_required(VERSION 3.12)
project(MorphologicalAnalysis)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(corpus REQUIRED)
find_package(xml_parser REQUIRED)

add_library(MorphologicalAnalysis DisambiguatedWord.cpp DisambiguatedWord.h DisambiguationCorpus.cpp DisambiguationCorpus.h MorphologicalTag.h MetamorphicParse.cpp MetamorphicParse.h InflectionalGroup.cpp InflectionalGroup.h State.cpp State.h Transition.cpp Transition.h MorphologicalParse.cpp MorphologicalParse.h FsmParse.cpp FsmParse.h FsmParseList.cpp FsmParseList.h FiniteStateMachine.cpp FiniteStateMachine.h FsmMorphologicalAnalyzer.cpp FsmMorphologicalAnalyzer.h MorphotacticEngine.cpp MorphotacticEngine.h)
target_link_libraries(MorphologicalAnalysis corpus::corpus xml_parser::xml_parser)
