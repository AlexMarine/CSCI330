/////////////////////////////////////////////////////////////////////////
//NIU CSCI-330 Fall 2019
//Section Number: 1
//Author: Alex Marine
//zID: z1863905
//Due Date: November 6, 2019
//Porgram Name: pipes.cc
//Purpose of Program:
//	This program simulates the pipe operator found in the terminal.
//	This ois accomplished using pipe, fork, dup, and execvp in the
//	program to allow for two user inputs to send the output of one
//	into the input of another.	
/////////////////////////////////////////////////////////////////////////

//include
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

//using standard namespace
using namespace std;

//main function
int main(int argc, char *argv[])
{
	int pipefd[2];		//for pipe
	int rs, rs2, rs3, rs4;	//return values for pipe, fork, and execvp
	char com1[256];		//command one inputted by user
	char com2[256];		//command two inputted by user
	char* tok1;		//token for first call to strtok	
	char* tok2;		//token for second call to strtok
	
	//while user did not prompt to quit program
	while (com1 != "quit" || com2 != "quit")
	{
		//prompt user
		cout << "Command1: ";
		//get user input for command one
		cin.getline(com1, 256);
		
		//set token one to strtok call
		tok1 = strtok(com1, " ");

		//if user inputted 'quit', exit program
		if (com1[0] == 'q' && com1[1] == 'u' && 
			com1[2] == 'i' && com1[3] == 't') 
		{
			return 0;
		}
		
		//prompt user
		cout <<"Command2: ";
		//get user inputs for command two
		cin.getline(com2, 256);

		//set token two to strtok call
		tok2 = strtok(com2, " ");

		//if user inputted 'quit', exit program
		if (com2[0] == 'q' && com2[1] == 'u' &&
			com2[2] == 'i' && com2[3] == 't')
		{
			return 0;
		}
		
		//call pipe
		rs = pipe(pipefd);
		//if rs < 0, there was an error. exit program
		if (rs < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		
		//call fork
		rs2 = fork();

		//if rs2 < 0, there was an error. exit program
		if (rs2 < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
	
		//child one
		if (rs2 == 0)
		{
			close(1);		//close std input
			dup(pipefd[1]);		//dup write end of pipe to std output
			close(pipefd[0]);	//close read end of pipe
			close(pipefd[1]);	//close qrite end of pipe
			
			//while token one is not null
			while (tok1 != NULL)
			{
				//call execvp, make tok1 executable
				rs3 = execvp(tok1, argv);

				//is rs3 = -1, there was an error. exit program
				if (rs3 == -1)
				{
					perror("execvp of first command");
					exit(rs2);
				}

				//set token to strtok call
				tok1 = strtok(NULL, " ");
			}
		}
		//parent
		else
		{
			//call fork
			rs4 = fork();

			//if rs4 < 0, there was an error. exit program
			if (rs4 < 0)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}

			//child two
			if (rs4 == 0)
			{
				close(0);		//close std output
				dup(pipefd[0]);		//dup read end of pipe to std input
				close(pipefd[1]);	//close write end of pipe
				close(pipefd[0]);	//close read end if pipe
				
				//while tok2 is not null
				while (tok2 != NULL)
				{
					//call execvp, make tok2 executable
					rs3 = execvp(tok2, argv);

					//is rs3 = -1, there was an error. exit program
					if (rs3 == -1)
					{
						perror("execvp of second command");
						exit(rs4);
					}

					//set token to strtok call
					cout << tok2 << endl;
					tok2 = strtok(NULL, " ");
				}
			}
		
			close(pipefd[0]);	//close read and of pipe
			close(pipefd[1]);	//close write end of pipe
			wait(&rs2);		//wait for child one to finish
			wait(&rs4);		//wait for child two to finish
		}
	}

	//end program
	return 0;
}
