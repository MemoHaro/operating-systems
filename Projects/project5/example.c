#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
  DIR *dp;
  struct dirent *dir;
  
  if((dp = opendir(".")) == NULL) {
    fprintf(stderr, "cannot open directory.\n");
    exit(1);
  }

  // Read entries
  while ((dir = readdir(dp)) != NULL) {
    // Skip removed files
    if (dir->d_ino == 0) {
      continue;
    }

    printf("%s\n", dir->d_name);
  }

  closedir(dp);  
  exit(0);
}
