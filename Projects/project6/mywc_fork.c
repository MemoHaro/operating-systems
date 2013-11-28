#include <stdio.h>
#include <ctype.h>
// Added
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define LINES 001
#define WORDS 002
#define BYTES 004

struct count {
  int bytes;
  int words;
  int lines;
};

short flags = 0;

struct count process_file(FILE *fp);

int main(int argc, char *argv[])
{
  // keep track of which indices contain files
  //  int file_index[argc];

  int c;
  //, filecount;
  
  pid_t pid;
  int pipefd[2];  
  // Keep track of local count
  struct count local_count;
  // keep track of total
  //  struct count total;
  
  //  filecount = 0;

  // pipe
  if(pipe(pipefd)) {
    fprintf (stderr, "Pipe failed.\n");
  }

  int i;
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
      //++filecount;
      if((pid = fork()) == -1) {
	fprintf(stderr, "Fork error.");
	exit(1);
      }
      // Child
      else if(pid == 0) {
	// Close up input side, child does not need to read
	close(pipefd[0]);
	// Open up file for reading
	FILE *file = fopen(argv[i], "r");
	// Get the count for each file
	local_count = process_file(file);	
	// Write the struct of totals to the pipe
	write(pipefd[1], &local_count, sizeof(struct count));
	// Write out the name and process id
	printf(" %s \tPID: %d\n", argv[i], getpid());
	fclose(file);	
	exit(0);
      }
      // Parent
      else {	
	// Holds the value of each read
	struct count tmp;	
	// Parent does not need to write
	//close(pipefd[1]);
	// Wait for all the children to exit
	//int i;
	//while(wait(NULL) > 0) {
	wait(NULL);
	  printf("Read %d bytes\n", (int)read(pipefd[0], &tmp, sizeof(struct count)));
	  printf("Blah: %d %d %d\n", tmp.bytes, tmp.words, tmp.lines);
	  //	}

	//for(i = 0; i < filecount; i++) {
	// wait(NULL);
	//}	
	//	printf("Read %d bytes\n", (int)read(pipefd[0], &tmp, sizeof(struct count)));
	//	printf("Blah: %d %d %d\n", tmp.bytes, tmp.words, tmp.lines);
	//	while(wait(NULL) > 0);
	// Read from the pipe
	//	while((i = (int)read(pipefd[0], &tmp, sizeof(struct count))) >= 0) {
	//	  printf("Read %d bytes\n", i);
	//	  printf("Blah: %d %d %d\n", tmp.bytes, tmp.words, tmp.lines);
	//	}
	// Done reading, close up read side
	//	close(pipefd[0]);
	//exit(0);
      }
    }    
  }

  return 0;
}

// Calculates the counts according to the flags
struct count process_file(FILE *fp)
{
  int c, prev;
  //  int lines, words, bytes;
  struct count filecount;
  filecount.lines = 0;
  filecount.words = 0;
  filecount.bytes = 0;
  prev = -1;
  while((c = fgetc(fp)) != EOF) {
    // Test if we have a word
    if(isspace(c) && prev > 0 && !isspace(prev)) {
      ++filecount.words;
    }
    // Test if we have a line
    if (c == '\n') {
      ++filecount.lines;
    }
    // Keep track of previous element
    prev = c;
    // Always increment bytes
    ++filecount.bytes;
  }
  // Non empty file, check if we missed one word at the end
  if (filecount.bytes > 0) {
    // Character as the last character, count it as a word
    if(!isspace(prev)) {
      ++filecount.words;
    }
  }

  // Did not pass flags, print all information
  if(flags == 0x00) {
    printf("%5d %5d %5d", filecount.lines, filecount.words, filecount.bytes);
  }

  // Flags got passed, handle them seperately
  else {
    if(flags & LINES) {
      printf("%5d", filecount.lines);    
    }
    if(flags & WORDS) {
      printf("%5d", filecount.words);
    }
    if(flags & BYTES) {
      printf("%5d", filecount.bytes);
    }  
  }
  return filecount;
}
