#include "WordCounter.h"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: word_count input.txt output.csv\n";
        return 1;
    }

    WordCounter counter;

    if (!counter.ReadFile(argv[1]))
    {
        std::cout << "Cannot open input file\n";
        return 1;
    }

    counter.CountWords();

    if (!counter.WriteCSV(argv[2]))
    {
        std::cout << "Cannot create output file\n";
        return 1;
    }

    std::cout << "CSV file created successfully\n";

    return 0;
}
