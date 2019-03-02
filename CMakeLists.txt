cmake_minimum_required(VERSION 3.12)
project(MorphologicalAnalysis)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(MorphologicalAnalysis MorphologicalTag.h MetamorphicParse.cpp MetamorphicParse.h InflectionalGroup.cpp InflectionalGroup.h State.cpp State.h Transition.cpp Transition.h MorphologicalParse.cpp MorphologicalParse.h FsmParse.cpp FsmParse.h FsmParseList.cpp FsmParseList.h FiniteStateMachine.cpp FiniteStateMachine.h FsmMorphologicalAnalyzer.cpp FsmMorphologicalAnalyzer.h)
add_executable(TestMorphologicalAnalysis MorphologicalTag.h MetamorphicParse.cpp MetamorphicParse.h InflectionalGroup.cpp InflectionalGroup.h State.cpp State.h Transition.cpp Transition.h MorphologicalParse.cpp MorphologicalParse.h FsmParse.cpp FsmParse.h FsmParseList.cpp FsmParseList.h FiniteStateMachine.cpp FiniteStateMachine.h FsmMorphologicalAnalyzer.cpp FsmMorphologicalAnalyzer.h TestMorphologicalAnalysis.cpp)

target_link_libraries(MorphologicalAnalysis Dictionary XmlParser Corpus)
target_link_libraries(TestMorphologicalAnalysis Dictionary XmlParser Corpus)
