#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b);
void checkInputError(void);
void checkOutputError(void);

int main(void) {
    char* curLine = (char *) malloc(sizeof(char));
    char** allLines = (char **) malloc(sizeof(char*));
    char cur = getchar();
    checkInputError();
    
    int iLetter = 0;
    int iLine = 0;
    while(!feof(stdin)){
        curLine[iLetter] = cur;
        curLine = (char*) realloc(curLine, (iLetter+2) * sizeof(char));
        if(curLine == NULL) {
            free(curLine);
            fprintf(stderr, "Error with memory allocation!");
            exit(1);
        }
        iLetter++;
        
        // If we just added a space byte
        if(cur == ' ') {
            allLines[iLine] = curLine;
            allLines = (char**) realloc(allLines, (iLine+2)*sizeof(char*));
            if(allLines == NULL) {
                free(allLines);
                fprintf(stderr, "Error with memory allocation!");
                exit(1);
            }
            iLine++;
            free(curLine);
            curLine = (char*) malloc(sizeof(char));
            iLetter = 0;
            
            do {
                cur = getchar();
                checkInputError();
                if(feof(stdin))
                    break;
            } while (cur == ' ');
            continue;
        }
        
        cur = getchar();
        checkInputError();
        if(feof(stdin)){
            curLine[iLetter] = ' ';
            allLines[iLine] = curLine;
            allLines = (char**) realloc(allLines, (iLine+2)*sizeof(char*));
            if(allLines == NULL) {
                free(allLines);
                fprintf(stderr, "Error with memory allocation!");
                exit(1);
            }
            iLine++;
            free(curLine);
            curLine = (char*) malloc(sizeof(char));
            iLetter = 0;
        }
        
    }
    
    
    
    for(int l=0; l<iLine; l++){
        for(int i=0; allLines[l][i]!=' ';i++){
            putchar(allLines[l][i]);
        }
        free(allLines[l]);
    }
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



