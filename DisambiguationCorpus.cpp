//
// Created by Olcay Taner YILDIZ on 2019-04-01.
//

#include <fstream>
#include "DisambiguationCorpus.h"
#include "DisambiguatedWord.h"

/**
 * Constructor which creates an {@link vector} of sentences and a {@link CounterHashMap} of wordList.
 */
DisambiguationCorpus::DisambiguationCorpus() = default;

/**
 * Constructor which creates a new empty copy of the {@link DisambiguationCorpus}.
 *
 * @return An empty copy of the {@link DisambiguationCorpus}.
 */
DisambiguationCorpus DisambiguationCorpus::emptyCopy() {
    return DisambiguationCorpus();
}

/**
 * Constructor which takes a file name {@link String} as an input and reads the file line by line. It takes each word of the line,
 * and creates a new {@link DisambiguatedWord} with current word and its {@link MorphologicalParse}. It also creates a new {@link Sentence}
 * when a new sentence starts, and adds each word to this sentence till the end of that sentence.
 *
 * @param fileName File which will be read and parsed.
 */
DisambiguationCorpus::DisambiguationCorpus(string fileName) {
    string line, word, parse;
    DisambiguatedWord* newWord;
    Sentence* newSentence = nullptr;
    ifstream inputFile;
    inputFile.open(fileName, ifstream::in);
    while (inputFile.good()){
        getline(inputFile, line);
        vector<string> tokens = Word::split(line, "\t");
        word = tokens.at(0);
        parse = tokens.at(1);
        if (!word.empty() && !parse.empty()){
            newWord = new DisambiguatedWord(word, MorphologicalParse(parse));
            if (word == "<S>") {
                newSentence = new Sentence();
            } else {
                if (word == "</S>") {
                    addSentence(newSentence);
                } else {
                    if (word == "<DOC>" || word == "</DOC>" || word == "<TITLE>" || word == "</TITLE>") {
                    } else {
                        if (newSentence != nullptr) {
                            newSentence->addWord(newWord);
                        }
                    }
                }
            }
        }
    }
    inputFile.close();
}

/**
 * The writeToFile method takes a {@link String} file name as an input and writes the elements of sentences {@link ArrayList}
 * to this file with proper tags which indicates the beginnings and endings of the document and sentence.
 *
 * @param fileName File which will be filled with the sentences.
 */
void DisambiguationCorpus::writeToFile(string fileName) {
    ofstream outputFile;
    outputFile.open(fileName, ofstream::out);
    outputFile << "<DOC>\t<DOC>+BDTag\n";
    for (Sentence* sentence : sentences) {
        outputFile << "<S>\t<S>+BSTag\n";
        for (int i = 0; i < sentence->wordCount(); i++) {
            auto* word = (DisambiguatedWord*) sentence->getWord(i);
            outputFile << word->getName() + "\t" + word->getParse().to_string();
        }
        outputFile << "</S>\t</S>+ESTag\n";
    }
    outputFile << "</DOC>\t</DOC>+EDTag\n";
    outputFile.close();
}

/**
 * The writeToFile method which takes a file name {@link String} and a {@link WordFormat} as input simply implies the
 * output format of the words to be written to the file with given name. Word format can be surface, letter2, letter3, and letter4.
 * Surface form leaves the output as it is, and letterK divides the output as the substrings of length of K.
 *
 * @param fileName File which will be filled with the sentences.
 * @param format   Output format of the words to be written to the file.
 */
void DisambiguationCorpus::writeToFile(string fileName, WordFormat format) {
    if (format == WordFormat::SURFACE || format == WordFormat::LETTER_2 || format == WordFormat::LETTER_3 || format == WordFormat::LETTER_4) {
        Corpus::writeToFile(move(fileName), format);
    }
}
