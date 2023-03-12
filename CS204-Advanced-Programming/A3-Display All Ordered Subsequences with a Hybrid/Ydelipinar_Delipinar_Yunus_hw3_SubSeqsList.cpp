#include "Ydelipinar_Delipinar_Yunus_hw3_SubSeqsList.h"
#include <iostream>


using namespace std;

//created by Yunus Delipinar 26617
SubSeqsList::SubSeqsList()
{
	hHead = NULL;
}
SubSeqHeadNode * SubSeqsList::generator(int num)         //this fucntion creates subseqHeadnode with size 1 
{
	SubSeqHeadNode * temp = new SubSeqHeadNode;
		SubSeqNode * temp2 = new SubSeqNode;
		temp ->size = 1;
		temp2->value = num;
		temp2->next = NULL;
		temp->sHead = temp2;
		temp->next=NULL;
		return temp;
}
void SubSeqsList::printList()       //print the list
{
	cout<< endl<<"FINAL CONTENT" <<endl;
	SubSeqHeadNode * ptr3 = hHead;
	if(ptr3 == NULL)
	{
		cout <<"List is empty!" << endl;
	}
	while(ptr3 !=NULL)
	{
		cout <<ptr3->size<<" |";
		SubSeqNode*miniptr = ptr3->sHead;
		while(miniptr != NULL)
		{
			cout <<" "<< miniptr->value;
			if(miniptr->next !=NULL)
			{
				cout << " -->";
			}
			miniptr=miniptr->next;
		}
		cout << endl;
		ptr3 = ptr3->next;
	}
}

bool SubSeqsList::SearchList(int searchValue)       //this function searches number in the list 
{
	SubSeqHeadNode * ptr = hHead;
	while (ptr!= NULL)
	{
		SubSeqNode * miniptr =ptr->sHead;
		while(miniptr != NULL)
		{
			if(miniptr->value == searchValue)    //if we found the node containing number return true
			{
				return true;
			}
			miniptr=miniptr->next;
		}
		ptr = ptr->next;
	}
	return false;          //if we dont found number then return false
}

void SubSeqsList::DeleteNum (int number)        //this function deletes the given number from the list with all of its subsequences
{
	while(SearchList(number))            //while we have number in list keep deleting nodes including it
	{
		SubSeqHeadNode * ptr = hHead;
		if(ptr->sHead->value == number)     //check the first node
		{
			hHead= hHead->next;
			delete ptr->sHead;
			delete ptr;
		}
		else
		{
			bool test = true;
			while(ptr ->next != NULL && test)
			{
				SubSeqNode * miniptr = ptr->next->sHead;   //create subseqnode variable to traverse ptr without changing it
				while(miniptr != NULL && test)
				{
					if (miniptr->value == number)       //if we found num then this the node to be deleted
					{
						test = false;
					}
					else
					{
						miniptr = miniptr->next;
					}
				}
				if(test)         //if we have not found the node then keep searching
				{
					ptr = ptr->next;
				}
			}
			if (!test)          //if we found the node to be deleted then delete it
			{
				SubSeqHeadNode * todeleted = ptr->next;
				ptr->next =todeleted->next;
				SubSeqNode *temp ;
				while(todeleted->sHead!=NULL)
				{
					temp = todeleted->sHead;
					todeleted->sHead = todeleted->sHead->next;
					delete temp;
				}
				delete todeleted;
			}
		}
	}
}
/* Begin: code taken from linkedList.cpp and updated */
void SubSeqsList::DeleteList ()            //this function deletes the whole list
{
	SubSeqHeadNode* ptr;
	while (hHead != NULL)
	{
		ptr=hHead;
		SubSeqNode*miniptr ;
		while(ptr->sHead != NULL)      //delete the subseqnodes
		{
			miniptr = ptr->sHead;
			ptr->sHead= miniptr->next;
			delete miniptr;
		}
		hHead= hHead->next;
		delete ptr;         //delete the headnode
	}
}
/* End: code taken from linkedList.cpp and updated */

SubSeqNode* SubSeqsList::Create(SubSeqNode* head, int num)  //this function creates a  copy of subseqnode 
{
	if(num == -1)     //this section just clones subseqnode without adding a number
	{
		if (head == NULL) 
		{
			return NULL;
		}
		SubSeqNode* temp = new SubSeqNode;
		temp->value = head->value;
		temp->next = Create(head->next, num);
		return temp;
	}
	else        //this part clones a subseqnode and adds a number 
	{
		if (head == NULL) 
		{
			SubSeqNode* add = new SubSeqNode;
			add->value = num;
			add->next = NULL;
			return add;
		}
		SubSeqNode* temp = new SubSeqNode;
		temp->value = head->value;
		temp->next = Create(head->next, num);
		return temp;
	}
 
}

bool SubSeqsList::canAdd (SubSeqNode * head, int num) //this function checks if i can add the number or not
{
	                                 //used in addNumber function
	SubSeqNode * ptr3 = head;       
	while (ptr3 != NULL)
	{
		if (ptr3->value >= num)
		{   
			return false;
		}
		ptr3 = ptr3->next;
	}
	return true;
}


SubSeqHeadNode * SubSeqsList::addSorted(SubSeqHeadNode * toAdd)  //this function add the given subseqnode with a sorted manner
{
	bool test1 = true;
	SubSeqHeadNode * ptr = hHead;
	if (toAdd->sHead->value < hHead->sHead->value)          //check the firs node
    {   
		toAdd->next=hHead; //connect the rest
		return toAdd;
    }
	while(ptr->next != NULL && ptr->next->size < toAdd->size)    //this loop moves to the next node until sizes are equal
	{
		ptr= ptr->next;
	}
	while((ptr->next != NULL && ptr->next->size == toAdd->size)&& test1) //if size equal check every node
	{
		
		SubSeqNode * add2= toAdd->sHead;
		SubSeqNode * ptr2 = ptr->next->sHead;
		while(ptr2 !=NULL&& test1)
		{
			if (ptr2->value >add2->value)
			{
				test1 = false;
			}
			else
			{
				ptr2 = ptr2->next;
				add2 = add2->next;
			}
		}
		if (test1)   //if did not find in this node check the other one
		{
			ptr = ptr->next;
		}
	}
	toAdd->next = ptr->next;//connecting rest of the nodes
	ptr->next = toAdd;       //add toAdd to hHead
	return hHead;
}	

void SubSeqsList::addNumber(int number)  //public member function to add number to a list using private functions
{
	if (hHead == NULL)
	{
		hHead = generator(number);		 //if head is null create node with size 1
	}
	else
	{
		SubSeqHeadNode * ptr = hHead; //loop variable
		SubSeqHeadNode * templist = new SubSeqHeadNode ;
		templist = generator(number);              //create our headnode number with size
		SubSeqHeadNode * tempptr = templist;
	
		while (ptr != NULL )
		{
			SubSeqNode * test = ptr->sHead;
			if(canAdd(test,number)) //if we can create subseqlist         
			{

				SubSeqHeadNode * temp = new SubSeqHeadNode;         //new subseqlist
                         
				SubSeqNode * list = Create(test,number);   //create a subseq with inputnumber added
				temp->sHead = list;                              //connect the subseq to subseqHeadNode
				temp->size= ptr->size+1;                         //update the new size
				temp->next = NULL;
	
				tempptr->next = temp;
				tempptr= tempptr->next;
			
			}
			ptr= ptr->next;
		}
	
		while(templist != NULL)     //this is where the all of the subseqnode that a number can create are stored
		{
			SubSeqNode * subSeqToAdd = Create(templist->sHead,-1);          
			SubSeqHeadNode * yun = new SubSeqHeadNode;
			yun->size = templist->size;
			yun->sHead = subSeqToAdd;
			yun->next = NULL;

			hHead = addSorted(yun);         //add or headnode to the mainlist
			templist= templist->next;      //move to the next head node to add to our mainlist
		}		
	}		
}
