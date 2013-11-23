#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>

void print_dir(char *d);

int main(int argc, char **argv)
{
  // One file passed
  if(argc == 2) {
    print_dir(argv[1]);
  }
  // No files passed, use cwd
  else if(argc == 1) {
    print_dir(".");
  }
  else {
    fprintf(stderr, "lsdir: too many files.\n");
    exit(1);
  }
  return 0;
}

// Initial call that calls the recursive _print_dir
void print_dir(char *d)
{
  DIR *dp;
  struct dirent *dir;
  if ((dp = opendir(d)) == NULL) {
    fprintf(stderr, "lsdir: cannot open directory %s.\n", d);
    exit(1);
  }
  while (dir = readdir(dp)) {
    if(dir->d_ino == 0) continue;
    
    // Recursively call print_dir on directories   
    if((dp = opendir(dir->d_name)) != NULL) {
      if (dir->d_name == "." || dir->d_name == "..") break;
      // Print name of directory
      printf("%s\n", dir->d_name);
      // Call our print_dir function
      print_dir(dir->d_name);
      closedir(dp);
    }
  }  
  closedir(dp);
}


