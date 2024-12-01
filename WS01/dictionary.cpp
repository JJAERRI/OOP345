#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <iomanip>

namespace seneca {

    Dictionary::Dictionary() : m_words(nullptr), m_wordCount(0) {}

    Dictionary::Dictionary(const char* filename) {
        std::ifstream file(filename);
        if (!file.is_open()) return;

        std::string line;
        size_t count = 0;
        while (std::getline(file, line)) {
            ++count;
        }

        m_wordCount = count;
        m_words = new Word[m_wordCount];

        file.clear();
        file.seekg(0);
        size_t index = 0;
        while (std::getline(file, line) && index < m_wordCount) {
            std::stringstream ss(line);
            std::string word, pos, definition;

            std::getline(ss, word, ',');
            std::getline(ss, pos, ',');
            std::getline(ss, definition);

            m_words[index].m_word = word;
            m_words[index].m_definition = definition;

            if (pos == "n." || pos == "n. pl.") m_words[index].m_pos = PartOfSpeech::Noun;
            else if (pos == "adv.") m_words[index].m_pos = PartOfSpeech::Adverb;
            else if (pos == "a.") m_words[index].m_pos = PartOfSpeech::Adjective;
            else if (pos == "v." || pos == "v. i." || pos == "v. t." || pos == "v. t. & i.") m_words[index].m_pos = PartOfSpeech::Verb;
            else if (pos == "prep.") m_words[index].m_pos = PartOfSpeech::Preposition;
            else if (pos == "pron.") m_words[index].m_pos = PartOfSpeech::Pronoun;
            else if (pos == "conj.") m_words[index].m_pos = PartOfSpeech::Conjunction;
            else if (pos == "interj.") m_words[index].m_pos = PartOfSpeech::Interjection;
            else m_words[index].m_pos = PartOfSpeech::Unknown;

            ++index;
        }
    }

    //copy constructor
    Dictionary::Dictionary(const Dictionary& other) {
        m_wordCount = other.m_wordCount;
        m_words = new Word[m_wordCount];
        for (size_t i = 0; i < m_wordCount; ++i) {
            m_words[i] = other.m_words[i];
        }
    }

    //move constroctor 
    Dictionary::Dictionary(Dictionary&& other) noexcept {
        m_wordCount = other.m_wordCount;
        m_words = other.m_words;
        other.m_words = nullptr;
        other.m_wordCount = 0;
    }

    //copy assignment
    Dictionary& Dictionary::operator=(const Dictionary& other) {
        if (this != &other) {
            delete[] m_words;
            m_wordCount = other.m_wordCount;
            m_words = new Word[m_wordCount];
            for (size_t i = 0; i < m_wordCount; ++i) {
                m_words[i] = other.m_words[i];
            }
        }
        return *this;
    }

    //move assignment
    Dictionary& Dictionary::operator=(Dictionary&& other) noexcept {
        if (this != &other) {
            delete[] m_words;
            m_wordCount = other.m_wordCount;
            m_words = other.m_words;
            other.m_words = nullptr;
            other.m_wordCount = 0;
        }
        return *this;
    }

    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    void Dictionary::searchWord(const char* word) {
        bool found = false;
        bool firstOccurrencePrinted = false;
        std::unordered_set<std::string> printedDefinitions;  // Set for storing already printed definitions

        size_t maxWordLength = 0;

        for (size_t i = 0; i < m_wordCount; ++i) {
            if (m_words[i].m_word == word) {
                if (m_words[i].m_word.length() > maxWordLength) {
                    maxWordLength = m_words[i].m_word.length();
                }
            }
        }

        for (size_t i = 0; i < m_wordCount; ++i) {
            if (m_words[i].m_word == word) {
                found = true;

                if (!firstOccurrencePrinted) {
                    std::cout << std::left << std::setw(maxWordLength) << m_words[i].m_word << " - "; 
                    if (g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
                        std::cout << "(" << partOfSpeechToString(m_words[i].m_pos) << ") ";
                    }
                    std::cout << m_words[i].m_definition << std::endl;
                    printedDefinitions.insert(m_words[i].m_definition);  
                    firstOccurrencePrinted = true;
                }

                if (g_settings.m_show_all) {
                    for (size_t j = i + 1; j < m_wordCount; ++j) {
                        if (m_words[j].m_word == word && printedDefinitions.find(m_words[j].m_definition) == printedDefinitions.end()) {
                            std::cout << std::string(maxWordLength, ' ') << " - "; 
                            if (g_settings.m_verbose && m_words[j].m_pos != PartOfSpeech::Unknown) {
                                std::cout << "(" << partOfSpeechToString(m_words[j].m_pos) << ") ";
                            }
                            std::cout << m_words[j].m_definition << std::endl;
                            printedDefinitions.insert(m_words[j].m_definition);  
                        }
                    }
                }

                if (!g_settings.m_show_all) break;  
            }
        }

        if (!found) {
            std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
        }
    }

    std::string partOfSpeechToString(PartOfSpeech pos) {
        switch (pos) {
        case PartOfSpeech::Noun: return "noun";
        case PartOfSpeech::Pronoun: return "pronoun";
        case PartOfSpeech::Adjective: return "adjective";
        case PartOfSpeech::Adverb: return "adverb";
        case PartOfSpeech::Verb: return "verb";
        case PartOfSpeech::Preposition: return "preposition";
        case PartOfSpeech::Conjunction: return "conjunction";
        case PartOfSpeech::Interjection: return "interjection";
        default: return "unknown";
        }
    }
}
