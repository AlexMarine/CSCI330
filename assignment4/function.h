/////////////////////////////////////////////////////////////////////////
//NIU CSCI-330 Fall 2019
//Section Number: 1
//Author: Alex Marine
//zID: z1863905
//Due Date: October 14, 2019
//Porgram Name: function.h
//Purpose of Program:
//	This program builds off of the cat program and allows the user
//	to enter additional commands to alter the way the file is
//	outputted
/////////////////////////////////////////////////////////////////////////


#ifndef FUNCTION_H
#define FUNCTION_H

//libraries included
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

//using standard namespace
using namespace std;

//function prototypes
void binary_rotation(int, char*, int);
void hexadecimal(char*, char*, int);
void caeser_cipher(int, char*, int);
void binary_representation(char*, char*, int);

#endif
