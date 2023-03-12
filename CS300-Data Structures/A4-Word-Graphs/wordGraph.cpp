#include <iostream>
#include <string>
#include "wordGraph.h"


wordGraph::wordGraph(vector<string> longList)  //contructor which contructs graph by traversing the given list
{
    int n = longList.size();
    vector<vector<int>>temp_graph(n + 1);
    for (int i = 0;i < n;i++) {
        for (int j = i + 1;j < n;j++) {
            if (isAdj(longList[i], longList[j])) {
                temp_graph[i].push_back(j);
                temp_graph[j].push_back(i);
            }
        }
    }
    Graph = temp_graph;
}

bool wordGraph::isAdj(string& x, string& y)        //function to check whether two words are adjacent to each other
{
    int size_x = x.size(), size_y = y.size();

    if ((size_y + 1) == size_x)       
    {
        if (x.find(y) != string::npos)
        {
            return true;
        }
        else
        {
            int count = 0;
            for (int i = 0;i < x.size();i++)
            {
                if (x[i] == y[count])
                {
                    count++;
                }
            }
            if (count == y.size())
            {
                return true;
            }
            else
            {
                return false;
            }
        }           
    }
    else if ((size_x + 1) == size_y)
    {
        if (y.find(x) != string::npos)
        {
            return true;
        }
        else
        {
            int count = 0;
            for (int i = 0;i < y.size();i++)
            {
                if (y[i] == x[count])
                {
                    count++;
                }
            }
            if (count == x.size())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
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
bool wordGraph::isContains(string beginW, string endW, vector<string> longList)
{
    beginI = -1;
    endI = -1;
    for (int i = 0;i < longList.size();i++) {      //this function check whether given two words exist in list
        if (longList[i] == beginW) {            //also finds the indexes of the given words in the list
            beginI = i;
        }
        else if (longList[i] == endW) {
            endI = i;
        }
        if (beginI != -1 && endI != -1)  //break the loop to gain time
        {
            break;       
        }
    }
    if (beginI == -1 || endI == -1)
    {
        return false;
    }
    else
    {
        return true;
    }
    
}
void wordGraph::findShortestPaths (vector<string>& words, vector<vector<int>>& prevs,  
    vector<vector<string>>& shortestpath, int current, vector<int>& currPath)  //using DFS to find shortest paths
{
    if (beginI == current) {  //using the index of the first word
        vector<string>temp;
        for (int i = currPath.size() - 1;i >= 0;i--) {
            temp.push_back(words[currPath[i]]);
        }
        temp.push_back(words[endI]);  //push relevant word to temp
        shortestpath.push_back(temp);         //push path to shortest path list
        return; 
    }
    for (int i = 0;i < prevs[current].size();i++) {
        currPath.push_back(prevs[current][i]);
        findShortestPaths(words, prevs, shortestpath, prevs[current][i], currPath);
        currPath.pop_back();   //delete the currpath from list
    }
}
void wordGraph::findAllPaths(vector<string> longList)  //BFS algorithm to find
{
    int n = longList.size();
    vector<vector<int>>visited(n);
    vector<int>steps(n, 0);
    queue<int>q;
    q.push(beginI);
    int depth = 0;
    while (q.size()) 
    {                           //loop until queue is empty
        int size = q.size();
        for (int i = 0;i < size;i++) 
        { 
            int curr = q.front();
            q.pop();
            for (int x = 0; x < Graph[curr].size(); x++)   //traverse the current words neighbours
            {
                if (steps[Graph[curr][x]]) 
                {
                    if (steps[Graph[curr][x]] == depth + 1)
                        visited[Graph[curr][x]].push_back(curr);
                    continue;
                }
                steps[Graph[curr][x]] = depth + 1;  
                visited[Graph[curr][x]].push_back(curr);
                q.push(Graph[curr][x]);
            }
        }
        depth++;  //increment the depth
    }


    vector<int>currPath;
    findShortestPaths(longList, visited, shortestPaths, endI, currPath);
}

void wordGraph::printShortestPaths() //printing the paths in required format
{
    if (shortestPaths.size() == 0)
    {
        cout << "There is no sequence of one letter transformations exists with given words." << endl;
    }
    else
    {
        for (int x = 0; x < 1; x++)   //loop to traverse all paths changed to x < 1 to display only the first path
        {
            cout << x +1 << "- Shortest path is below" << endl << endl;
            for (int y = 0; y < shortestPaths[x].size(); y++)  //loop to traverse path
            {
                if (y == 0)
                {
                    cout << shortestPaths[x][y] << endl;
                }
                else
                {
                    string prevWord = shortestPaths[x][y-1];
                    string word = shortestPaths[x][y];
                    int prevSize = prevWord.size();
                    int size = word.size();
                    int index = 0;                //above if and elses for checking all cases
                    if (prevSize < size)    
                    {
                        while(index < prevSize)  //loop to find correct index
                        {
                            
                            if (prevWord[index] != word[index])  
                            {
                                break;
                            }
                            index++;
                        }
                        cout << word << " (insert " << word[index] << " after position " << index << ")" << endl;
                    }
                    else if (prevSize > size)  
                    {
                        while (index < size)    //loop to find correct index
                        {
                            if (prevWord[index] != word[index])
                            {
                                break;
                            }
                            index++;
                        }
                        cout << word << " (delete " << prevWord[index] << " at position " << index+1 << ")" << endl;
                    }
                    else
                    {
                        while (index < size)    //loop to find correct index
                        {
                            if (prevWord[index] != word[index])
                            {
                                break;
                            }
                            index++;
                        }
                        cout << word << " (change " << prevWord[index] << " at position " << index + 1 <<" to " << word[index] << ")" << endl;
                    }              
                }
            }
        }
    }
}
void wordGraph::deleteOldPaths()  //delete old paths to avoid confusion
{
    while (shortestPaths.size() != 0)
    {
        shortestPaths.pop_back();
    }
}

