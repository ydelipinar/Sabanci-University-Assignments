#ifndef Ydelipinar_Delipinar_Yunus_hw5_Wallet_h
#define Ydelipinar_Delipinar_Yunus_hw5_Wallet_h

#include <string>
#include <iostream>
#include <sstream>
using namespace std;
//created by Yunus Delipinar 26617

struct Money
{
	double amount;
	string currency;
	// constructors come here
};

class Wallet
{
	public:
		Wallet(); //default contructor
		Wallet (const Wallet &); //copy contructor
		~Wallet(); //destructor
		Wallet operator + (const Money & rhs) const;
		Wallet operator - (const Money & rhs) const;
		const Wallet & operator = (const Wallet & rhs); // = operator
		Money * createClone (int test) const;  // create clone
		const Wallet & operator += (const Wallet & rhs);
		bool operator == (const Wallet & rhs);
		bool operator >= (const Money & rhs) const;
	    string  tostring()     const; 
		

	private:
		int Walletsize ;
		Money * myWallet;

};

ostream & operator << (ostream & os, const Wallet & ct);
bool operator <= (const Money & lhs, const  Wallet & rhs);
Wallet operator + (const Wallet & lhs,const Wallet & rhs);
	
#endif