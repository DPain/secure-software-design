#include "stdio.h"

int main(void) {
	
    const char x[] = "CAT";
    printf("%s should be CAT", x);
    int i = 0;
    
    while (x[i] != 0){
    	printf("\n%d was the ascii value of character %d\n", (int) x[i], i);
    	i++;
    }

    return 0;
}
