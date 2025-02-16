cmake_minimum_required(VERSION 3.12)
project(MorphologicalAnalysis)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(corpus REQUIRED)
find_package(xml_parser REQUIRED)

add_library(MorphologicalAnalysis src/DisambiguatedWord.cpp src/DisambiguatedWord.h src/DisambiguationCorpus.cpp src/DisambiguationCorpus.h src/MorphologicalTag.h src/MetamorphicParse.cpp src/MetamorphicParse.h src/InflectionalGroup.cpp src/InflectionalGroup.h src/State.cpp src/State.h src/Transition.cpp src/Transition.h src/MorphologicalParse.cpp src/MorphologicalParse.h src/FsmParse.cpp src/FsmParse.h src/FsmParseList.cpp src/FsmParseList.h src/FiniteStateMachine.cpp src/FiniteStateMachine.h src/FsmMorphologicalAnalyzer.cpp src/FsmMorphologicalAnalyzer.h src/MorphotacticEngine.cpp src/MorphotacticEngine.h)
target_link_libraries(MorphologicalAnalysis corpus::corpus xml_parser::xml_parser)
add_executable(Test src/DisambiguatedWord.cpp src/DisambiguatedWord.h src/DisambiguationCorpus.cpp src/DisambiguationCorpus.h src/MorphologicalTag.h src/MetamorphicParse.cpp src/MetamorphicParse.h src/InflectionalGroup.cpp src/InflectionalGroup.h src/State.cpp src/State.h src/Transition.cpp src/Transition.h src/MorphologicalParse.cpp src/MorphologicalParse.h src/FsmParse.cpp src/FsmParse.h src/FsmParseList.cpp src/FsmParseList.h src/FiniteStateMachine.cpp src/FiniteStateMachine.h src/FsmMorphologicalAnalyzer.cpp src/FsmMorphologicalAnalyzer.h Test/DisambiguationCorpusTest.cpp Test/InflectionalGroupTest.cpp Test/MorphologicalParseTest.cpp Test/FsmParseTest.cpp Test/FsmParseListTest.cpp Test/TransitionTest.cpp Test/FsmMorphologicalAnalyzerTest.cpp Test/FiniteStateMachineTest.cpp src/MorphotacticEngine.cpp src/MorphotacticEngine.h)
target_link_libraries(Test corpus::corpus xml_parser::xml_parser)
