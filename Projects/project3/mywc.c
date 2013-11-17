#include <stdio.h>
#include <ctype.h>

#define LINES 0x01
#define WORDS 0x02
#define BYTES 0x04

// Keeps track of the flags
char flags = 0x00;

// Keeps track of total when more than one file
int total_lines = 0;
int total_words = 0;
int total_bytes = 0;


// Prototype for the function that will process files
void process_file(FILE *fp);

int main(int argc, char **argv)
{ 
  int i, c, filecount;
  filecount = 0;
  // iterate through the arguments
  for(i = 1; i < argc; i++) {
    // process arguments that are flags
    if(*argv[i] == '-') {      
      // Iterate through the character in the flags
      // Options w, c, and l are supported.
      while((c = *(++argv[i]))) {		
	switch(c) {
	case 'c':
	  flags |= BYTES;
	  break;
	case 'w':
	  flags |= WORDS;
	  break;
	case 'l':
	  flags |= LINES;
	  break;
	  // Error message if not one of the supported flags
	default:
	  fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], c);
	  return 1;
	}
      }
    }
    else {
      // Read our file
      FILE *file = fopen(argv[i], "r");      
      process_file(file);      
      printf("\t%s\n", argv[i]);
      fclose(file);
    }
    // Read from stdin
    if(filecount == 0) {
      process_file(stdin);      
    }
  }
  return 0;
}

// Calculates the counts according to the flags
void process_file(FILE *fp)
{
  int c, prev;
  int lines, words, bytes;
  lines = words = bytes = 0;
  // just set prev to some non-whitespace character
  prev = 'a';

  while((c = fgetc(fp)) != EOF) {
    if (c == '\n') {
      ++lines;
    }
    // Don't count the words until we hit a non-whitespace character
    else if(isspace(c)) {
      
    }   
    // When we see the next c
    // This is wrong, figure out a better way to count words
    else if(isspace(prev) && !isspace(c)) {
      ++words;
    }   
    else {
      
    }
    // Always increment bytes
    prev = c;
    ++bytes;
  }
  total_lines += lines;
  total_words += words;
  total_bytes += bytes;

  if(flags & LINES) {
    printf("%5d", lines);    
  }
  if(flags & WORDS) {
    printf("%5d", words);
  }
  if(flags & BYTES) {
    printf("%5d", bytes);
  }  

  printf("\n");
  return;
}
