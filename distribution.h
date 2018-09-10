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
Node* getNode(Base** map, char* word);
int getFreq(Base** map, char* key, char* pair);
void calcTotalFreq(const char* key, Node* value, int* sum);
int getTotalFreq(Base** map);