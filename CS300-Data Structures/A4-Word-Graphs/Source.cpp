#include <iostream>
#include <fstream>
#include <string>
#include "wordGraph.h"
#include <queue>
#include <vector>

using namespace std;

bool isAdj(string& x, string& y)
{
    int size_x = x.size(), size_y = y.size();

    if ((size_y + 1) == size_x && x.find(y) != string::npos)
    {
        return true;
    }
    else if ((size_x + 1) == size_y && y.find(x) != string::npos)
    {
        return true;
    }
    else if (size_x == size_y)
    {
        int count = 0;
        for (int i = 0;i < x.size() && count <= 1;i++)
        {
            if (x[i] != y[i])
            {
                count++;
            }
        }
        if (count <= 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
void collectPaths(vector<string>& words, vector<vector<int>>& prevs,
    vector<vector<string>>& result, int curr, vector<int>& currPath, int stop, int eindex) {
    if (stop == curr) {
        vector<string>temp;
        for (int i = currPath.size() - 1;i >= 0;i--) {
            temp.push_back(words[currPath[i]]);
        }
        temp.push_back(words[eindex]);
        result.push_back(temp);
        return;
    }
    for (int i = 0;i < prevs[curr].size();i++) {
        currPath.push_back(prevs[curr][i]);
        collectPaths(words, prevs, result, prevs[curr][i], currPath, stop, eindex);
        currPath.pop_back();
    }
}
int main()
{
    ifstream File;
    File.open("words.txt");
    string x;
    vector<string> longList;
    while (File >> x)    //get the text file to the matrix
    {
        longList.push_back(x);
    }
    wordGraph graph(longList);
    string word1 = "", word2;
    
    while (1)
    {
        cout << "Enter two words: ";
        cin >> word1 >> word2;
        cout << endl;
        if (word1[0] == '*')
        {
            cout << "* is entered, exiting the loop" << endl;
            break;
        }
        else if (graph.isContains(word1, word2, longList))  //if given words in our list
        {
            graph.findAllPaths(longList);     //calculate paths
            graph.printShortestPaths();       //print the shortest path with given format
            cout << endl;
                
        }
       
        else
        {
            cout << "One or both words is not in the list please re-enter the words" << endl << endl;
        }
        graph.deleteOldPaths();//delete the old paths to prepare upcoming words
    }
}