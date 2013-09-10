
/*** fileaccess.c ***/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

/* fileaccess file ...		*/
/* print info on access modes	*/
/*				*/

main(int argc, char *argv[]) 
{
  int errors, k, perm;
  struct stat buf;
  struct passwd *passwd;
  char *p;
  errors = 0;

  // getuid to get the user id
  printf("UID: %d\n", getuid());
  
  // getpwduid(uid_t uid) gets the passwd struct, see man pwd.h for fields
  passwd = getpwuid(getuid());
  // print the user name, from the passwd struct
  printf("User: %s\n", passwd->pw_name); 
  // print the users home directory
  printf("Home: %s\n", passwd->pw_dir);

  for (k = 1; k < argc; k++) {
    /* fetch inode information */
    if (stat(argv[k], &buf) == (-1)) {
      fprintf(stderr, "%s: cannot access %s\n",
                       argv[0], argv[k]);
      errors++;
      continue;
    }
    /* print file permissions */
        
    printf("File Owner: %d\n", buf.st_uid);
    printf("Group: %d\n", buf.st_gid);
    if (buf.st_mode & 0400)
      printf("read\n");
    else 
      printf("no read\n");   

  }
  if (errors)
    exit(1);
  else
    exit(0);
}


