#include <iostream>
#include <string>
#include <sstream>
#include "Ydelipinar_Delipinar_Yunus_hw5_Wallet.h"

using namespace std;

//Created by Yunus Delipinar 26617
Wallet::Wallet()          //default constructor
{
	Walletsize = 0;
	myWallet = new Money[Walletsize];
}
Money * Wallet::createClone (int test) const   //function to create clone
{
	Money * myWalletClone = new Money[Walletsize+test];   //using + test  has given me acces to manipulate array size
	for( int x = 0; x < Walletsize; x++)
	{
		myWalletClone[x] = myWallet[x];
	}
	return myWalletClone;
	
}
Wallet ::Wallet(const Wallet & copy)  //deep copy contructor
{
	Walletsize = copy.Walletsize;
	myWallet = copy.createClone(0);
}
Wallet::~Wallet()   //destructor
{
	delete [] myWallet;
	myWallet = NULL;

}
  Wallet Wallet::operator + (const Money & rhs) const
{
	bool test = false;
    int index = 0;
	while(index < Walletsize && test== false)            //loop to check existence of currency in a wallet
	{
		if (myWallet[index].currency == rhs.currency)
		{
			test = true;
		}
		else
		{
		  index++;
		}
	}
	if(test)  //if money currency exist   
	{
		Wallet temp(*this);
		temp.myWallet[index].amount +=rhs.amount;  //add the amount
		return temp;
	}
	else             //if currency does not exist in wallet then create new array with bigger size and add the currency
	{
		Wallet temp(*this);
		Money * list = temp.createClone(1);
		list[temp.Walletsize] = rhs;
		delete [] temp.myWallet;
		temp.myWallet = list;
		temp.Walletsize = Walletsize+1;
		return temp;
	}
 }
 /* Begin: code taken from clockt.cpp */

 Wallet operator + (const Wallet & lhs,const Wallet & rhs)        
 {
	 Wallet temp(lhs);	//uses the default (compiler generated) copy constructor
    temp += rhs;		//uses the previously defined operator+=
    return temp;
 }
 /* End: code taken from clockt.cpp */
 Wallet Wallet::operator - (const Money & rhs) const
 {
	bool test = false;
    int index = 0;
	while(index < Walletsize && test== false)   //loop to check existence of the currency
	{
		if (myWallet[index].currency == rhs.currency)
		{
			test = true;
		}
		else
		{
			index++;
		}
	}
	if(test)  //if money currency exist
	{
		if(myWallet[index].amount > rhs.amount)              //checks the amount in the wallet
		{
			Wallet temp(*this);
			temp.myWallet[index].amount -=rhs.amount;
			return temp;
		}
		else if (myWallet[index].amount == rhs.amount)       //if wallet.amount equals to money.amount then remove the currency in the wallet
		{
			Wallet temp(*this);
			Money * list = new Money[Walletsize-1];
			int x =  0;
			int y = 0;
			while(x < Walletsize-1)
			{
				if(y == index)
				{
					y++;
				}
				list[x] = myWallet[y];
				x++;
				y++;
			}
		     
			delete [] temp.myWallet;    //delete the memory to prevent memory leak
			temp.myWallet = list;
			temp.Walletsize = Walletsize-1;
			return temp;
		}
		else      //if wallet.amount smaller than money.amount then return the wallet without changing it
		{
			Wallet temp(*this);
			return temp;
		}
	}
	else        //if money currency does not exist return the wallet
	{
		Wallet temp(*this);
		return temp;
	}
 }

const Wallet & Wallet::operator = (const Wallet & rhs)
{
	if (this != &rhs)
	{
		delete [] myWallet; 
		myWallet = rhs.createClone(0);
		Walletsize = rhs.Walletsize;
	}
	return *this;
}

 const Wallet & Wallet::operator += (const Wallet & rhs)
 {
	int common = 0 ;
	 for (int i = 0; i < rhs.Walletsize; i++)       //these loops find the common currencies in both wallets
	 {
		 for(int j = 0; j < Walletsize; j++)
		 {
			 if ( rhs.myWallet[i].currency == myWallet[j].currency)
			 {
				 common++;
			 }
		 }
	 } 
	 int count = Walletsize-common;  //count of the uncommon currencies
	 int size = rhs.Walletsize + count;    //size of the new wallet object
	 int top = rhs.Walletsize;
	 Money * temp = rhs.createClone(count);  //creating a wallet with additional slots for new currencies

	 for(int i = 0; i < Walletsize; i++)  //these loops add the lhs amounts to temp wallet and if there is a new currency exist then it creates new object
	 {
		 bool test = true;
		 for (int j= 0; j< size && test; j++)
		 {
			 if(j == top)   //checks that if the index points to null if it is then assign new currency
			 {
				 temp[j] = myWallet[i];
				 test = false;
				 top++;
			 }
			 else if(myWallet[i].currency == temp[j].currency)
			 {
				 temp[j].amount += myWallet[i].amount;
				 test = false;
			 }
		 }
	 }
	 delete [] myWallet;  //prevent to memory leak
	 myWallet = temp;
	 Walletsize = size;
	 return *this;
 }
 bool Wallet::operator == (const Wallet & rhs)
 {
	 if(Walletsize != rhs.Walletsize)  //check the walletsize beforehand
	 {
		 return false;
	 }
	 else
	 {
		 int common = 0;

		 for(int i = 0; i < Walletsize; i++)        //these loops checks the equality through looking every index 
		 {
			 for(int j = 0; j < rhs.Walletsize; j++)
			 {
				 if(myWallet[i].currency == rhs.myWallet[j].currency)
				 {
					 if(myWallet[i].amount == rhs.myWallet[j].amount)
					 {
						 common++;
					 }
				 }
			 }
		 }
		 if (common == Walletsize)  // if number of the equal elements in wallet equalt to walletsize then it is the same wallet
		 {
			 return true;
		 }
		 else
		 {
			 return false;
		 }
	 }
 }
bool Wallet::operator >= (const Money & rhs) const
{
	bool test = true;
    int index = 0;
	while(index < Walletsize && test )  //loop for finding a currency
	{
		if (myWallet[index].currency == rhs.currency)
		{
			test = false;
		}
		else
		{
			index++;
		}
	}
	if (test) //if currency in ot in wallet return false
	{
		return false;
	}
	else  //check for amount
	{
		if(myWallet[index].amount >= rhs.amount)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
bool operator <= (const Money & lhs, const Wallet & rhs)  //using previosly defined >= operator makes the function easy
{
	return rhs >= lhs;
}
ostream & operator << (ostream & os, const Wallet & ct)
 {
	 
	 os << ct.tostring();  //uses the functino defined below
     return os;

 }
string Wallet::tostring()     const
 {
	 ostringstream os;
	 int count = Walletsize;
	 for(int x = 0; x < count; x++)  //simple loop for printing the elements of the array
	 {
		 if(x<count-1)
		 {
			os << myWallet[x].currency << " " << myWallet[x].amount<< " - ";
		 }
		 else
		 {
			 os << myWallet[x].currency << " " << myWallet[x].amount;
		 }
	 }
    return os.str();  
}
