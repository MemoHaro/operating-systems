#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
	int c;
	struct passwd *pw;
	DIR *dp;
	struct dirent *dir;
	if(argc < 2) {
		exit(1);
	}
	pw = getpwuid(getuid());
	// open directory
	if((dp = opendir(argv[1])) == NULL) {
		fprintf(stderr, "cannot open directory.\n");
	}

	// counts how many files in directory
	while((dir = readdir(dp)) != NULL) {
		if(dir->d_ino ==0)
			continue;
		c++;
	}
	printf("There are %d files in %s.\n", c, argv[1]);
	closedir(dp);	
	// Compare user home directory and directory given
	if(strcmp(pw->pw_dir,argv[1]) == 0) {
		printf("%s is %s's home directory\n", pw->pw_dir, pw->pw_name);
	}
	return 0;
}
