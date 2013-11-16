#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

void print_file(FILE *fp);

int main(int argc, char *argv[])
{
  // Read the arguments as files
  if(argc > 1) {
    // Iterate over the files passed in
    FILE *argfp;      
    int i;
    for(i = 1; i < argc; i++) {     
      // Read the file
      if((argfp = fopen(argv[i],"r"))) {
	// Print a header for each file
	printf("=================================\n");
	printf("FILE: %s\n", argv[i]);
	printf("=================================\n");
	// Print the file contents with line numbers
	print_file(argfp);
      }
      // Cannot open file
      else {	
	// Build a message and report error
	char msg[50];
	sprintf(msg, "Cannot open file %s\n", argv[i]);
	perror(msg);
	exit(-1);
      }

    }
  }
  // Read from stdin
  else {
    print_file(stdin);
  }

  exit(0);
}

// Prints the contents of a file pointer with line numbers
void print_file(FILE *fp)
{
  // Current character
  int c; 
  // Line number
  int i = 1;
  // Flag to see if we are at a newline
  int newline = 1;
  while ((c = getc(fp)) != EOF) {    
    // We are at the beginning of the line, print the line number
    if(newline) {
      printf("%d\t", i++);
    }
    // Hit the end of the line, set the flag to true
    if(c == '\n') {
      newline = 1;
    } 
    // Not at the end of the line, set the flag to false
    else {
      newline = 0;
    }
    // Write the character to stdout
    putc(c, stdout);    
  }  
  return;
}
