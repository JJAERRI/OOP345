#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
#include <iostream>

namespace seneca {
    enum class PartOfSpeech {
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
    };

    struct Word {
        std::string m_word{};
        std::string m_definition{};
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary {
        Word* m_words = nullptr;  
        size_t m_wordCount = 0;

    public:
        Dictionary();           
        Dictionary(const char* filename);  
        Dictionary(const Dictionary& other);  
        Dictionary(Dictionary&& other) noexcept;  
        Dictionary& operator=(const Dictionary& other);  
        Dictionary& operator=(Dictionary&& other) noexcept;  
        ~Dictionary();  

        void searchWord(const char* word); 
    };

    std::string partOfSpeechToString(PartOfSpeech pos);
}

#endif
