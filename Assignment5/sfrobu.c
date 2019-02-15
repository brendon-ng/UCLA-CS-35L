#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int frobcmp(char const * a, char const * b);
int compare(const void *a, const void *b);
void checkForSystemCallError(int status);
void checkInputError(void);
void checkOutputError(void);

int main(void) {
  int f = 0;
  int regularFile = 0;
  if (argc == 2){
    if(strcmp(argv[1], "-f") == 0)
      f = 1;
    else {
      char* msg = "sfrobu.c: invalid option!";
      write(2, msg, strlen(msg));
      exit(1);
    }
  }
  else if (argc > 2){
    char* msg = "sfrobu.c: extra operand\n";
    write(2, msg, strlen(msg));
    exit(1);
  }

  struct stat buffer;
  int status = fstat(0, &buffer);
  checkForSystemCallError(status);

  size_t fileSize = buffer.st_size;

  char** allLines;
  char* line;
  int iLine = 0;

  //If it is a regular file
  if(S_ISREG(buffer.st_mode)){
    line = (char*) malloc(sizeof(char) * fileSize);
    status = read(0, line, buffer.st_size+1);
    checkForSystemCallError(status);

    int lines = 0;
    for(size_t i=0; i < fileSize; i++) {
      if(i==0 && line[0] != ' ')
	lines++;

      if(line[i] == ' ') {
	lines++;
	while(i<fileSize-1 && line[i+1] == ' ')
	  i++;
      }
      
      if(i == fileSize-1 && line[i] != ' ') {
	line = realloc(line, sizeof(char) * (fileSize + 2));
	if(line == NULL){
	  char* msg = "sfrobu.c: memory allocation error\n";
	  write(2, msg, strlen(msg));
	  exit(1);
	}
	line[fileSize] = ' ';
	fileSize++;
	break;
      }
    }

    allLines = (char**) malloc(lines * sizeof(char*));

    int addedLine = 0;
    for(size_t i=0; i<fileSize; i++){
      if(!addedLine && line[i] != ' ') {
	allLines[iLine] = &line[i];
	iLine++;
	addLine = 1;
      }
      else if (addedLine && line[i] == ' ')
	addedLine = 0;
    }
  }

  
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
            
            allLines = (char**) realloc(allLines, (iLine+2) * sizeof(char*));
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
    qsort(allLines, iLine+1, sizeof(char*), func);
    
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

void checkForSystemCallError(int status) {
  if(status < 0) {
    char* msg = "sfrobu.c: system call error.\n";
    write(2, msg, strlen(msg));
    exit(1);
  }
}
