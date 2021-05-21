/////////////////////////////////////////////////////////////////////////
//NIU CSCI-330 Fall 2019
//Section Number: 1
//Author: Alex Marine
//zID: z1863905
//Due Date: October 14, 2019
//Porgram Name: dog.cc
//Purpose of Program:
//	This program builds off of the cat program and allows the user
//	to enter additional commands to alter the way the file is
//	outputted
/////////////////////////////////////////////////////////////////////////


//include header file
#include "function.h"

//main function includes argc and *argv[]
int main(int argc, char *argv[])
{
	//char array buffer with length of argc
	int buffsize = 1024;	//size of buffer
	ssize_t nr;		//read in bytes from file
	int opt;		//command line options selected
	int s_num = 0;		//integer for size of buffer
	int n_num = 0;		//integer for number of bytes read
	int c_num = 0;		//integer for caeser cipher
	int r_num = 0;		//integer for binary rotation
	bool caeser = false;	//caeser cipher set to false
	bool rotation = false;	//binary rotation set to false
	bool hex = false;	//hexadecimal set to false
	bool binary = false;	//binary representation to false
	
	//while getopt gets command line options
	while ((opt = getopt(argc, argv, "s:n:c:r:xb")) != -1)
	{
		//switch for opt variable
		switch (opt)
		{
			case 's':	//case for -s command
				s_num = atoi(optarg);	//set s_num to integer
				buffsize = s_num;	//set buffer to s_num
				break;			//break case
			case 'n':	//case for -n command
				n_num = atoi(optarg);	//set n_num to integer
				break;			//break case
			case 'c':	//case for -c command
				c_num = atoi(optarg);	//set c_num to integer
				caeser = true;		//set caeser to true
				break;			//break case
			case 'r':	//case for -r command
				r_num = atoi(optarg);	//set r_num to integer
				rotation = true;	//set rotation to true
				break;			//break cae
			case 'x':	//case for -x command
				hex = true;		//set hex to true
				break;			//break case
			case 'b':	//case for -b command
				binary = true;		//set binary to true
				break;			//break case
			default:	//case for default value
				break;			//break case
		}
	}
	
	//if both binary rotation and caeser cipher activated
	if (rotation == true && caeser == true)
	{
		//explain error to user
		cerr << "Binary Rotation and Caeser Cipher can not both be applied." << endl;
		cerr << "Program will now close." << endl;

		//end program
		exit(1);
	}
	//if both binart representation and hexadecimal representation activated
	if (binary == true && hex == true)
	{
		//explain error tos user
		cerr << "Binary Representation and Hexadecimal Represenation can not both be applied." << endl;
		cerr << "Program will now close." << endl;

		//end program
		exit(1);
	}
	
	//variable declaration
	char buffer[buffsize];			//buffer with size buffsize
	char hex_buffer[(buffsize * 2)];	//buffsize for hex_buffer is 2 times larger than normal
	char bin_buffer[(buffsize * 8)];	//buffsize for bin_buffer is 8 times larger than normal

	//go through optind and open filed inputted
	for (int i = optind; i < argc; i++)
	{
		//open files with read access only
		int fd = open(argv[i], O_RDWR);
		
		//if file doesn't open, out put error
		if (fd == -1)
		{
			//error occured in open function call, exit program
			perror("open");
			exit(1);
		}
		
		//if number of bytes read was altered
		if (n_num != 0)
		{
			//read file with n_num bytes read in
			nr = read(fd, buffer, n_num);
			
			if (caeser == true)	//if -c command was enterd
			{
				//call caeser_cipher function
				caeser_cipher(c_num, buffer, buffsize);
			}
			if (rotation == true)	//if -r command was entered
			{
				//call binary_rotation functiom
				binary_rotation(r_num, buffer, buffsize);
			}
			if (hex == true)	//if -x command was entered
			{
				//call hexadecimal function
				hexadecimal(buffer, hex_buffer, buffsize);

				//write to stdout
				write(1, hex_buffer, (buffsize * 2));

				//end program
				return 0;
			}
			if (binary == true)	//if -b command was entered
			{
				//call binary_representation function
				binary_representation(buffer, bin_buffer, buffsize);

				//write to stdout
				write(1, bin_buffer, (buffsize * 8));

				//end program
				return 0;
			}
			
			//write to stdout
			write(1, buffer, nr);
			cout << endl;	//line break
		}
		else	//if number of bytes read was not altered
		{	
			do	//do while there are still bytes being read in
			{
				//read in files
				nr = read(fd, buffer, buffsize);
				
				
				if (caeser == true)	//if -c command was entered
				{
					//call caeser_cipher function
					caeser_cipher(c_num, buffer, buffsize);
				}
				if (rotation == true)	//if -r was entered
				{
					//call binary_rotation was entered
					binary_rotation(r_num, buffer, buffsize);
				}
				if (hex == true)	//if -x command was entered
				{
					//call hexadecimal function
					hexadecimal(buffer, hex_buffer, buffsize);

					//write to stdout
					write(1, hex_buffer, (buffsize * 2));

					//end program
					return 0;
				}
				if (binary == true)	//if -b command was entered
				{
					//call binary_representation function
					binary_representation(buffer, bin_buffer, buffsize);

					//write to stdout
					write(1, bin_buffer, (buffsize * 8));

					//close program
					return 0;
				}
				
				//write to std out
				write(1, buffer, nr);

			} while (nr != 0);	//if bytes are still being read, do again
		}
	}	

	//close files
	int close(int fd);

	//close program
	return 0;
}
