#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkForIOError();

int main(int argc, char* argv[]) {
  // Check for errors in arguments
  if(argc == 1){
    fprintf(stderr, "tr2b.c: missing operand\n");
    exit(1);
  }
  if(argc == 2){
    fprintf(stderr, "tr2b.c: missing operand after '%s'\nTwo strings must be given when translating.\n",argv[1]);
    exit(1);
  }
  if(argc > 3){
    fprintf(stderr, "tr2b.c: extra operand '%s'\n", argv[3]);
    exit(1);
  }

  // Create arrays 'to' and 'from'
  char* from = argv[1];
  char* to = argv[2];

  // Check if operands are the same length or if there are duplicates
  int lengthFrom = strlen(from);
  int lengthTo = strlen(to);
  if(lengthFrom != lengthTo){
    fprintf(stderr, "tr2b.c: operands must be the same length.\n");
    exit(1);
  }
  for(int i=0; i<lengthFrom; i++){
    for(int j=i+1; j<lengthFrom; j++){
      if(from[i] == from[j]){
	fprintf(stderr, "tr2b.c: 'from' operand has duplicate byte(s).\n");
	exit(1);
      }
    }
  }

  // getchar and putchar, change if necessary for every character in stdin
  char cur = getchar();
  checkForIOError();
  while(cur != EOF){
    int index = -1;
    for(int i=0; i<lengthFrom; i++){
      if(cur == from[i]){
	index = i;
	break;
      }
    }
    
    if(index == -1)
      putchar(cur);
    else
      putchar(to[index]);
    checkForIOError();

    cur = getchar();
    checkForIOError();
  }

  exit(0);
}





void checkForIOError(){
  if (ferror(stdin) != 0) {
    fprintf(stderr, "Error with I/O!\n");
    exit(1);
  }
}
