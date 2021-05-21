/////////////////////////////////////////////////////////////////////////
//NIU CSCI-330 Fall 2019
//Section Number: 1
//Author: Alex Marine
//zID: z1863905
//Due Date: October 14, 2019
//Porgram Name: function.cc
//Purpose of Program:
//	This program builds off of the cat program and allows the user
//	to enter additional commands to alter the way the file is
//	outputted
/////////////////////////////////////////////////////////////////////////


//include header file
#include "function.h"

//binary_rotation function definition
void binary_rotation(int shift, char* buffer, int amount_read)
{
	//go through amount of bytes read in
	for (int i = 0; i < amount_read; i++)
	{
		//shift buffer by size of shift
		buffer[i] += shift;
	}

	//line break
	cout << endl;
}

//hexadecimal function defintion
void hexadecimal(char* buffer, char* hex_buffer, int amount_read)
{
	for (int i = 0; i < amount_read; i++)
	{
		unsigned char c = buffer[i];
		
		char hexlut[] = "0123456789abcdef";
		int x = i * 2;
		hex_buffer[x+0] = hexlut[((c & 0xf0) >> 4)];
		hex_buffer[x+1] = hexlut[(c & 0x0f)];


	}
}

//caeser_cipher function definition
void caeser_cipher(int shift, char* buffer, int amount_read)
{
	//go through amount of bytes read in
	for (int i = 0; i < amount_read; i++)
	{
		//if value is lowercase and between a-z
		if(buffer[i] >= 'a' && buffer[i] <= 'z')
		{
			//shift buffer by size of shift
			buffer[i] = ((buffer[i] - 'a' + shift) % 26) + 'a';
		}
		//if value is uppercase and between A-Z
		else if(buffer[i] >= 'A' && buffer[i] <= 'Z')
		{
			//shift buffer by size of shift
			buffer[i] = ((buffer[i] - 'A' + shift) % 26) + 'A';
		}
	}
}

//binary_representation function definition
void binary_representation(char* buffer, char* bin_buffer, int amount_read)
{
	for (int i = 0; i < amount_read; i++)
	{
		unsigned char c = buffer[i];
		int x = i * 8;
		bin_buffer[x+7] = (c & 1) ? '1' : '0';
		bin_buffer[x+6] = (c & 2) ? '1' : '0';
		bin_buffer[x+5] = (c & 4) ? '1' : '0';
		bin_buffer[x+4] = (c & 8) ? '1' : '0';
		bin_buffer[x+3] = (c & 16) ? '1' : '0';
		bin_buffer[x+2] = (c & 32) ? '1' : '0';
		bin_buffer[x+1] = (c & 64) ? '1' : '0';
		bin_buffer[x+0] = (c & 128) ? '1' : '0';
	}
}
