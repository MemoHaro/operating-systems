#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
	char *filename = argv[1];
	struct stat st;
	stat(filename, &st);

	// Checks if file is a directory
	if(S_ISDIR(st.st_mode)) {
		printf("Directory\n");
	}

	// Checks if the user is also the owner of file
	if(getuid() == st.st_uid) {
		printf("Owner\n");
	}
	return 0;
}
