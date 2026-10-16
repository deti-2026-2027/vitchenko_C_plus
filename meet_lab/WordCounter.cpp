#include "WordCounter.h"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <utility>

bool CompareWords(const std::pair<std::string, int>& a,
                  const std::pair<std::string, int>& b)
{
    return a.second > b.second;
}

bool WordCounter::ReadFile(const std::string &fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
        lines.push_back(line);
    return true;
}

void WordCounter::CountWords()
{
    for (const std::string& line : lines)
    {
        std::string word;

        for (unsigned char c : line)
        {
            if (std::isalnum(c))
                word += c;
            else if (!word.empty())
            {
                words[word]++;
                word.clear();
            }
        }

        if (!word.empty())
            words[word]++;
    }
}

bool WordCounter::WriteCSV(const std::string& fileName)
{
    std::ofstream file(fileName);

    if (!file.is_open())
        return false;

    int total = 0;

    for (const std::pair<const std::string, int>& word : words)
        total += word.second;

    std::vector<std::pair<std::string, int>> sortedWords(
        words.begin(), words.end());

    std::sort(sortedWords.begin(), sortedWords.end(), CompareWords);

    file << "Слово,Частота,Частота (%)\n";

    for (const std::pair<std::string, int>& word : sortedWords)
    {
        double percent = 0;

        if (total > 0)
            percent = word.second * 100.0 / total;

        file << word.first << ", "
             << word.second << ", "
             << percent << "\n";
    }

    return true;
}
