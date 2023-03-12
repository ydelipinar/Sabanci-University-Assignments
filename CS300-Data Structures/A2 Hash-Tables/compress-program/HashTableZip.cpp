#include <iostream>
#include <string>
#include "HashTableZip.h"

HashTableZip::HashTableZip()
{
	codeSize = 256;
    array = new codeGeass[4096];
    makeEmpty();
}
int HashTableZip::hash(const string& key) //standard hash function taken from lecture slides
{
    int hashVal = 0;

    for (int i = 0; i < key.length();i++)
        hashVal = 37 * hashVal + key[i];

    hashVal = hashVal % 4096;

    if (hashVal < 0)
        hashVal = hashVal + 4096;

    return(hashVal);

}
int HashTableZip::findPos(const string& x) 
{
    int p = hash(x); // current position

    while (array[p].info != EMPTY && array[p].geass != x)
    {

        p++;  // increment the index p
        if (p >= 4096)             // perform the mod
        {
            p -= 4096;   // if necessary
        }
    }
    return p;
}
bool HashTableZip::isExist(const string& s)
{
    int count = 0;   // how many times we searched
    int p = hash(s);
    while (array[p].info != EMPTY && count < 4096)
    {
        if (array[p].geass == s)
        {
            return true;
        }
        p++;
        count++;
        if (p >= 4096)             // perform the mod
        {
            p -= 4096;   // if necessary
        }
      
    }
    return false;
}
bool HashTableZip::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE;
}

int HashTableZip::getCode(const string& x)
{
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return array[currentPos].code;

    return -1;
}
void HashTableZip::insert(const string& x)
{
    // Insert x as active
    int currentPos = findPos(x);
    if (isActive(currentPos))
        return;

    codeGeass temp(ACTIVE);
    temp.code = codeSize;
    temp.geass = x;
    array[currentPos] = temp;
    codeSize++;
    // enlarge the hash table if necessary 
}

bool HashTableZip::isFull()   
{
    return codeSize >= 4096;
}

void HashTableZip::makeEmpty()           //initializes the list
{
    for (int x = 0; x < 4096; x++)
    {
        if (x < 256)
        {
            char c = char(x);
            string s(1, c);
            codeGeass temp(ACTIVE);
            temp.code = x;
            temp.geass = s;
            array[x] = temp;

        }
        else
        {
            codeGeass temp(EMPTY);
            array[x] = temp;
        }
        
    }
}
HashTableZip::~HashTableZip()   //destructor
{
    delete [] array;
    array = NULL;
}