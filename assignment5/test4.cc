#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
	int des_p[2];
	
	if(pipe(des_p) == -1)
	{
		perror("pipe");
		exit(1);
	}

	if (fork() == 0)
	{
		close(1);
		dup(des_p[1]);
		close(des_p[0]);
		close(des_p[1]);

		const char* prog1[] = {"ls", "-l", 0};

		execvp(prog1[0], argv);
		perror("execvp");
		exit(1);
	}

	if (fork() == 0)
	{
		close(0);
		dup(des_p[0]);
		close(des_p[1]);
		close(des_p[0]);

		const char* prog2[] = {"wc", "-l", 0};

		execvp(prog2[0], argv);
		perror("execvp");
		exit(1);
	}

	close(des_p[0]);
	close(des_p[1]);
	wait(0);
	wait(0);
	
	return 0;
}	
