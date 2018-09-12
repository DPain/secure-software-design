#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <bitset>
#include <climits>
#include <cmath>
using namespace std;

int main() {
    int num = 31;
    bitset<5> set = bitset<5>(0);
    
    cout << "number: " << bitset<5>(num) << endl;
    
    char test = 0b11010;
    cout << "test: " << bitset<5>(test ^ (0b11111 & test)) << endl;
    
    int i = 0;
    for(i = 0; i < 32; i++) {
        set = bitset<5>(31);
        cout << "set: " << set << endl;
        int j = 0;
        for(j = 0; j < 5; j++) {
            set = set << 1;
            cout << "set: " << set << endl;
        }
    }
    
    return 0;
}