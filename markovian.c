#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 

#include "distribution.h"

#define BUFFER_SIZE 1024
#define SKIP_FIRST_LINE 13
#define MAX_READ_LINE 7

int isDigitsPunct(const char *str) {
    while (*str) {
        if (isdigit(*str) == 0 && ispunct(*str) == 0) {
            return 0;
        }
        str++;
    }
    return 1;
}

void readBible(Base **words) {
    // Buffer used to read the file
    char str[BUFFER_SIZE];
    
    //Reading duh Bible
    FILE * fp = fopen("project_gutenberg_the_king_james_bible.txt", "r");
    if (fp == NULL) {
        printf("File does not exist!\n");
        exit(1);
    } else {
        printf("File exists!\n");
    }

    // Skip the first few lines since it does not contain content
    for(int k = 0; k < SKIP_FIRST_LINE; k++) {
        fgets(str, BUFFER_SIZE, fp);
    }
    
    int line_num = 0;
    char *prevWord = NULL;
    while (fgets(str, BUFFER_SIZE, fp) && line_num < MAX_READ_LINE) {
        printf("line: %s\n", str);

        printf("Splitting string \"%s\" into words:\n", str);
        char temp[BUFFER_SIZE];
        strcpy(temp, str);
        // Removing new line char
        temp[strcspn(temp, "\n")] = 0;
        char *word = strtok(temp, " ");
        while (word != NULL) {
            if(!isDigitsPunct(word)) {
                printf("word: %s\n", word);
                if(prevWord != NULL) {
                    // Probability distribution job here
                    char* base = strdup(prevWord);
                    base[strcspn(base, "\n")] = 0;
                    char* pair = strdup(word);
                    pair[strcspn(pair, "\n")] = 0;
                    incrementFreq(&*words, base, pair);
                }
                prevWord = strdup(word);
                prevWord[strcspn(prevWord, "\n")] = 0;
            }
            
            word = strtok(NULL, " ");
        }
        line_num++;
    }
}

void readExample(Base **words) {
    char text[BUFFER_SIZE] = "In the beginning God created the heaven and the earth. And the earth was without form, and void; and darkness was upon the face of the deep. And the Spirit of God moved upon the face of the waters. And God said, Let there be light: and there was light. And God saw the light, that it was good: and God divided the light from the darkness. And God called the light Day, and the darkness he called Night. And the evening and the morning were the first day.";
    
    char *prevWord = NULL;
    printf("%s\n", text);
    char *word = strtok(text, " ");
    while (word != NULL) {
        
        //printf("word: %s\n", word);
        if(prevWord != NULL) {
            // Probability distribution job here
            incrementFreq(&*words, prevWord, word);
        }
        prevWord = word;
        
        word = strtok(NULL, " ");
    }
}

char* generateRandomSentence(Base *map) {
    srand(time(0));
    int mapSize = getMapSize(&map);
    int num = rand() % mapSize;
    
    printf("Random number:%d/%d\n", num, mapSize);
    printf("Random word:%s\n", ((Base*) getNthBase(&map, num))->key);
    
    return "asdf";
}

int main(void) {
    Base *words = NULL;
    
    //readExample(&words);
    readBible(&words);
    
    printf("Abs Total Freq: %d\n", getAbsTotalFreq(&words));
    printf("Total Freq: %d for Word: %s\n", getTotalFreq(&words, "the"), "the");
    
    printf("%d\n", getFreq(&words, "1:1", "In"));
    printf("%d\n", getFreq(&words, "face", "of"));
    printf("%d\n", getFreq(&words, "the", "waters."));
    
    char* output = generateRandomSentence(words);
    printf("%s\n", output);
    
    return 0;
}