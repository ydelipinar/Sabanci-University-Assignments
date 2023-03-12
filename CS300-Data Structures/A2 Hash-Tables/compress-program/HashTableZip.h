#pragma once
#include <iostream>
#include <string>
using namespace std;
// created by Yunus Delipinar 26617
   
class HashTableZip
{
	public:
       
		HashTableZip(); //default contructor
		~HashTableZip(); //destructor
		
        int getCode(const string& x);
        void insert(const string& x);
       
        void makeEmpty();
        enum EntryType { ACTIVE, EMPTY};
        bool isFull();
        bool isExist(const string & s);
    private:

        struct codeGeass   //struct than I will use
        {
            int code;
            string geass = "";
            EntryType info;

            codeGeass(EntryType t = EMPTY) :
               info(t) {}

        };

        const string ITEM_NOT_FOUND;
        int codeSize;
        codeGeass * array;

        bool isActive(int currentPos) const;
        int findPos(const string& x);
        int hash(const string & x);
};