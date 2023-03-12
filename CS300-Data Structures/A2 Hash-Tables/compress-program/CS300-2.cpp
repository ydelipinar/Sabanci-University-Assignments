#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "HashTableZip.h"
using namespace std;

//created by Yunus Delipinar
int main()
{
	HashTableZip dict;
	char ch;
	ifstream file("compin");
	
	string current = "";
	string prev = "";
	string output;
	ofstream outFile("compout");

	while (file.get(ch)) //eof returns true if next character 
	{
		string temp(1, ch);
		current += temp;
		if (!dict.isExist(current))      
		{
			if(!dict.isFull())           //if we can still add code
			{ 
					dict.insert(current);
			}	
			int code = dict.getCode(prev);
			cout << code << " ";
			outFile << code << " ";
			current = current[current.length() - 1];
			prev = current[current.length() - 1];
			if (file.peek() == EOF)
			{
				code = dict.getCode(prev);
				cout << code << " " ;
				outFile << code << " ";
			}
		}
		else
		{
			prev = current;
			if (file.peek() == EOF)
			{
				int code = dict.getCode(prev);
				cout << code << " ";
				outFile << code << " ";
			}
		}	
	}
}