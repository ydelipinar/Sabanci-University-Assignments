#ifndef Ydelipinar_Delipinar_Yunus_hw3_SubSeqsList_h
#define Ydelipinar_Delipinar_Yunus_hw3_SubSeqsList_h
#include <iostream>
using namespace std;
//created by Yunus Delipinar 26617

struct SubSeqNode
{
	int value;
	SubSeqNode * next;
	// constructors come here
};

struct SubSeqHeadNode
{
	int size; // number of elements in the subsequence
	SubSeqNode * sHead; // head of the subsequence list
	SubSeqHeadNode * next;
	// constructors come here
};

class SubSeqsList
{
	public:
		SubSeqsList(); //default constructor that creates an empty list
		void addNumber( int number);          //add number to al ist
		bool SearchList(int searchValue);   //searches the number in a list
		void DeleteList ();              //deletes all list
		void DeleteNum (int number); //deletes number from a list
		void printList();         //prints the list
		// member functions come here

	private:
		SubSeqHeadNode * hHead;
		SubSeqHeadNode * addSorted(SubSeqHeadNode * toAdd); //add headnodes to mainlist
		bool canAdd (SubSeqNode * head,int num);           //checks whether we create headnode with a given number
		SubSeqNode* Create(SubSeqNode* head, int num) ;      //clones a subseqnode
		SubSeqHeadNode * generator(int num);                    //generates subseqheadnode with size 1
		// any helper functions you see necessary
};
#endif