#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int frobcmp(char const * a, char const * b);
int compare(const void *a, const void *b);
void checkForSystemCallError(int status);

int f = 0;

int main(int argc, char* argv[]) {
  // Check for -f flag and argument errors
  if (argc == 2){
    if(strcmp(argv[1], "-f") == 0)
      f = 1;
    else {
      char* msg = "sfrobu.c: invalid option!\n";
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

  char** allLines = (char**) malloc(sizeof(char*));
  char* line;
  int iLine = 0;

  //If it is a regular file
  if(S_ISREG(buffer.st_mode)){
    //allocate enough memory
    line = (char*) malloc(sizeof(char) * fileSize+1);

    //read the whole file
    status = read(0, line, buffer.st_size);
    checkForSystemCallError(status);

    //Count how many lines, divided by spaces
    int lines = 0;
    for(size_t i=0; i < fileSize; i++) {
      if(line[i] == ' ') {
	if(i != 0)
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
	lines++;
	break;
      }
    }

    //Allocate memory for array of lines
    allLines = (char**) realloc(allLines,((lines+1) * sizeof(char*)));

    //Add new line to allLines when there is a space
    int addedLine = 0;
    for(size_t i=0; i<fileSize; i++){
      if(!addedLine && line[i] != ' ') {
	allLines[iLine] = &line[i];
	iLine++;
	addedLine = 1;
      }
      else if (addedLine && line[i] == ' ')
	addedLine = 0;
    }
  }

  
  //Byte by byte read input (for non normal files AND if file grew)
  char* cur = (char*) malloc(sizeof(char));
  status = read(0, cur, 1);
  checkForSystemCallError(status);

  // Ignore leading spaces
  if(status != 0){
    while(status != 0 && *cur == ' '){
      status = read(0, cur, 1);
      checkForSystemCallError(status);
    }
  }

  // Read in char by char
  char* curLine = (char *) malloc(sizeof(char));
  int iLetter = 0;
  while(!feof(stdin) && status > 0){
    // If we just added a space byte
    if(*cur == ' ') {
      curLine[iLetter] = *cur;
      curLine = realloc(curLine, (iLetter + 2) * sizeof(char));
      allLines[iLine] = curLine;
      allLines = (char**) realloc(allLines, (iLine+2) * sizeof(char*));
      iLine++;
      if(curLine == NULL || allLines == NULL) { // check for memory error
        for(int l=0; l<=iLine; l++){
          free(allLines[l]);
        }
        free(allLines);
	free(curLine);
        char* msg = "sfrobu.c: error with memory allocation\n";
        write(2, msg, strlen(msg));
        exit(1);
      }

      // Handle multiple spaces
      int breakAgain =0;
      do {
        status = read(0, cur, 1);
        checkForSystemCallError(status);
        if(feof(stdin) || status == 0){
          breakAgain = 1;
          break;
        }
      } while (*cur == ' ');
            
      if(breakAgain)
        break;
  
      iLetter = 0;
      curLine = NULL;
      curLine = (char*) malloc(sizeof(char));
    }
    else {
      // Regular characters
      curLine[iLetter] = *cur;
      curLine = realloc(curLine, (iLetter + 2) * sizeof(char));
      if(curLine == NULL) {   // Check for memory error
        for(int l=0; l<=iLine; l++){
          free(allLines[l]);
        }
        free(allLines);
	free(curLine);
        char* msg = "sfrobu.c: error with memory allocation\n";
        write(2, msg, strlen(msg));
        exit(1);
      }
      iLetter++;
      status = read(0, cur, 1);
      checkForSystemCallError(status);
      if(feof(stdin) || status == 0){ // check for end of file
	curLine[iLetter] = ' '; 
	allLines[iLine] = curLine;
	allLines = (char**) realloc(allLines, (iLine+2) * sizeof(char*));
	iLine++;
      	if(allLines == NULL) {  // check for memory error
          for(int l=0; l<=iLine; l++){
            free(allLines[l]);
          }
          free(allLines);
          free(curLine);
          char* msg = "sfrobu.c: error with memory allocation\n";
          write(2, msg, strlen(msg));
          exit(1);
        }
	break;
      }
    }
  }
  
  // sort and print
  int (* func) (const void *, const void *) = &compare;
  qsort(allLines, iLine, sizeof(char*), func);

  
  for(size_t l=0; l<iLine; l++){
    size_t i;
    for(i=0; i!=strlen(allLines[l]); i++){
      if(allLines[l][i] == ' '){
	i++;
	break;
      }
    }
    status = write(1, allLines[l], i);
    checkForSystemCallError(status);
  }
  free(allLines);
  free(curLine);
  free(cur);
  return 0;
}


int frobcmp(char const * a, char const * b) {
  if(!f) {
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
  else {
     while(*a != ' ' || *b != ' '){
      if (*a == ' ')
	return -1;
      if (*b == ' ')
	return 1;
      char fa = toupper((unsigned char) (*a ^ 42));
      char fb =	toupper((unsigned char) (*b ^ 42));
      if(fa < fb)
	return -1;
      if(fb < fa)
	return 1;
      a++;
      b++;
    }
    return 0;
  }
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
