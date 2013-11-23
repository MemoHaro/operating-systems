#include <stdio.h>
#include <ctype.h>
// Added
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define LINES 001
#define WORDS 002
#define BYTES 004

short flags = 0;

void process_file(FILE *fp);

int main(int argc, char *argv[])
{
  // keep track of which indices contain files
  int file_index[argc];

  int i, c, filecount;
  
  pid_t pid;
  //int pipefd[2];
  
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
      // For each file, fork the process      
      ++filecount;
      if((pid = fork()) == -1) {
	fprintf(stderr, "Fork error.");
	exit(1);
      }
      // Child
      else if(pid == 0) {
	//	printf("CHILD: pid %d.\n", getpid());
	FILE *file = fopen(argv[i], "r");
	process_file(file);	
	printf(" %s \tPID: %d\n", argv[i], getpid());
	fclose(file);
	exit(0);
      }
      // Parent
      else {
	// Wait for all the children to exit
	while(wait(NULL) > 0);
      }
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
  //total_lines += lines;
  //total_words += words;
  //total_bytes += bytes;

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
