#include <iostream>
#include <string>
#include <fstream>
#include "Ydelipinar_Delipinar_Yunus_hw6_Board.h"
using namespace std;

//created by Yunus Delipinar

template <class itemType>
Board<itemType>::Board (const int &row, const int &column)
{
	rows = row;
	columns = column;
	matrix = new Alucard<itemType> * [rows];   //initialize our dynamic 2d array

	for(int i = 0; i<rows; i++)       
	{
		matrix[i] = new Alucard<itemType> [columns]; 
	}
}

template <class itemType>
Board<itemType>::Board (const Board<itemType> & copy)
{
	matrix = copy.createClone();
	rows = copy.rows;
	columns = copy.columns;
}

template <class itemType>
Board<itemType>::~Board()
{
	for (int i = 0; i< rows; i++) // Returning memory to free heap for reuse 
    { 
		delete [] matrix[i]; 
	}
	delete [] matrix;
	matrix = NULL;
}

template <class itemType>
void Board<itemType>::readBoardFromFile(ifstream & input)  //function to fill the board
{
	itemType info;
	int row = 0 ,column = 0;
	while(input >> info)
	{
		if(column == columns)  //if end of the column then move to the other row
		{
			row ++;
			column = 0;
		}
		Alucard<itemType> temp;        //initalizing the elements of the board
		temp.info= info;
		temp.status = "closed";
		matrix[row][column] = temp;
		column ++;
	}
}

template <class itemType>
void Board<itemType>::displayBoard()
{
	for (int i = 0; i<rows; i++)
	{
		for(int j = 0; j<columns; j++)
		{
			if(matrix[i][j].status == "closed")
			{
				cout << "X ";
			}
			else
			{
				cout << matrix[i][j].info << "  ";
			}
		}
		cout << endl;
	}
}

template <class itemType>
void Board<itemType>::closeCard(int & row, int & column)   //mutator function to change status
{
	matrix[row][column].status = "closed";
}

template <class itemType>
int Board<itemType>::getRow()
{
	return rows;
}

template <class itemType>
int Board<itemType>::getColumn()
{
	return columns;
}

template <class itemType>
Alucard<itemType> ** Board<itemType>::createClone() const   //creates clone of the matrix to create copy board
{
	Alucard<itemType> ** matrixClone;
	matrixClone = new Alucard<itemType> * [rows];
	for(int i = 0; i<rows; i++)
	{
		matrixClone[i] = new Alucard<itemType> [columns]; 
	} 
	for (int i = 0; i<rows; i++)
	{
		for(int j = 0; j<columns; j++)
		{
			matrixClone[i][j] = matrix[i][j];
		}
	}
	return matrixClone;
}

template <class itemType>
string Board<itemType>::getStatus(int &row, int &column)      //accesor function to use
{
	return matrix[row][column].status;
}

template <class itemType>
void Board<itemType>::openStatus(int & row, int & column) //mutator function to change the status
{
	matrix[row][column].status = "opened";
}

template <class itemType>
itemType Board<itemType>::getInfo(int & row, int & column)  //accesor function to acces private elements
{
	return matrix[row][column].info;
}


