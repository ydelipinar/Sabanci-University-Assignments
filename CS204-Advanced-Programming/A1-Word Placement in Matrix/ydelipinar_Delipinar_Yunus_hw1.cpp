#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "strutils.h"
#include <sstream>
#include <vector>
#include <iomanip>  

using namespace std;

void Print(const vector<vector<string>> & matrix);                                                     //prototypes for functions
bool right (vector<vector< string >> & matrix, string word, int row, int column, string orientation);
bool left (vector<vector< string >> & matrix, string word, int row, int column, string orientation);
bool up  (vector<vector< string >> & matrix, string word, int row, int column, string orientation);
bool down (vector<vector< string >> & matrix, string word, int row, int column, string orientation);


int main()
{
	vector<vector<string>> myMatrix;
	string fileName, line;
	ifstream file;

	cout << "Please enter the name of the file: ";
	cin >> fileName;

	file.open(fileName.c_str());       
	while (file.fail())           //check the filename until user enters correctly
	{
		cout << "File name is incorrect, please enter again: " ;
		cin >> fileName;
		file.open(fileName.c_str()); 
	}

	int linecount = 1; // to know which line is processed
	
	while (getline(file, line))
	{
		int wordcount = 1;
		int row, column;
		string temp, word, direction, orientation;
		istringstream fileStream(line);

		while (fileStream >> temp)
		{
			if (linecount == 1)  //get numbers of rows and columns
			{
				if (wordcount == 1)
				{
					if (atoi(temp) > 0)  //check if the row number bigger than 0
					{
						row = atoi(temp);
						//cout << row << endl;  
					}
					else                //display error message if input is wrong
					{
						cout << "Invalid number for row and/or column!" << endl;	
						file.close();
						wordcount = 0;
					}
				}
				else if (wordcount == 2)
				{
					if (atoi(temp) > 0)   //check if the column number bigger than 0
					{
						column = atoi(temp);
						vector<vector< string >> matrix(row, vector<string>(column, "-"));  //create matrix with given rows and columns
						myMatrix = matrix;                                                   // make the matrix exist out of the while loop
					}
					else        //display error message if input is wrong
					{
						cout << "Invalid number for row and/or column!" << endl;	
						file.close();                                                  //close file so that we wont read rest of the file
					}
				}
				else                         // give an error if there are more than 3 inputs in first line
				{
					cout << "There should not be more than two inputs" << endl;
				}
			}
			else if (linecount > 1)    //take inputs from other lines
			{
				if (wordcount == 1)    //get word itself
				{
					word = temp;
				}
				else if (wordcount == 2)  //get starting position's row number
				{
					row = atoi(temp);
				}
				else if (wordcount == 3)    //get starting position's column number
				{
					column = atoi(temp);
				}
				else if (wordcount == 4)   // get direction
				{
					direction = temp;
				}
				else if(wordcount == 5)    // get orientation
				{
					orientation = temp;
				}
			}
			wordcount++;
		}
		wordcount--;
		if ( linecount > 1 && wordcount !=5)   //give an error if there are not 5 words in a line other than first line and skip the line
		{
			cout << "Invalid line! Number of values is different than 5." << endl;
		}
		else if (linecount > 1 && (myMatrix.size() <= row || myMatrix[0].size() <= column))  //give an error if starting point is out of range and skip the line
		{
			cout << "Starting point is out of range! Point: " << row << "," << column << endl;
		}
		else if (linecount > 1 && (direction != "r" && direction != "l" && direction !="u" && direction != "d")) //give an error if direction is wrong and skip the line
		{
			cout << "Invalid input for direction! Direction: " << direction <<endl;
		}
		else if (linecount > 1 && (orientation != "CW" && orientation != "CCW"))    //give an error if orientation is wrong and skip the line 
		{
			cout << "Invalid input for orientation! Orientation: " << orientation << endl;
		}
		else if (linecount > 1)   
		{
			if (myMatrix[row][column] != "-")    //give an eror because starting location is occupied 
			{
				cout << "\"" << word << "\"" << " could not be put into the matrix with given starting point: " << row << ", " << column << " direction: " << direction << " orientation: " << orientation << endl;
				Print (myMatrix);
			}
			else
			{
				bool isPlaced;

				if (direction == "r")                                                 //if direction is right apply the function right
				{
					isPlaced = right(myMatrix, word,  row, column, orientation);
				}
				else if (direction == "l")                                        //if direction is left apply the function left
				{
					isPlaced = left(myMatrix, word,  row, column, orientation);
				}
				else if (direction == "u")                                       //if direction is up apply the function up
				{
					isPlaced = up(myMatrix, word,  row, column, orientation);
				}
				else if (direction == "d")                                       //if direction is down apply the function down
				{
					isPlaced = down(myMatrix, word,  row, column, orientation);
				}

				if (isPlaced)                                                        //if the word placed to the matrix
				{
					cout << "\"" << word << "\"" << " was put into the matrix with given starting point: " << row << ", " << column << " direction: " << direction << " orientation: " << orientation << endl;
					Print (myMatrix);
				}
				else                                                        //if the word could not be placed to the matrix
				{
					cout << "\"" << word << "\"" << " could not be put into the matrix with given starting point: " << row << ", " << column << " direction: " << direction << " orientation: " << orientation << endl;
					Print (myMatrix);
				}

			}
		}
		linecount++;  //update line
	}
	file.close();
}

void Print(const vector<vector<string>> & matrix)                   //to print matrix to the console
{
	for (int j = 0; j < matrix.size(); j++)
	{
		for (int k = 0; k < matrix[0].size(); k++)
		{
			cout << setw(4) << matrix[j][k];
		}
		cout << endl;
	}
	cout << endl;
}

bool right (vector<vector< string >> & matrix, string word, int row, int column, string orientation)
{
	
	vector<vector<string>> fakematrix = matrix;   //create fake matrix to check whether given word can fit the original matrix
	bool test = true;

	fakematrix[row][column] = word[0];         //place first letter of the word 

	if (orientation == "CW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")     //RIGHT      
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")      //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")             //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	else if (orientation == "CCW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	if (test)                  // if our word placed to the fakematrix then upgrade our real matrix
	{
		matrix = fakematrix;
	}
	return test;               // return the bool value if our matrix replaced or not
}

bool left (vector<vector< string >> & matrix, string word, int row, int column, string orientation)
{
	vector<vector<string>> fakematrix = matrix;   //create fake matrix to check whether given word can fit the original matrix
	bool test = true;

	fakematrix[row][column] = word[0];         //place first letter of the word 

	if (orientation == "CW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
		    if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
	        else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	else if (orientation == "CCW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	if (test)                  // if our word placed to the fakematrix then upgrade our real matrix
	{
		matrix = fakematrix;
	}
	return test;               // return the bool value if our matrix replaced or not
}

bool up (vector<vector< string >> & matrix, string word, int row, int column, string orientation)
{
	vector<vector<string>> fakematrix = matrix;   //create fake matrix to check whether given word can fit the original matrix
	bool test = true;

	fakematrix[row][column] = word[0];         //place first letter of the word 

	if (orientation == "CW")
	{	
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	else if (orientation == "CCW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if (  column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	if (test)                  // if our word placed to the fakematrix then upgrade our real matrix
	{
		matrix = fakematrix;
	}
	return test;               // return the bool value if our matrix replaced or not
}

bool down (vector<vector< string >> & matrix, string word, int row, int column, string orientation)
{
	vector<vector<string>> fakematrix = matrix;   //create fake matrix to check whether given word can fit the original matrix
	bool test = true;

	fakematrix[row][column] = word[0];         //place first letter of the word 

	if (orientation == "CW")
	{	
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if ( column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	else if (orientation == "CCW")
	{
		for (int x = 1; (x < word.length() && test == true); x++)
		{
			if (row+1 < fakematrix.size() && fakematrix[row+1][column] == "-")          //DOWN
			{
				row++;
				fakematrix[row][column] = word[x];
			}
			else if ( column+1 < fakematrix[0].size() && fakematrix[row][column+1] == "-")    //RIGHT       
			{
				column++;
				fakematrix[row][column] = word[x];
			}
			else if (row-1 >= 0 && fakematrix[row-1][column] == "-")                   //UP
			{
				row--;
				fakematrix[row][column] = word[x];
			}
			else if ( column-1 >= 0 && fakematrix[row][column-1] == "-")               //LEFT
			{
				column--;
				fakematrix[row][column] = word[x];
			}
			else
			{
				test = false;                    //return false in order to know matrix is not placed
			}
		}
	}
	if (test)                  // if our word is placed to the fakematrix then update our real matrix
	{
		matrix = fakematrix;
	}
	return test;
}