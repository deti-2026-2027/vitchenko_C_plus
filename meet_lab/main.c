#include <stdio.h>
#include <string.h>

typedef struct Word{
    char text[100];
    int count;
    double freq;
} Word;

Word words[10000];

int is_letter_or_digit(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'))
    return 1;
    return 0;
};

int read_words(FILE * in, Word words[])
{
    int ch;
    char buf[100] = {0};
    int len = 0;
    int words_readed = 0;
    while((ch = fgetc(in)) != EOF)
    {
        if (is_letter_or_digit((char)ch) == 1)
            buf[len++] = (char)ch;

        else if (len > 0)
        {
            buf[len] = '\0';
            int added = 0;
            for (int i = 0; i < words_readed; i++)
            {
                if (strcmp(words[i].text, buf) == 0)
                {
                    words[i].count++;
                    added = 1;
                    break;
                }
            }
            if(added == 0)
            {
                strcpy(words[words_readed].text, buf);
                words[words_readed++].count = 1;
            }
            buf[0] = '\0';
            len = 0;
        }
    }
    if(len > 0)
    {
        int added = 0;
        for (int i = 0; i < words_readed; i++)
            {
                if (strcmp(words[i].text, buf) == 0)
                {
                    words[i].count++;
                    added = 1;
                    break;
                }
            }
        if(added == 0)
        {
            strcpy(words[words_readed].text, buf);
            words[words_readed++].count = 1;
        }
    }
    return words_readed;
};

void sort_words(Word words[], int words_readed)
{
    for (int i = 0; i < words_readed - 1; i++)
    {
        for (int j = 0; j < words_readed - 1 - i; j++)
        {
            if (words[j].count < words[j + 1].count)
            {
                Word temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    FILE* fin = fopen(argv[1], "r");
    FILE* fout = fopen(argv[2], "w");

    int words_readed = read_words(fin, words);
    sort_words(words, words_readed);

    int total_words = 0;
    for (int i = 0; i < words_readed; i++)
        total_words += words[i].count;

    for (int i = 0; i < words_readed; i++)
    {
        words[i].freq = (words[i].count * 100.0) / total_words;
        fprintf(fout, "%s   %d   %.2f\n", words[i].text, words[i].count, words[i].freq);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
