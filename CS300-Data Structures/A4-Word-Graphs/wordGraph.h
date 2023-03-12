#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

class wordGraph
{
public:

    wordGraph(vector<string> list); //default contructor
    bool isContains(string x, string y, vector<string> list);
    void findAllPaths(vector<string> list);  //using BFS
    void printShortestPaths();
    void deleteOldPaths();
private:


    bool isAdj(string& x, string& y);
    void findShortestPaths(vector<string>& words, vector<vector<int>>& prevs, vector<vector<string>>& result, int curr, vector<int>& currPath); //use dfs
    
    int endI = -1;
    int beginI = -1;
    vector<vector<string>> shortestPaths;  //paths that is found
    vector<vector<int>>Graph;  //graph

};