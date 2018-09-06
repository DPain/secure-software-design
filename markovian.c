#include <glib.h>
<<<<<<< HEAD
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define BUFFER_SIZE 1024
#define SKIP_FIRST_LINE 13
#define MAX_READ_LINE 2

int isDigitsPunct(const char *str) {
    while (*str) {
        if (isdigit(*str) == 0 && ispunct(*str) == 0) {
            return 0;
        }
        str++;
    }
    return 1;
}
=======
#include <stdio.h>
>>>>>>> a1d96cb891c8faf1800d081ee89d605cdf004036

int main(void) {
    GHashTable *words = g_hash_table_new(g_str_hash, g_str_equal);
    
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
    char *prevWord;
    while (fgets(str, BUFFER_SIZE, fp) && line_num < MAX_READ_LINE) {
        printf("line: %s\n", str);
        int size = strlen(str);

        printf("Splitting string \"%s\" into words:\n", str);
        char *word = strtok(str, " ");
        while (word != NULL) {
            if(!isDigitsPunct(word)) {
                printf("word: %s\n", word);
            }
            
            if(prevWord != NULL) {
                // Probability distribution job here
                if(g_hash_table_contains(words, prevWord)) {
                    //int count = g_hash_table_lookup(g_hash_table_lookup(words, prevWord), word);
                } else {
                    //(words, prevWord, (gpointer) g_hash_table_lookup(words, prevWord), word);
                }
            }
            
            prevWord = word;
            word = strtok(NULL, " ");
        }
        line_num++;
    }
    
    /**
    
    
    GHashTable *prob_dist1 = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(prob_dist1, "Virginia", GINT_TO_POINTER(20));
    g_hash_table_insert(prob_dist1, "Texas", GINT_TO_POINTER(33));
    g_hash_table_insert(prob_dist1, "Ohio", GINT_TO_POINTER(30));
    g_hash_table_insert(prob_dist1, "Delaware", GINT_TO_POINTER(17));
    
    GHashTable *prob_dist2 = g_hash_table_new(g_str_hash, g_str_equal);
    g_hash_table_insert(prob_dist2, "Virginia", GINT_TO_POINTER(10));
    g_hash_table_insert(prob_dist2, "Texas", GINT_TO_POINTER(50));
    g_hash_table_insert(prob_dist2, "Ohio", GINT_TO_POINTER(40));
    
    g_hash_table_destroy(prob_dist1);
    g_hash_table_destroy(prob_dist2);
    g_hash_table_destroy(words);
    */
    
    return 0;
}