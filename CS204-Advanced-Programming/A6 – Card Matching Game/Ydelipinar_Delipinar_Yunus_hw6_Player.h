#ifndef YDELIPINAR_DELIPINAR_YUNUS_HW6_PLAYER_H
#define YDELIPINAR_DELIPINAR_YUNUS_HW6_PLAYER_H


#include <iostream>
#include "Ydelipinar_Delipinar_Yunus_hw6_Board.h"
//created by Yunus Delipinar

template <class itemType>
class Player
{
	private:
		Board<itemType> & myBoard;  //board class to play
		int score;
	public:
		Player (Board<itemType> & board);         //constructor
		itemType openCard(int & row, int & column);
		bool validMove(int  &row, int  &column);
		void increaseNumberOfSuccess();
		int getNumberOfSuccess();
};







#include "Ydelipinar_Delipinar_Yunus_hw6_Player.cpp"



#endif


