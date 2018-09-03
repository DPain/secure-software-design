#include "stdio.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

char rot13(char c) {
    if ((c >= 'a' && c < 'n') || (c >= 'A' && c < 'N')) {
        return c + 13;
    } else if ((c >= 'n' && c <= 'z') || (c >= 'N' && c <= 'Z')) {
        return c - 13;
    } else {
        return c;
    }
}

char * translate(char * str, int length) {
    char * result = malloc(sizeof(char) * length);
    for (int i = 0; i < length; i++) {
        //Translating by ROT 13
        result[i] = rot13(str[i]);
    }
    return result;
}

int main(void) {
    char str[BUFFER_SIZE];
    long int * output;
    //Reading input.txt
    FILE * fp = fopen("input.txt", "r");
    if (fp == NULL) {
        printf("File does not exist!\n");
        exit(1);
    } else {
        printf("File exists!\n");
    }

    int i = 0;
    while (fgets(str, BUFFER_SIZE, fp)) {
        printf("line: %s\n", str);
        int size = strlen(str);
        output = malloc(sizeof(long int) * size);

        char * space = strtok(str, " ");
        int processed_len = 0;
        printf("Splitting string \"%s\" into tokens:\n", str);
        while (space != NULL) {
            printf("word: %s\n", space);
            processed_len = strlen(space);
            printf("length: %d\n", processed_len);

            char * dash = strtok(space, "-");
            while (dash != NULL) {
                printf("%s\n", dash);
                output[i] = strtol(dash, NULL, 10);
                dash = strtok(NULL, "-");
                i++;
            }
            space = strtok(space + processed_len + 1, " ");
        }
    }

    int length = i;
    char * text = malloc(sizeof(char) * length);
    for (int j = 0; j < length; j++) {
        text[j] = output[j] - 1 + 'a';
    }
    printf("%s\n", text);

    //Test
    //ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz
    //NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm
    //int length = 52;
    //char* text = malloc(sizeof(char) * length);
    //text = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    printf("%s\n", translate(text, length));
}
