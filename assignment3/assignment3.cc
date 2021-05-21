/////////////////////////////////////////////////////////////////////////
//NIU CSCI-330 Fall 2019
//Section Number: 1
//Author: Alex Marine
//zID: z1863905
//Due Date: September 27, 2019
//Porgram Name: assignment3.cc
//Purpose of Program: This program implements the behavior of the cat
//	command, as it takes a list of files, and then it otuputs
//	the contents of each file in the order they were supplied.
/////////////////////////////////////////////////////////////////////////

//libraries included
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//using standard namespace
using namespace std;

//main function includes argc and *argv[]
int main(int argc, char *argv[])
{
	//char array buffer with length of argc
	char buffer[2048];

	//for loop that goes through 
	for (int i = 1; i < argc; ++i) 
	{
		//if argv is named '-', don't open file, otherwise contine
		if (argv[i] == "-")
		{
			//inform user
			cout << "File '-' will not be opened." << endl;
		}
		else
		{
			//open files with read access only
			int fd = open(argv[i], O_RDONLY);

			//if file doesn't open, out put error
			if (fd == -1)
			{
				//error occured in open function call
				perror("open");
				exit(1);
			}
		
		
			//read contents of files
			ssize_t nr = read(fd, buffer, 2048);

			//for loop goes through each file and outputs their contents
			for (int i = 0; i < nr; i++)
			{
				if (nr == -1)
				{
					perror("read");
					exit(2);
				}

				//output content of each file read
				cout<<buffer[i];
			}
	
			//close files
			int close(int fd);
		}

	}
	
	//line break
	cout<<endl;

	//close program
	return 0;
}
