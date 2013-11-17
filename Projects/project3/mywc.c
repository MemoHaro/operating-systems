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
      ++filecount;
      FILE *file = fopen(argv[i], "r");
      // Opened file fine
      if(file) {
	process_file(file);      
	printf(" %s\n", argv[i]);
	fclose(file);
      }
      else {
	fprintf(stderr, "mywc: unable to open %s\n", argv[i]);
	return 1;
      }
    }
  }
  // Read from stdin if we have no files passed.
  if(filecount == 0) {
    process_file(stdin);      
    printf("\n");
  }
  // Need to print total
  if(filecount > 1) {
    // Did not pass flags, print all information
    if(flags == 0x00) {
      printf("%5d %5d %5d", total_lines, total_words, total_bytes);
    }

    if(flags & LINES) {
      printf("%5d", total_lines);    
    }
    if(flags & WORDS) {
      printf("%5d", total_words);
    }
    if(flags & BYTES) {
      printf("%5d", total_bytes);
    }  
    printf(" total\n");
  }
  return 0;
}

// Calculates the counts according to the flags
void process_file(FILE *fp)
{
  int c, prev;
  int lines, words, bytes;
  lines = words = bytes = 0;
  prev = -1;
  while((c = fgetc(fp)) != EOF) {
    // Test if we have a word
    if(isspace(c) && prev > 0 && !isspace(prev)) {
      ++words;
    }
    // Test if we have a line
    if (c == '\n') {
      ++lines;
    }
    // Keep track of previous element
    prev = c;
    // Always increment bytes
    ++bytes;
  }
  // Non empty file, check if we missed one word at the end
  if (bytes > 0) {
    // Character as the last character, count it as a word
    if(!isspace(prev)) {
      ++words;
    }
  }
  // Add the local sums to the global total
  total_lines += lines;
  total_words += words;
  total_bytes += bytes;

  // Did not pass flags, print all information
  if(flags == 0x00) {
    printf("%5d %5d %5d", lines, words, bytes);
  }

  // Flags got passed, handle them seperately
  else {
    if(flags & LINES) {
      printf("%5d", lines);    
    }
    if(flags & WORDS) {
      printf("%5d", words);
    }
    if(flags & BYTES) {
      printf("%5d", bytes);
    }  
  }
  return;
}
