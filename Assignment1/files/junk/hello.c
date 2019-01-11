#include <stdio.h>
int
main (void)
{
  char n = '\n', b = '\\', q = '"';
  char const *p = "#include <stdio.h>%cint%cmain (void)%c{%c  char n = '%cn', b = '%c%c', q = '%c';%c  char const *p = %c%s%c;%c  printf (p, n, n, n, n, b, b, b, q, n, q, p, q, n, n, n, n);%c  return 0;%c}%c";
  printf (p, n, n, n, n, b, b, b, q, n, q, p, q, n, n, n, n);
  return 0;
}
