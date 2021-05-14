cmake_minimum_required(VERSION 3.12)
project(MorphologicalAnalysis)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(MorphologicalAnalysis DisambiguatedWord.cpp DisambiguatedWord.h DisambiguationCorpus.cpp DisambiguationCorpus.h MorphologicalTag.h MetamorphicParse.cpp MetamorphicParse.h InflectionalGroup.cpp InflectionalGroup.h State.cpp State.h Transition.cpp Transition.h MorphologicalParse.cpp MorphologicalParse.h FsmParse.cpp FsmParse.h FsmParseList.cpp FsmParseList.h FiniteStateMachine.cpp FiniteStateMachine.h FsmMorphologicalAnalyzer.cpp FsmMorphologicalAnalyzer.h)
add_executable(Test DisambiguatedWord.cpp DisambiguatedWord.h DisambiguationCorpus.cpp DisambiguationCorpus.h MorphologicalTag.h MetamorphicParse.cpp MetamorphicParse.h InflectionalGroup.cpp InflectionalGroup.h State.cpp State.h Transition.cpp Transition.h MorphologicalParse.cpp MorphologicalParse.h FsmParse.cpp FsmParse.h FsmParseList.cpp FsmParseList.h FiniteStateMachine.cpp FiniteStateMachine.h FsmMorphologicalAnalyzer.cpp FsmMorphologicalAnalyzer.h Test/DisambiguationCorpusTest.cpp Test/InflectionalGroupTest.cpp Test/MorphologicalParseTest.cpp Test/FsmParseTest.cpp Test/FsmParseListTest.cpp Test/TransitionTest.cpp Test/FsmMorphologicalAnalyzerTest.cpp Test/FiniteStateMachineTest.cpp)

target_link_libraries(MorphologicalAnalysis Dictionary XmlParser Corpus)
target_link_libraries(Test Dictionary XmlParser Corpus)
