#include "distribution.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void incrementFreq(Base** map, char* word, char* pair) {
    Node* base = (Node*) getNode(&*map, word);
    if(base != NULL) {
        // An entry exists in the Hash Table
        while(base->next != NULL && strcmp(base->pair, pair) != 0) {
            base = base->next;
        }
        if(strcmp(base->pair, pair) == 0) {
            base->freq++;
        } else {
            Node* node = (Node*) malloc(sizeof(Node));
            node->pair = strdup(pair);
            node->freq = 1;
            node->next = NULL;
            
            base->next = node;
            
            printf("Adding to Existing Node [key:\"%s\" pair:\"%s\"]\n", word, node->pair);
        }
    } else {
        // No word pair does not exist in the Hash Table
        Node* node = (Node*) malloc(sizeof(Node));
        node->pair = strdup(pair);
        node->freq = 1;
        node->next = NULL;
        
        printf("Adding to New Node [key:\"%s\" pair:\"%s\"]\n", word, node->pair);
        char* key = strdup(word);
        
        Base* newBase = (Base*) malloc(sizeof(Base));
        newBase->key = strdup(key);
        newBase->node = node;
        newBase->next = NULL;
            
        if(*map == NULL) {
            *map = newBase;
        } else {
            Base* temp = *map;
            while(temp->next != NULL) {
                temp = temp->next;
            }
            
            temp->next = newBase;
        }
    }
}

Node* getNode(Base** map, char* word) {
    Base* temp = *map;
    while(temp != NULL) {
        if(strcmp(temp->key, word) == 0) {
            return temp->node;
        } else {
            temp = temp->next;
        }
    }
    return NULL;
}

int getFreq(Base** map, char* key, char* pair) {
    Base* tempBase = *map;
    while(tempBase != NULL) {
        if(strcmp(tempBase->key, key) == 0) {
            Node* tempNode = tempBase->node;
            while(tempNode != NULL) {
                if(strcmp(tempNode->pair, pair) == 0) {
                    return tempNode->freq;
                }
                tempNode = tempNode->next;
            }
        }
        tempBase = tempBase->next;
    }
    return 0;
}

int getTotalFreq(Base** map) {
    int sum = 0;
    
    Base* tempBase = *map;
    
    while(tempBase != NULL) {
        Node* tempNode = tempBase->node;
        //printf("%s\n", tempBase->key);
        printf("[Key:%s , Pair:%s , Freq:%d]\n", tempBase->key, tempNode->pair, tempNode->freq);
        while(tempNode != NULL) {
            sum += tempNode->freq;
            tempNode = tempNode->next;
        }
        tempBase = tempBase->next;
    }
    
    return sum;
}