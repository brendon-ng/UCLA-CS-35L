#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b);
int compare(const void *a, const void *b);
void checkInputError(void);
void checkOutputError(void);

int main(void) {
    char** allLines = (char **) malloc(sizeof(char*));
    char cur = getchar();
    checkInputError();
    if(cur == EOF){
        return 0;
    }
    allLines[0] = (char*) malloc(sizeof(char));
    
    int iLetter = 0;
    int iLine = 0;
    while(cur != EOF){
        // If we just added a space byte
        if(cur == ' ') {
            allLines[iLine][iLetter] = ' ';
            if(allLines == NULL) {
                for(int l=0; l<=iLine; l++){
                    free(allLines[l]);
                }
                free(allLines);
                fprintf(stderr, "Error with memory allocation!");
                exit(1);
            }
            
            int breakAgain =0;
            do {
                cur = getchar();
                checkInputError();
                if(cur == EOF){
                    breakAgain = 1;
                    break;
                }
            } while (cur == ' ');
            
            if(breakAgain)
                break;
            
            iLine++;
            allLines[iLine] = (char*) malloc(sizeof(char));
            iLetter = 0;
        }
        else {
            allLines[iLine][iLetter] = cur;
            allLines[iLine] = (char*) realloc(allLines[iLine], (iLetter+2) * sizeof(char));
            if(allLines == NULL) {
                for(int l=0; l<=iLine; l++){
                    free(allLines[l]);
                }
                free(allLines);
                fprintf(stderr, "Error with memory allocation!");
                exit(1);
            }
            iLetter++;
            cur = getchar();
            if (cur == EOF) {
                allLines[iLine][iLetter] = ' ';
                break;
            }
        }
    }
    
    int (* func) (const void *, const void *) = &compare;
    qsort(allLines[0], iLine+1, sizeof(char*), func);
    
    for(int l=0; l<=iLine; l++){
        for(int i=0; allLines[l][i]!='\0';i++){
            putchar(allLines[l][i]);
        }
        free(allLines[l]);
    }
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

int compare(const void *a, const void *b) {
    return frobcmp(*(const char**) a, *(const char**) b);
}


void checkInputError() {
    if (ferror(stdin) != 0) {
        fprintf(stderr, "Error with reading input!");
        exit(1);
    }
}

void checkOutputError() {
    if (ferror(stdin) != 0) {
        fprintf(stderr, "Error with printing output!");
        exit(1);
    }
}



