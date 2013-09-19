
/*** fileaccess.c ***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) 
{
  int errors, k;
  struct stat buf;
  struct passwd *passwd;
  char *p, *file, *home;
  uid_t uid; 
  gid_t gid;
  errors = 0;
  
  passwd = getpwuid(getuid());
  uid = getuid();
  gid = getgid();
  // print the user name, from the passwd struct
  //printf("User: %s\n", passwd->pw_name); 
  // print the users home directory
  //printf("Home: %s\n", passwd->pw_dir);
  // prints the users shell
  //printf("Shell: %s\n", passwd->pw_shell);

  for (k = 1; k < argc; k++) {
    // File is absolute
    if(argv[k][0] == '/') {
      file = argv[k];
      printf("File is absolute\n");
    }
    // File is relative 
    else {
      home = passwd->pw_dir;
      //concat the homedirectory to argv[k]
      printf("File is relative\n");
      printf("Users' home directory: %s\n", home);
      file = malloc(sizeof(home) + 1 + sizeof(argv[k]));
      strcat(file, home);
      strcat(file, "/");
      strcat(file, argv[k]);
      printf("File is now: %s\n", file);
    }
    /* fetch inode information */
    if (stat(argv[k], &buf) == (-1)) {
      fprintf(stderr, "%s: cannot access %s\n",
                       argv[0], argv[k]);
      errors++;
      continue;
    }

    if(argv[k][0] == '/') {
      printf("Absolute, don't need to do anything.\n");
    }

    printf("File: %s - ", argv[k]);
    /* print file permissions */
    if(uid == buf.st_uid) {
      printf("File owner:\n"); 
      if(buf.st_mode & 0400) {
        printf("\tRead permission.\n");
      }
      if(buf.st_mode & 0200) {
        printf("\tWrite permission.\n");
      }
      if(buf.st_mode & 0100) {
        printf("\tExecute permission.\n");
      }
    }
    else if(gid == buf.st_gid) {
      printf("Group:\n");
      if(buf.st_mode & 0040) {
        printf("\tRead permission.\n");
      }
      if(buf.st_mode & 0020) {
        printf("\tWrite permission.\n");
      }
      if(buf.st_mode & 0010) {
        printf("\tExecute permission.\n");
      }

    }
    else {
      printf("Other\n");
      if(buf.st_mode & 0004) {
        printf("\tRead permission.\n");
      }
      if(buf.st_mode & 0002) {
        printf("\tWrite permission.\n");
      }
      if(buf.st_mode & 0001) {
        printf("\tExecute permission.\n");
      }
    }    
  }
  if (errors)
    exit(1);
  else
    exit(0);
}

