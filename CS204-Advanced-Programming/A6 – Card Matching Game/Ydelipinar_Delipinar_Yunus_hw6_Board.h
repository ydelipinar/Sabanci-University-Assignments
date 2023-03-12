#ifndef YDELIPINAR_DELIPINAR_YUNUS_HW6_BOARD_H
#define YDELIPINAR_DELIPINAR_YUNUS_HW6_BOARD_H
#include <iostream>
#include <string>
#include <fstream>

//created by Yunus Delipinar
using namespace std;

template <class itemType>
struct Alucard
{
	string status;

	itemType info;
};

template <class itemType>
class Board
{
	private:
		Alucard<itemType> ** matrix;
		int rows;
		int columns;
	public:
		Board( const int &row, const int &column); //constructor
		Board (const Board &);                     //copy constructor
		~Board(); //destructor
		void readBoardFromFile(ifstream & input);
		void displayBoard();
		void closeCard(int & row, int & column);
		int getRow();
		int getColumn();
		Alucard<itemType> ** createClone () const;
		string getStatus(int &row, int &column);         //accesor function
		void openStatus(int & row, int & column);         //mutator function
		itemType getInfo(int & row, int & column);         //accesor function


};
#include "Ydelipinar_Delipinar_Yunus_hw6_Board.cpp" 


#endif