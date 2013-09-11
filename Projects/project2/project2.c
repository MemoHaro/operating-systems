#include <stdio.h>

int main()
{
  /* Buffer to hold the line input */
  char buf[1024];
  /* Number of lines */
  int count = 0;
  int c;
  while((c = getchar()) != EOF) {
    printf("%c", c);
    count++;
    memset(buf, '\0', 1024);  
   }  

  return 0;
}
