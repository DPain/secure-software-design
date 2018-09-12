#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h> 

#include "distribution.h"

#define BUFFER_SIZE 1024
#define SKIP_FIRST_LINE 13
#define MAX_READ_LINE 7
#define TWITTER_MAX_SIZE 280

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
    FILE * fp = fopen("10.txt", "r");
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
    char text[BUFFER_SIZE * 10] = "In the beginning God created the heaven and the earth. And the earth was without form, and void; and darkness was upon the face of the deep. And the Spirit of God moved upon the face of the waters. And God said, Let there be light: and there was light. And God saw the light, that it was good: and God divided the light from the darkness. And God called the light Day, and the darkness he called Night. And the evening and the morning were the first day. And God said, Let there be a firmament in the midst of the waters, and let it divide the waters from the waters. And God made the firmament, and divided the waters which were under the firmament from the waters which were above the firmament: and it was so. And God called the firmament Heaven. And the evening and the morning were the second day. And God said, Let the waters under the heaven be gathered together unto one place, and let the dry land appear: and it was so. And God called the dry land Earth; and the gathering together of the waters called he Seas: and God saw that it was good. And God said, Let the earth bring forth grass, the herb yielding seed, and the fruit tree yielding fruit after his kind, whose seed is in itself, upon the earth: and it was so. And the earth brought forth grass, and herb yielding seed after his kind, and the tree yielding fruit, whose seed was in itself, after his kind: and God saw that it was good. And the evening and the morning were the third day. And God said, Let there be lights in the firmament of the heaven to divide the day from the night; and let them be for signs, and for seasons, and for days, and years: And let them be for lights in the firmament of the heaven to give light upon the earth: and it was so. And God made two great lights; the greater light to rule the day, and the lesser light to rule the night: he made the stars also. And God set them in the firmament of the heaven to give light upon the earth, And to rule over the day and over the night, and to divide the light from the darkness: and God saw that it was good. And the evening and the morning were the fourth day. And God said, Let the waters bring forth abundantly the moving creature that hath life, and fowl that may fly above the earth in the open firmament of heaven. And God created great whales, and every living creature that moveth, which the waters brought forth abundantly, after their kind, and every winged fowl after his kind: and God saw that it was good. And God blessed them, saying, Be fruitful, and multiply, and fill the waters in the seas, and let fowl multiply in the earth. And the evening and the morning were the fifth day. And God said, Let the earth bring forth the living creature after his kind, cattle, and creeping thing, and beast of the earth after his kind: and it was so. And God made the beast of the earth after his kind, and cattle after their kind, and every thing that creepeth upon the earth after his kind: and God saw that it was good. And God said, Let us make man in our image, after our likeness: and let them have dominion over the fish of the sea, and over the fowl of the air, and over the cattle, and over all the earth, and over every creeping thing that creepeth upon the earth. So God created man in his own image, in the image of God created he him; male and female created he them. And God blessed them, and God said unto them, Be fruitful, and multiply, and replenish the earth, and subdue it: and have dominion over the fish of the sea, and over the fowl of the air, and over every living thing that moveth upon the earth. And God said, Behold, I have given you every herb bearing seed, which is upon the face of all the earth, and every tree, in the which is the fruit of a tree yielding seed; to you it shall be for meat. And to every beast of the earth, and to every fowl of the air, and to every thing that creepeth upon the earth, wherein there is life, I have given every green herb for meat: and it was so. And God saw every thing that he had made, and, behold, it was very good. And the evening and the morning were the sixth day. Thus the heavens and the earth were finished, and all the host of them. And on the seventh day God ended his work which he had made; and he rested on the seventh day from all his work which he had made.";
    
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

void generateRandomTweet(Base *map, char **output) {
    char tweet[TWITTER_MAX_SIZE];
    memset(tweet, 0, sizeof(char) * TWITTER_MAX_SIZE);
    
    srand(time(0));
    int mapSize = getMapSize(&map);
    int num = rand() % mapSize;
    
    size_t i = 0;
    Base* base = getNthBase(&map, num);
    strcat(tweet, base->key);
    i += strlen(base->key);
    
    //printf("Random number:%d/%d\n", num, mapSize);
    //printf("Random word:%s\n", base->key);
    
    int nodeSize = getTotalFreq(&map, base->key);
    num = rand() % nodeSize;
    
    Node* node = (Node*) getNodeFromRatio(&base, num);
    // Account for trailing \0 character
    while(i + strlen(node->pair) < (TWITTER_MAX_SIZE - 1)) {
        strcat(tweet, " ");
        strcat(tweet, node->pair);
        // Including space
        i += (strlen(node->pair) + 1);

        //printf("Random key pair:%s - %s %d Tweet Size:%d\n", base->key, node->pair, num, i);
        
        //printf("Getting Base\n");
        base = getBase(&map, node->pair);
        // If there are no key pairs available, it will always randomly choose another base
        while(base == NULL) {
            mapSize = getMapSize(&map);
            num = rand() % mapSize;
            base = getNthBase(&map, num);
        }
        
        nodeSize = getTotalFreq(&map, base->key);
        num = rand() % nodeSize;
        
        node = (Node*) getNodeFromRatio(&base, num);
    }
    
    strcpy(output, tweet);
}

int main(void) {
    Base *words = NULL;
    
    readExample(&words);
    //readBible(&words);
    
    printf("Abs Total Freq: %d\n", getAbsTotalFreq(&words));
    printf("Total Freq: %d for Word: %s\n", getTotalFreq(&words, "the"), "the");
    printf("Total Freq: %d for Word Pair: %s\n", getFreq(&words, "the", "beginning"), "the-beginning");
    printPairs(&words, "the");
    
    printf("%d\n", getFreq(&words, "1:1", "In"));
    printf("%d\n", getFreq(&words, "face", "of"));
    printf("%d\n", getFreq(&words, "the", "waters."));
    
    char output[TWITTER_MAX_SIZE];
    memset(output, 0, sizeof(char) * TWITTER_MAX_SIZE);
    
    // Sets random tweet to output
    generateRandomTweet(words, &output);
    
    printf("Result:%s tweet size:%d\n", output, sizeof(output));
    
    // Open a file for writing.
    FILE *file = fopen("random_tweet.txt", "w");
    
    int results = fputs(output, file);
    fclose(file);
    
    return 0;
}