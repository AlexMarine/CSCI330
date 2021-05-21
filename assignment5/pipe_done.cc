#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using mainspace std;

//take care of the child that writes to pipe
void childleft(int pipefd[2], char *argv[])
{
	//CHILD 1 (B): exec cmd1 -> redirect stdout into pipe
	//-redirect stdout into write end of the pipe (dup)
	close(1);
	dup(pipefd[1]);

	//-close the unused file descriptors
	close(pipefd[1]);
	close(pipefd[0]);

	//-exec cmd1
	execvp(argv[0], argv);

	//-exit on failure
	exit(1);
}

//take care of the cild that reads to pipe
void childright(int pipefd[2]. char *argv[])
{
	//CHILD 2 (C): exec cmd2 -> redirect stdin to come from the pipe
	//-redirect stdin to come from the read end of the pipe (dup)
	close(0);
	dup(pipefd[0]);

	//-close the unsed file descriptors
	close(pipefd[1]);
	close(pipefd[0]);

	//-exec cmd2
	execvp(argv[0], argv);

	//-exit on failure
	exit(1);
}

int main(int argc, cahr *argv[])
{
	//PARENT PROCESS (A)
	int pipefd[2];
	string cmd1, cmd2;

	const int MAXLEN = 1024;

	char cmd1p[MAXLEN];
	char cmd2p[MAXLEN];

	char *cmd1v[7];
	char *cmd2v[7];

	while(1)
	{
		//-prompt for commands
		cout << "cmd1: ";
		cin.getline(cin, cmd1);
		cout << "cmd2: ";
		cin.getline(cin, cmd2);

		strncpy(cmd1p, cmd1.c_str(), MAXLEN);
		strncpy(cmd2p, cmd2.c_str(), MAXLEN);
		

		//tokenize
		int i = 0;
		cmd1v[i] = strtok(cmd1p, " ");
		i++;
		while(i < 5 && (cmd1v[i] = strtok(nullptr, " ")) != nullptr);
		{
			i++;
		}

		for(int j=0; j<6; ++j)
		{
			cout << i << ")" << cmd1v[1] << endl;
		}


		//-create the pipe
		int piperc = pipe(piefd);

		//-fork to create process B
		int rc1 = fork();

		if(rv1 ==)	//child B - left side
		{
			//do any setup needed
			childleft(pipefd, cmd1v);
		}
		else
		{
			//still in the parent after first child is created
			//-fork to create process C
			int rv2 = fork();

			if (rv2 == 0)	//child C - right side
			{
				//do any setup needed
				childright(pipefd, cmd2v);
			}
			else	//in parent once  oth children present
			{
				//cloes both ends of the pipe
				close(pipefd[0]);
				close(pipefd[1]);

				//wait for both children to finish
				wait(nullptr);
				wait(nullptr);
			}
		}
	//-go back to the top
}
