#!/bin/bash

#################################################################
#			NIU CSCI-330 FALL 2019			#
#								#
#	Section Number		1				#
#	Author:			Alex Marine			#
#	zID:			z1863905			#
#	Due Date:		November 18, 2019		#
#	Program Name:		z1863905db.sh			#
#								#
#	Purpose of Program					#
#		This program is shell script that allows the 	#
#		user to create a database and put information	#
#		in said database. In can be run in interactive	#
#		mode as well as taking	command line parameters.#
#################################################################

#new function definition
new()
{
	#variable declaration
	filename="null"
	label="null"
	choice="null"

	#prompt user for the filename of the database
	read -p "What would you like to name the file? " filename

	#ask user if they would like to put a label in the database
	read -p "Would you like to put a label in the database? (y/n) " choice

	if [ $choice == y ]; then

		#prompt the user for the name of the label
		read -p "What would you like the label to be? " label

		#put the label in the databse
		echo "$label" >> $filename

		#inform the user that the database was created
		echo "New database created"

	elif [ $choice == n ]; then

		#make the label for the database "Untitled Database
		echo "Untitled database" >> $filename

		#inform the user that the database was created
		echo "New database created"

	#if an incorrect input was entered
	else
			
		#inform user that they made an invalid inpit
		echo "ERROR: INVALID INPUT"
		
	fi	

	#new line
	echo
}

#add function definition
add()
{
	#variable declaration
	filename="null"
	make="null"
	model="null"
	year="null"
	color="null"

	#prompt user for filename to add to
	read -p "What database would you like to add to? " filename

	#prompt user for make of car
	read -p "What is the make of the car? " make

	#prompt user for model of car
	read -p "What is the model of the car? " model

	#prompt user for the year of the car
	read -p "What is the year of the car? " year

	#if year is greater than 1870 and less than 2025
	if [[ $year -gt 1870 ]] && [[ $year -lt 2025 ]]; then

		#prompt user for the color of the car
		read -p "What is the color of the car? " color

		#put records in database
		echo "$make, $model, $year, $color" >> $filename

		#inform user that the records were added to the database
		echo "Successfully added a record to the database"

	#if year is less than 1870 or greater than 2025
	else

		#inform user that the year can not be lower than 1870 or higher than 2025
		echo "ERROR: YEAR CAN NOT BE LOWER THAN 1870 OR GREATER THAN 2025"
	
	fi

	#new line
	echo
}

#show function definition
show()
{
	#variable declaration
	filename="null"
	howmuch="null"
	sing="null"
	r1="null"
	r2="null"

	#prompt user for filename to show
	read -p "What database would you like to display? " filename

	#prompt user for how much they want to see
	read -p "How much would you like to see? (all/single/range) " howmuch

	#if howmuch is equal to all
	if [ $howmuch == all ]; then

		#new line
		echo

		#output all records in database
		cat $filename

	#if howmuch is equal to single
	elif [ $howmuch == single ]; then

		#prompt user for line to show
		read -p "What record line would you like to display? " sing

		#new line
		echo

		#add 1 to sing
		sing=$((sing + 1))

		#output contents of line scpecified in database
		sed -n -e "$sing p" $filename

	#if howmuch is equal to range
	elif [ $howmuch == range ]; then

		#prompt user for the bottom range to show
		read -p "What is the lower bound you would like to display? " r1

		#prompt useer for the top range to show
		read -p "What is the upper bound you would like to display? " r2

		#new line
		echo

		#add 1 to r1 and r2
		r1=$((r1 + 1))
		r2=$((r2 + 1))

		#output contents of range in database
		sed -n -e "$r1,$r2 p" $filename

	#if an incorrect input was entered
	else

		#inform user that they made an invalid input
		echo "ERROR: INVALID INPUT"

	#end if loop
	fi

	#new line
	echo
}

#delete function definition
delete()
{
	#variable declaration
	filename="null"
	howmuch="null"
	sing="null"
	r1="null"
	r2="null"
	tmp="null"

	#prompt user for filename to delete
	read -p "What database would you like to delete from? " filename

	#prompt user for how much they want to delete
	read -p "How much would you like to delete? (all/single/range) " howmuch

	#if howmuch equals all
	if [ $howmuch == all ]; then

		#delete all contents in database besides the label
		sed '1! d' $filename > $tmp

		#move data from tmp to filename
		mv $tmp $filename

		#inform user that all lines were deleted
		echo "All records in database deleted"

	#if howmuch equals single
	elif [ $howmuch == single ]; then

		#prompt user for line to delete from
		read -p "What record line would you like to delete from? " sing

		#add 1 to sing
		sing=$((sing + 1))

		#delete line specified in database and store in tmp
		sed "${sing}d" $filename > $tmp

		#move data from tmp to filename
		mv $tmp $filename

		#inform user that a single line was deleted
		echo "Single line deleted in database"

		

	#if howmuch equals range
	elif [ $range == range ]; then

		#prompt user for the bottom range to delete
		read -p "What is the lower bound you would like to delete from? " r1

		#prompt user for the top range to delete
		read -p "What is the upper bound you would like to delete from? " r2

		#add 1 to r1 and r2
		r1=$((r1 + 1))
		r2=$((r2 + 1))

		#delete range specified in database and store in tmp
		sed "${r1},${r2} d" $filename > $tmp

		#moce data from tmp to filename
		mv $tmp $filename

		#inform user that all lines in range were deleted
		echo "All lines in range deleted in database"

	#if an incorrect input was entered
	else

		#inform user that they made an invalid input
		echo "ERROR: INVALID INPUT"
			
	fi

	#new line
	echo
}

#variable declaration
com='null'
tmp='tmp'

#if there is no command line parameters
if [[ $1 == "" ]]; then

	#repeats until user enters quit
	while [ $com != quit ]; do

		#prompt user to enter command
		echo "new: create new database file"
		echo "add: add a record to a database"
		echo "show: show record(s) found in a database"
		echo "delete: delete record(s) found in a database"
		echo "quit: exit program"
		read -p "What would you like to do? " com

		#new line
		echo
	
		#if com equals new
		if [ $com == new ]; then
	
			#call new function
			new
	
		#if com equals add
		elif [ $com == add ]; then
	
			#call add function
			add
	
		#if com equals show
		elif [ $com == show ]; then
	
			#call show function
			show
	
		#if com equals delete
		elif [ $com == delete ]; then
	
			#call delete function
			delete
	
		#if com equals quit
		elif [ $com == quit ]; then
	
			#inform user that the program will end
			echo "The program will now end"
	
			#ecit program
			exit 1;
	
		#if com equals something else
		else
	
			#inform user that they made an incorrect input
			echo "ERROR: INVALID INPUT"
	
		#end if loop
		fi

	#end while loop
	done

#if there is a command line parameter
else
	#if user entered new as command
	if [[ $1 == new ]]; then

		#if paramater 2 is empty
		if [[ $2 == "" ]]; then
		
			#inform user that no filename was entered
			echo "ERROR: NO FILENAME SPECIFIED"

		#if paramter 4 is not empty
		elif [[ $4 != "" ]]; then

			#inform user that there were too many paramters filled
			echo "ERROR: MORE THAN TWO PARAMETERS SPECIFIED"

		#if paramter 3 is empty
		elif [[ $3 == "" ]]; then

			#set paramter 2 to the name of the datavase text file
			db=$2

			#make paramter 2 the label in the text file named paramter 2
			echo "Untitled database" >> $db

			#inform user that database was created
			echo "New database created"

		#if paramter 3 is not empty
		elif [[ $3 != "" ]]; then

			#set paramter 2 to the name of the database text file
			db=$2

			#make parameter 3 the label in the text file named parameter 1
			echo "$3" >> $db

			#inform user that database was created
			echo "New database created"

		#if an incorrect input was entered
		else
			
			#inform user that they made an invalid inpit
			echo "ERROR: INVALID INPUT"
		
		fi			

	#if user entered add as command
	elif [[ $1 == add ]]; then

		#if parameter 6 is empty
		if [[ $6 == "" ]]; then

			#inform user that color was not specified
			echo "ERROR: NOT ALL PARAMETERS SPECIFIED"

		#if paramater 5 is not between 1870 and 2025
		elif [[ ! $5 -gt 1870 ]] && [[ ! $5 -gt 2025 ]]; then

			#inform user that the year was not between 1870 and 2025
			echo "ERROR: YEAR NOT BETWEEN 1870 AND 2025"

		#if paramter 7 is not empty
		elif [[ $7 != "" ]]; then

			#inform the user that there were too many parameters filled
			echo "ERROR: TOO MANY PARAMETERS SPECIFIED"
		
		#if all paramters were filled
		else
		
			#insert record into database	
			echo "$3, $4, $5, $6" >> $2

			#inform user that the information was added to the database
			echo "Successfully added a record to the database"

		#end if loop
		fi

	#if user entered show as command
	elif [[ $1 == show ]]; then

		#if parameter 3 is empty
		if [[ $3 == "" ]]; then

			#inform user that not enough parameters were filled
			echo "ERROR: NOT ALL PARAMETERES WERE SPECIFIED"

		#if parameter 6 is not empty
		elif [[ $6 != "" ]]; then
			
			#inform the user that there were too many parameters specified
			echo "ERROR: TOO MANY PARAMETERS SPECIFIED"

		#if paramter 3 is equal to all
		elif [[ "$3" == "all" ]]; then
			
			#output all contents of database specified
			cat $2

		#if paramter 3 is equal to single
		elif [[ $3 == single ]]; then

			#set hold variable to paramter 4
			hold=$4

			#add 1 to hold
			hold=$((hold + 1))

			#output content of line specified in database
			sed -n -e "$hold p" $2

		#if paramter 3 is equal to range
		elif [[ $3 == range ]]; then

			#set hold 1 and 2 variables to paramter 4 and 5
			hold1=$4
			hold2=$5

			#add 1 to hold1 and hold1
			hold1=$((hold1 + 1))
			hold2=$((hold2 + 1))

			#output content of range specified in database
			sed -n -e "$hold1,$hold2 p" $2

		#if an incorrect input was entered
		else

			#inform user that they made an invalid input
			echo "ERROR: INVALID INPUT"
			
		#end if loop
		fi

	#if user entered delete as command
	elif [[ $1 == delete ]]; then

		#if parameter 3 is empty
		if [[ $3 == "" ]]; then

			#inform user that not enough parameters were filled
			echo "ERROR: NOT ALL PARAMETERES WERE SPECIFIED"

		#if paramter 6 is not empty
		elif [[ $6 != "" ]]; then

			#inform user that there were too many parameters specified
			echo "ERROR: TOO MANY PARAMETERS SPECIFIED"

		#if paramter 3 is equal to all
		elif [[ $3 == all ]]; then

			#delete all contens of database
			sed '1! d' $2 > $tmp

			#move data from tmp to db
			mv $tmp $2

			#inform user that all lines were deleted
			echo "all lines deleted"

		#if paramter 3 is equal to single
		elif [[ $3 == single ]]; then

			#set hold variable to paramter 4
			hold=$4

			#add 1 to paramter 4
			hold=$((hold + 1))

			#delete line specified in database and store in tmp
			sed "${hold}d" $2 > $tmp

			#move data from tmp to db
			mv $tmp $2

			#inform user that a single line was deleted
			echo "single line deleted"

		#if paramter 3 is equal to range
		elif [[ $3 == range ]]; then

			#set hold 1 and 2 to paramters 4 and 5
			hold1=$4
			hold2=$5

			#add 1 to hold 1 and 2
			hold1=$((hold1 + 1))
			hold2=$((hold2 + 1))

			#delete range specified in database and store in tmp
			sed "${hold1},${hold2} d" $2 > $tmp

			#move data from tmp to db
			mv $tmp $2

			#inform user that all lines in range were deleted
			echo "lines in range deleted"

		#if an incorrect input was entered
		else

			#inform user that they made an invalid input
			echo "ERROR: INVALID INPUT"
			
		#end if loop
		fi

	#if user entered quit as command
	elif [[ $1 == quit ]]; then

		#inform user that the program will end
		echo "the program will now end"

	#if and incorrect input was entered
	else

		#inform user that they made an ivalid input
		echo "ERROR: INVALID INPUT"
	
	#end if loop
	fi

#end if loop
fi
