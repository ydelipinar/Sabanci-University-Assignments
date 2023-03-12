#include <iostream>
#include <string>
#include <sstream>
#include "Ydelipinar_Delipinar_Yunus_hw3_SubSeqsList.h"
#include "strutils.h"

using namespace std;

//Created by Yunus Delipinar 26617

int main()
{
	SubSeqsList list;
	string numbers, sNumber;
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);
	cout << endl;
	istringstream numberList(numbers);
	int number;
	
	while (numberList >> sNumber)                 //read the numbers taken by user
	{
		number = atoi(sNumber);
		if (number >= 0)                       //if it is not negative
		{
			if(list.SearchList(number))        //check if number exist in list
			{
				cout <<number<<" is already in the list!" << endl;            
			}
			else                                                       //if number dont exist in list add it
			{
				list.addNumber(number);
				cout <<"Subsequence(s) containing " << number<<" has/have been added "<< endl;
			}
		}
		else                        //if number is negative
		{
			number = -1*number;
			if(list.SearchList(number))                //if it exist then delete it
			{
				list.DeleteNum(number);
				cout <<"All subsequence(s) containing "<< number << " has/have been deleted" << endl;
			}
			else
			{
				cout << "There is no subsequence that contains " << number<< " to be deleted" << endl;
			}
		}
	}
	list.printList(); //print the list
	list.DeleteList(); //delete the list
	 
}