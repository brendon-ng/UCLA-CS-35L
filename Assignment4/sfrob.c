#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b);

int main(void) {
    char** allLines = (char **) malloc(sizeof(char));
    char* curLine = (char *) malloc(sizeof(char));
    char cur = getchar();
    
    curLine[0] = cur;
    
    
    
    printf("%c", curLine[0]);
    
    free(curLine);
    free(allLines);
    return 0;
}


int frobcmp(char const * a, char const * b) {
    while (*a == *b){
        if (*a == ' ')
            return 0;
        a++;
        b++;
    }
    if ( (*a ^ 42) > (*b ^ 42) )
        return 1;
    else
        return -1;
}



