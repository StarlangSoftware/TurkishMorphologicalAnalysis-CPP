Morphological Analysis
============

## Morphology

In linguistics, the term morphology refers to the study of the internal structure of words. Each word is assumed to consist of one or more morphemes, which can be defined as the smallest linguistic unit having a particular meaning or grammatical function. One can come across morphologically simplex words, i.e. roots, as well as morphologically complex ones, such as compounds or affixed forms.

Batı-lı-laş-tır-ıl-ama-yan-lar-dan-mış-ız 
west-With-Make-Caus-Pass-Neg.Abil-Nom-Pl-Abl-Evid-A3Pl
‘It appears that we are among the ones that cannot be westernized.’

The morphemes that constitute a word combine in a (more or less) strict order. Most morphologically complex words are in the ”ROOT-SUFFIX1-SUFFIX2-...” structure. Affixes have two types: (i) derivational affixes, which change the meaning and sometimes also the grammatical category of the base they are attached to, and (ii) inflectional affixes serving particular grammatical functions. In general, derivational suffixes precede inflectional ones. The order of derivational suffixes is reflected on the meaning of the derived form. For instance, consider the combination of the noun göz ‘eye’ with two derivational suffixes -lIK and -CI: Even though the same three morphemes are used, the meaning of a word like gözcülük ‘scouting’ is clearly different from that of gözlükçü ‘optician’.

## Dilbaz

Here we present a new morphological analyzer, which is (i) open: The latest version of source codes, the lexicon, and the morphotactic rule engine are all available here, (ii) extendible: One of the disadvantages of other morphological analyzers is that their lexicons are fixed or unmodifiable, which prevents to add new bare-forms to the morphological analyzer. In our morphological analyzer, the lexicon is in text form and is easily modifiable, (iii) fast: Morphological analysis is one of the core components of any NLP process. It must be very fast to handle huge corpora. Compared to other morphological analyzers, our analyzer is capable of analyzing hundreds of thousands words per second, which makes it one of the fastest Turkish morphological analyzers available.

The morphological analyzer consists of five main components, namely, a lexicon, a finite state transducer, a rule engine for suffixation, a trie data structure, and a least recently used (LRU) cache.

In this analyzer, we assume all idiosyncratic information to be encoded in the lexicon. While phonologically conditioned allomorphy will be dealt with by the transducer, other types of allomorphy, all exceptional forms to otherwise regular processes, as well as words formed through derivation (except for the few transparently compositional derivational suffixes are considered to be included in the lexicon.

In our morphological analyzer, finite state transducer is encoded in an xml file.

To overcome the irregularities and also to accelerate the search for the bareforms, we use a trie data structure in our morphological analyzer, and store all words in our lexicon in that data structure. For the regular words, we only store that word in our trie, whereas for irregular words we store both the original form and some prefix of that word. 

Video Lectures
============

[<img src="https://github.com/StarlangSoftware/TurkishMorphologicalAnalysis/blob/master/video1.jpg" width="50%">](https://youtu.be/KxguxpbgDQc)[<img src="https://github.com/StarlangSoftware/TurkishMorphologicalAnalysis/blob/master/video2.jpg" width="50%">](https://youtu.be/UMmA2LMkAkw)[<img src="https://github.com/StarlangSoftware/TurkishMorphologicalAnalysis/blob/master/video3.jpg" width="50%">](https://youtu.be/dP97ovMSSfE)[<img src="https://github.com/StarlangSoftware/TurkishMorphologicalAnalysis/blob/master/video4.jpg" width="50%">](https://youtu.be/Tgmy5tts_pY)

For Developers
============

You can also see [Java](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis), [Python](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Py), [Cython](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Cy), [Swift](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Swift), [Js](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Js), [C](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-C), or [C#](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-CS) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called TurkishMorphologicalAnalysis-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run TurkishMorphologicalAnalysis-CPP.

Detailed Description
============

+ [Creating FsmMorphologicalAnalyzer](#creating-fsmmorphologicalanalyzer)
+ [Word level morphological analysis](#word-level-morphological-analysis)
+ [Sentence level morphological analysis](#sentence-level-morphological-analysis)

## Creating FsmMorphologicalAnalyzer 

FsmMorphologicalAnalyzer provides Turkish morphological analysis. This class can be created as follows:

    FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer();
    
This generates a new `TxtDictionary` type dictionary from [`turkish_dictionary.txt`](https://github.com/olcaytaner/Dictionary/tree/master/src/main/resources) with fixed cache size 100000 and by using [`turkish_finite_state_machine.xml`](https://github.com/olcaytaner/MorphologicalAnalysis/tree/master/src/main/resources). 

Creating a morphological analyzer with different cache size, dictionary or finite state machine is also possible. 
* With different cache size, 

        FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer(50000);   

* Using a different dictionary,

        FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer("my_turkish_dictionary.txt");   

* Specifying both finite state machine and dictionary, 

        FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer("fsm.xml", "my_turkish_dictionary.txt") ;      
    
* Giving finite state machine and cache size with creating `TxtDictionary` object, 
        
        TxtDictionary dictionary = new TxtDictionary("my_turkish_dictionary.txt", new TurkishWordComparator());
        FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer("fsm.xml", dictionary, 50000) ;
    
* With different finite state machine and creating `TxtDictionary` object,
       
        TxtDictionary dictionary = new TxtDictionary("my_turkish_dictionary.txt", new TurkishWordComparator(), "my_turkish_misspelled.txt");
        FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer("fsm.xml", dictionary);

## Word level morphological analysis

For morphological analysis,  `morphologicalAnalysis(String word)` method of `FsmMorphologicalAnalyzer` is used. This returns `FsmParseList` object. 


    FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer();
    String word = "yarına";
    FsmParseList fsmParseList = fsm.morphologicalAnalysis(word);
    for (int i = 0; i < fsmParseList.size(); i++){
      System.out.println(fsmParseList.getFsmParse(i).transitionList();
    } 
      
Output

    yar+NOUN+A3SG+P2SG+DAT
    yar+NOUN+A3SG+P3SG+DAT
    yarı+NOUN+A3SG+P2SG+DAT
    yarın+NOUN+A3SG+PNON+DAT
    
From `FsmParseList`, a single `FsmParse` can be obtained as follows:

    FsmParse parse = fsmParseList.getFsmParse(0);
    System.out.println(parse.transitionList();   
    
Output    
    
    yar+NOUN+A3SG+P2SG+DAT
    
## Sentence level morphological analysis
`morphologicalAnalysis(Sentence sentence)` method of `FsmMorphologicalAnalyzer` is used. This returns `FsmParseList[]` object. 

    FsmMorphologicalAnalyzer fsm = new FsmMorphologicalAnalyzer();
    Sentence sentence = new Sentence("Yarın doktora gidecekler");
    FsmParseList[] parseLists = fsm.morphologicalAnalysis(sentence);
    for(int i = 0; i < parseLists.length; i++){
        for(int j = 0; j < parseLists[i].size(); j++){
            FsmParse parse = parseLists[i].getFsmParse(j);
            System.out.println(parse.transitionList());
        }
        System.out.println("-----------------");
    }
    
Output
    
    -----------------
    yar+NOUN+A3SG+P2SG+NOM
    yar+NOUN+A3SG+PNON+GEN
    yar+VERB+POS+IMP+A2PL
    yarı+NOUN+A3SG+P2SG+NOM
    yarın+NOUN+A3SG+PNON+NOM
    -----------------
    doktor+NOUN+A3SG+PNON+DAT
    doktora+NOUN+A3SG+PNON+NOM
    -----------------
    git+VERB+POS+FUT+A3PL
    git+VERB+POS^DB+NOUN+FUTPART+A3PL+PNON+NOM

# Cite

	@inproceedings{yildiz-etal-2019-open,
    	title = "An Open, Extendible, and Fast {T}urkish Morphological Analyzer",
    	author = {Y{\i}ld{\i}z, Olcay Taner  and
      	Avar, Beg{\"u}m  and
      	Ercan, G{\"o}khan},
    	booktitle = "Proceedings of the International Conference on Recent Advances in Natural Language Processing (RANLP 2019)",
    	month = sep,
    	year = "2019",
    	address = "Varna, Bulgaria",
    	publisher = "INCOMA Ltd.",
    	url = "https://www.aclweb.org/anthology/R19-1156",
    	doi = "10.26615/978-954-452-056-4_156",
    	pages = "1364--1372",
	}

For Contibutors
============

### Conan Setup

1. First install conan.

pip install conan

Instructions are given in the following page:

https://docs.conan.io/2/installation.html

2. Add conan remote 'ozyegin' with IP: 104.247.163.162 with the following command:

conan remote add ozyegin http://104.247.163.162:8081/artifactory/api/conan/conan-local --insert

3. Use the comman conan list to check for installed packages. Probably there are no installed packages.

conan list

### conanfile.py file

1. Put the correct dependencies in the requires part
```
    requires = ["math/1.0.0", "classification/1.0.0"]
```

2. Default settings are:
```
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": True, "fPIC": True}
    exports_sources = "src/*", "Test/*"

    def layout(self):
        cmake_layout(self, src_folder="src")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        copy(conanfile=self, keep_path=False, src=join(self.source_folder), dst=join(self.package_folder, "include"), pattern="*.h")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.a")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.so")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "lib"), pattern="*.dylib")
        copy(conanfile=self, keep_path=False, src=self.build_folder, dst=join(self.package_folder, "bin"), pattern="*.dll")

    def package_info(self):
        self.cpp_info.libs = ["ComputationalGraph"]
```

### CMakeLists.txt file
1. Set the C++ standard with compiler flags.
```
	set(CMAKE_CXX_STANDARD 20)
	set(CMAKE_CXX_FLAGS "-O3")
```
2. Dependent packages should be given with find_package.
```
	find_package(util_c REQUIRED)
	find_package(data_structure_c REQUIRED)
```
3. For library part, use add_library and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_library(Math src/Distribution.cpp src/Distribution.h src/DiscreteDistribution.cpp src/DiscreteDistribution.h src/Vector.cpp src/Vector.h src/Eigenvector.cpp src/Eigenvector.h src/Matrix.cpp src/Matrix.h src/Tensor.cpp src/Tensor.h)
	target_link_libraries(Math util_c::util_c data_structure_c::data_structure_c m)
```
4. For executable tests, use add_executable and target_link_libraries commands. Use m library for math linker in Linux.
```
	add_executable(DiscreteDistributionTest src/Distribution.cpp src/Distribution.h src/DiscreteDistribution.cpp src/DiscreteDistribution.h src/Vector.cpp src/Vector.h src/Eigenvector.cpp src/Eigenvector.h src/Matrix.cpp src/Matrix.h src/Tensor.cpp src/Tensor.h Test/DiscreteDistributionTest.cpp)
	target_link_libraries(DiscreteDistributionTest util_c::util_c data_structure_c::data_structure_c m)
```

### Data files
1. Add data files to the cmake-build-debug folder.

### C++ files

1. If needed, comparator operators == and < should be implemented for map and set data structures.
```
    bool operator==(const Word &anotherWord) const{
        return (name == anotherWord.name);
    }
    bool operator<(const Word &anotherWord) const{
        return (name < anotherWord.name);
    }
```
2. Do not forget to comment each function.
```
	/**
 	* A constructor of Word class which gets a String name as an input and assigns to the name variable.
	*
	* @param _name String input.
 	*/
	Word::Word(const string &_name) {
```
3. Function names should follow caml case.
```
	int Word::charCount() const
```
4. Write getter and setter methods.
```
	string Word::getName() const
	void Word::setName(const string &_name)
```
5. Use catch.hpp for testing purposes. Add
```
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
```
line in only one of the test files. Add
```
#include "catch.hpp"
```
line in all test files. Example test file is given below:
```
TEST_CASE("DictionaryTest") {
    TxtDictionary lowerCaseDictionary = TxtDictionary("lowercase.txt", "turkish_misspellings.txt");
    TxtDictionary mixedCaseDictionary = TxtDictionary("mixedcase.txt", "turkish_misspellings.txt");
    TxtDictionary dictionary = TxtDictionary();
    SECTION("testSize"){
        REQUIRE(29 == lowerCaseDictionary.size());
        REQUIRE(58 == mixedCaseDictionary.size());
        REQUIRE(62113 == dictionary.size());
    }
    SECTION("testGetWord"){
        for (int i = 0; i < dictionary.size(); i++){
            REQUIRE_FALSE(nullptr == dictionary.getWord(i));
        }
    }
    SECTION("testLongestWordSize"){
        REQUIRE(1 == lowerCaseDictionary.longestWordSize());
        REQUIRE(1 == mixedCaseDictionary.longestWordSize());
        REQUIRE(21 == dictionary.longestWordSize());
    }
```
6. Enumerated types should be declared with enum class.
```
	enum class Pos {
		ADJECTIVE,
		NOUN,
		VERB,
		ADVERB,
```
7. Every header file should start with
```
	#ifndef MATH_DISTRIBUTION_H
	#define MATH_DISTRIBUTION_H
```
and end with
```
	#endif //MATH_DISTRIBUTION_H
```
8. Do not forget to use const expression for parameters, if they will not be changed in the function.
```
	void Word::setName(const string &_name);
```
9. Do not forget to use const expression for methods, which do not modify any class attribute. Also use [[dodiscard]]
```
	[[nodiscard]] bool isPunctuation() const;
```
10. Use xmlparser package for parsing xml files.
```
    auto* doc = new XmlDocument("test.xml");
    doc->parse();
    XmlElement* root = doc->getFirstChild();
    XmlElement* firstChild = root->getFirstChild();
```
11. Data structures: Use map for hash map, unordered_map for linked hash map, vector for array list, unordered_set for hash set
