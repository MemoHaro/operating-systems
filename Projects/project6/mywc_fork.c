#include <stdio.h>
#include <ctype.h>
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
  int c, filecount;

  pid_t pid;
  int pipefd[2];
  // Keep track of local count
  struct count local_count = {.bytes = 0, .words = 0, .lines = 0};
  // keep track of total
  struct count total_count = {.bytes = 0, .words = 0, .lines = 0};
  filecount = 0;

  char *files[argc];

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
      // File up the array with the file names
      files[filecount++] = argv[i];
    }
  }

  // Read from stdin if we have no files
  if(filecount == 0) {
    process_file(stdin);
    printf("\n");
    exit(0);
  }

  // Iterate over each file to write to pipe
  int k;
  for(k = 0; k < filecount; k++) {
    if((pid = fork()) == -1) {
      fprintf(stderr, "Error while forking.\n");
      exit(1);
    }
    if(pid == 0) {
      FILE *file = fopen(files[k], "r");
      // Get the count for each file
      local_count = process_file(file);
      printf(" %s \tPID: %d\n", files[k], getpid());
      if(write(pipefd[1], &local_count, sizeof(struct count)) == -1) {
	fprintf(stderr, "Error writing to pipe.\n");
      }
      exit(0);
    }
  }

  for(k = 0; k < filecount; k++) {
    if(read(pipefd[0], &local_count, sizeof(struct count)) == -1) {
      fprintf(stderr, "Error reading the pipe.\n");
    }
    total_count.bytes += local_count.bytes;
    total_count.words += local_count.words;
    total_count.lines += local_count.lines;
  }

  // Don't need to print total if just one file
  if(filecount == 1) {
    exit(0);
  }

  // Did not pass flags, print all information
  if(flags == 0) {
    printf("%5d ", total_count.lines);
    printf("%5d ", total_count.words);
    printf("%5d ", total_count.bytes);
  }
  if(flags & LINES) {
    printf("%5d ", total_count.lines);
  }
  if(flags & WORDS) {
    printf("%5d ", total_count.words);
  }
  if(flags & BYTES) {
    printf("%5d ", total_count.bytes);
  }
  printf("total\n");
  return 0;
}

// Calculates the counts according to the flags
struct count process_file(FILE *fp)
{
  int c, prev;
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
  if(flags == 0) {
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
