#################################################################
#			NIU CSCI-330 FALL 2019			#
#								#
#	Section Number		1				#
#	Author:			Alex Marine			#
#	zID:			z1863905			#
#	Due Date:		December 2, 2019		#
#	Program Name:		z1863905.awk			#
#								#
#	Purpose of Program:					#
#		This program is an awk script that will generate#
#		a report when supplied input data in a specified#
#		format.						#
#################################################################


#perform at start of program
BEGIN {

	#set the field seperator to ':'
	FS=":"

	#print header
	printf "%-19s %-12s %10s\n", "Name", "Position", "Sales Amount";
	printf "=============================================\n";
}

{
	#if number of fields is 4, we are in products
	if(NF == 4) {

		#set parameter 1 to product id
		p_pid=$1
		#set parameter 4 to product price
		p_price=$4

		#create array of product ids and set to corresponding price
		p_arr[p_pid]=p_price
	}
	#if the number of fields is 3, we are in associates 
	else if(NF == 3) {

		#set parameter 1 to associate id
		a_aid=$1
		#set parameter 2 to name
		a_name=$2
		#set parameter 3 to position
		a_pos=$3

		#spilt associate name
		split(a_name, a, " ")
		#put second word before first with comma in between
		a_name=a[2]", "a[1]

		#create array of associate ids and set to corresponding name and position
		a_arr[a_aid]=a_name "-" a_pos
	}
	#if the number of fields is 5, we are in sales
	else if(NF == 5) {

		#set parameter 2 to transaction id
		s_tid=$2
		#set parameter 3 to quantity
		s_quant=$3
		#set parameter 4 to date
		s_date=$4
		#set parameter 5 to associate id
		s_aid=$5

		#if sales date is 2018
		if(s_date ~ /\/2018/) {

			#if associate id is in sales
			if(s_aid in s_arr) {

				#create array of associate ids and set to array of associate ids
				#plus array of transaction ids and multiply by quantity sold
				s_arr[s_aid]=s_arr[s_aid]+p_arr[s_tid]*s_quant
			}
			#if associate if is not in sales
			else {

				#create array of associates ids and set to array of transaction ids
				#plus quantity sold
				s_arr[s_aid]=p_arr[s_tid]*s_quant
			}
		}
	}	
}

#perform at end of program
END {

	#for all total in sales
	for(total in s_arr) {

		#if total is in a_arr
		if(total in a_arr) {

			#split array of total
			split(a_arr[total], a, "-")
			#set name to object in slot one of array a
			name=a[1]
			#set position to object in slot two of array a
			postion=a[2]

			#print out name, postion, and s_arr
			printf "%-19s %-12s %12.2f\n", name, postion, s_arr[total] | "sort -rn -k 4"
			
		}
	}	
}
