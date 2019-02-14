#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
  // Check for errors in arguments
  if(argc == 1){
    char* msg = "tr2b.c: missing operand\n";
    write(2, msg, strlen(msg));
    exit(1);
  }
  if(argc == 2){
    char* msg = "tr2b.c: missing operand\nTwo strings must be given when translating.\n";
    write(2, msg, strlen(msg));
    exit(1);
  }
  if(argc > 3){
    char* msg = "tr2b.c: extra operand\n";
    write(2, msg, strlen(msg));
    exit(1);
  }

  // Create arrays 'to' and 'from'
  char* from = argv[1];
  char* to = argv[2];

  // Check if operands are the same length or if there are duplicates
  int lengthFrom = strlen(from);
  int lengthTo = strlen(to);
  if(lengthFrom != lengthTo){
    char* msg = "tr2b.c: operands must be the same length.\n";
    write(2, msg, strlen(msg));
    exit(1);
  }
  for(int i=0; i<lengthFrom; i++){
    for(int j=i+1; j<lengthFrom; j++){
      if(from[i] == from[j]){
	char* msg = "tr2b.c: 'from' operand has duplicate byte(s).\n";
	write(2, msg, strlen(msg));
	exit(1);
      }
    }
  }

  // getchar and putchar, change if necessary for every character in stdin 
  char* cur = (char *) malloc(sizeof(char));
  while(1){
    ssize_t numRead = read(0, cur, 1);  // read in character
    if(numRead < 0){	// Check for error
      char* msg = "Error reading input.\n";
      write(2, msg, strlen(msg));
      exit(1);
    }
    if (numRead == 0)	// If its zero, its the end of the file
      break;
	  
    // Look for match
    int index = -1;
    for(int i=0; i<lengthFrom; i++){
      if(*cur == from[i]){
	index = i;
	break;
      }
    }

    ssize_t written;
    if(index == -1)
      written = write(1, cur, 1);
    else{
      char toWrite = to[index];
      written = write(1, &toWrite, 1);
    }
    
    if(written <= 0){	// Check for output error
      char* msg = "Error writing output.\n";
      write(2, msg, strlen(msg));
      exit(1);
    }
  }

  exit(0);
}
