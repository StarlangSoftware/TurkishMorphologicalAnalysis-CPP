For Developers
============

You can also see [Java](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis), [Python](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Py), [Cython](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-Cy), or [C#](https://github.com/starlangsoftware/TurkishMorphologicalAnalysis-CS) repository.

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
