typedef struct Base {
    char* key;
    struct Node* node;
    struct Base* next;
} Base;

typedef struct Node {
    char* pair;
    int freq;
    struct Node* next;
} Node;

void incrementFreq(Base** map, char* word, char* pair);
Base* getBase(Base** map, char* word);
Base* getNthBase(Base** map, int n);
Node* getNodeFromRatio(Base** base, int n);
int getFreq(Base** map, char* key, char* pair);
int getTotalFreq(Base** map, char* key);
int getAbsTotalFreq(Base** map);
int getMapSize(Base** map);
void printPairs(Base** map, char* key);