#include <iostream>
#include <string>
#include <fstream>
#include "Ydelipinar_Delipinar_Yunus_hw6_Player.h"

//created by Yunus Delipinar

using namespace std;

template <class itemType>
Player<itemType>::Player (Board<itemType> & board):myBoard(board), score(0){};     //constructor

	
template <class itemType>
itemType Player<itemType>::openCard (int & row, int & column)
{
	myBoard.openStatus(row , column);
	return myBoard.getInfo(row, column);
}

template <class itemType>
bool Player<itemType>::validMove(int & row, int & column)
{
	if(row >= myBoard.getRow())
	{
		return false;
	}
	else if (column >= myBoard.getColumn())
	{
		return false;
	}
	else if (myBoard.getStatus(row, column) == "opened")
	{
		return false;
	}
	else 
	{
		return true;
	}
}

template <class itemType>
void Player<itemType>::increaseNumberOfSuccess()
{
	score++;
}

template <class itemType>
int Player<itemType>::getNumberOfSuccess()
{
	return score;
}