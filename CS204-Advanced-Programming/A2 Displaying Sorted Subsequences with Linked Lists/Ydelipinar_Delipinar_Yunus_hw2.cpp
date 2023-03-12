#include <iostream>
#include <string>
#include <sstream>
#include "strutils.h"

using namespace std;

//Created by Yunus Delipinar 26617

struct node 
{
int value;
node* next;
};

node * DeleteList (node *toDeleted, bool test);   //To delete nodes and if it is the end of input, print the nodes that are deleted in the end
void DisplayList (node * head);                   //To displat linked list
node * FuncforA(node * head, int newvalue);        // Function for ascending order
node * FuncforD(node * head, int newvalue);        //function for descending order
bool SearchList(node *head, int searchValue);          //function for checking whether newvalue is in the list or not

int main()
{
	string orderM, numbers, number;
	               
	node* head = NULL;              //create our node pointing NULL

	cout << "Please enter the order mode (A/D): " ;
	cin >> orderM;
    while (orderM != "A" && orderM != "D")         //get input from user until correct input is entered
	{
		cin.clear();
		cin.ignore(1000,'\n');
		cout << "Please enter the order mode again (A/D): " ;
		cin >> orderM ;
	}
	cin.clear();
	cin.ignore(1000,'\n');
	cout << "Please enter the numbers in a line: ";
	getline(cin, numbers);
	cout << endl;
	istringstream numberList(numbers);
	int value;
	while (numberList >> number)                 //read the numbers taken by user
	{
		value = atoi(number);
		cout << "Next number: " << value << endl;
		if(SearchList(head,value))                       //check the list if it contains the same number, if so print the required message and skip the number
		{
			cout << value << " is already in the list!" << endl;
			DisplayList(head);
		}
		else if (orderM == "A")                          //if order is ascending do this
		{
			head = FuncforA(head, value);
			cout << "Appended: " << value << endl;
			DisplayList(head);
		}
		else if (orderM == "D")	                         //if order is descending do that
		{
			head = FuncforD(head, value);
			cout << "Appended: " << value << endl;
			DisplayList(head);
		}
	}
	if (head == NULL)                                    //if head remains NULL at the end of the program then list is empty and user did not entered any number to list
	{
		cout << "The list is empty at the end of the program and nothing is deleted" << endl;
	}
	else                                                  // if head is not NULL then delete the list and diplay the values that are deleted
	{
		head = DeleteList(head, true);     //used true this time as it is the end of the programme
	}
}
/* Begin: code taken from linkedList.cpp and updated */
node * DeleteList (node *toDeleted, bool test) 
{		
  node *temp;
  if (test)                                                           //to check if it is end of the inputs
  {
	  cout << "All the nodes are deleted at the end of the program: ";
	  while (toDeleted != NULL) 
	  {				
		 temp = toDeleted;
		 toDeleted =toDeleted->next;
		 cout << temp->value << " ";
		 delete temp;   
	   }
  }
  else                                                        //delete the nodes coming after the given input
  {
	cout << "Deleted nodes: ";
	if (toDeleted == NULL)                           //if newnode-> next is NUll then there is nothing to be deleted so print None
	{
		  cout << "None";
	}
	while (toDeleted != NULL)                   // delete nodes until the newnode->next is NULL and print the deleted values
	{				
		temp = toDeleted;
		toDeleted =toDeleted->next;
	    cout << temp->value << " ";
		delete temp;   
	 }
  }
  cout << endl;
  return toDeleted;
}
/* End: code taken from linkedList.cpp and updated */

/* Begin: code taken from ptrfunc.cpp and updated  */
void DisplayList (node * head) 
{
	cout << "List content: ";                           //display the content of the list
	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->value << " ";
		ptr = ptr->next;
	}
	cout << endl<< endl;
		
}
/* End: code taken from ptrfunc.cpp and updated  */

/* Begin: code taken from ptrfunc.cpp and updated  */
node * FuncforA(node * head, int newvalue)

// post: add newvalue to list, and if required delete the nodes after the new node , return head of new list with newvalue in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return  
    // in this case, we return the address of new node since it is new head  
    if (head == NULL || newvalue < head->value)        
    {   
		node * temp = new node;  //node to be inserted 
		temp->value = newvalue;
		temp->next = head; //connect the rest
		temp-> next = DeleteList(temp->next, false); //delete the nodes after the temp and make temp->next NULL also use false to inform computer that this is not the end of the inputs
		return temp;
		
    }

    // check node one ahead so we don't pass!
    while (ptr->next != NULL && ptr->next->value < newvalue)
    {   
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points

    //now insert node with newkey after where ptr points to
	node * temp = new node;  //node to be inserted 
	temp->value = newvalue;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;
	temp-> next = DeleteList(temp->next, false);  //delete the nodes after the temp and make temp->next NULL also use false to inform computer that this is not the end of the inputs

    return head;
}
/* End: code taken from ptrfunc.cpp and updated  */

/* Begin: code taken from ptrfunc.cpp and updated  */
node * FuncforD(node * head, int newvalue)

// post: add newvalue to list, and if required delete the nodes after the new node , return head of new list with newvalue in it
{
    node *  ptr = head;   // loop variable

    // if new node should be first, handle this case and return  
    // in this case, we return the address of new node since it is new head  
    if (head == NULL || newvalue > head->value)        
    {   
		node * temp = new node;  //node to be inserted 
		temp->value = newvalue;
		temp->next = head; //connect the rest
		temp-> next = DeleteList(temp->next, false); //delete the nodes after the temp and make temp->next NULL also use false to inform computer that this is not the end of the inputs
		return temp;
		
    }

    // check node one ahead so we don't pass!
    while (ptr->next != NULL && ptr->next->value > newvalue)
    {   
		ptr = ptr->next;
    } // postcondition: new node to be inserted just after the node that ptr points

    //now insert node with newvalue after where ptr points to
	node * temp = new node;  //node to be inserted 
	temp->value = newvalue;
	temp->next = ptr->next; //connect the rest
	ptr->next = temp;
	temp-> next = DeleteList(temp->next, false);  //delete the nodes after the temp and make temp->next NULL also use false to inform computer that this is not the end of the inputs

    return head;
}
/* End: code taken from ptrfunc.cpp and updated  */


/* Begin: code taken from linkedList.cpp and updated */
bool SearchList(node *head, int searchValue)                 //search the list to check if the list contains the given value or not
{
	while (head != NULL)
	{
		if(head->value == searchValue) 
			return true;			
		head = head->next;
	}
	
	return false;
}
/* End: code taken from linkedList.cpp and updated */


