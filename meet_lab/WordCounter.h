#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

#include <map>
#include <string>
#include <list>

class WordCounter {
public:
    bool ReadFile(const std::string& fileName);
    void CountWords();
    bool WriteCSV(const std::string& fileName);

private:
    std::map<std::string, int> words;
    std::list<std::string> lines;
};

#endif
