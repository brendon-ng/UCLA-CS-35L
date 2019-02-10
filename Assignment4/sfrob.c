#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const * a, char const * b);





int frobcomp(char const * a, char const * b) {
  while (*a == *b){
    if (*a == ' ')
      return 0;
    a++;
    b++;
  }
  if( (*a ^ 42) > (*b ^ 42) )
    return 1;
  else
    return -1;
}
