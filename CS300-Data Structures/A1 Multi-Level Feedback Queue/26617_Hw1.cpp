
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <queue>
#include <vector>

//created by Yunus Delipinar
struct process
{
    int pID;
    int index = 0;
    vector<string> tSlice;
    process(int id)
    {
         pID = id;
    }
};

struct Queue
{
    int qID;
    queue<process> myQueue;
   
    Queue(int id)
    {
        qID = id;
    }
};

int main()
{
    ifstream File;
    string folderName;
    cout << "Please enter the process folder name: ";
    cin >> folderName;
    cout << "When all processes are completed, you can find execution sequence in " << folderName << "\"/output.txt\"." << endl << endl;

    int noq = -1, nop = -1, sos = -1;

    File.open(folderName + "\\configuration.txt");
    int x;
    cout << "Given Files for the Sample Run:" << endl << endl;
    cout << folderName << "/configuration.txt:" << endl;
    
    while (File >> x)
    {
        if (noq == -1)
        {
            noq = x;
        }
        else if (nop == -1)
        {
            nop = x;
        }
        else
        {
            sos = x;
        }
        cout << x << endl;
    }
    
    vector<Queue> schedule;

    for (int x = 1; x < noq + 1; x++)
    {
        Queue temp(x);
        schedule.push_back(temp);
    }
    File.close(); 
    vector<process> pList;
    for (int x = 1; x < nop + 1; x++)        //creating processes
    {
        cout << endl;
        string fileName = "p" + to_string(x) + ".txt";
        cout << folderName << "/" << fileName << ":" << endl;
        File.open(folderName + "\\" + fileName);
        process temp(x);
       
        string dummy;
        while (File >> dummy)             //read process texts and get the data to process struct
        {
            cout << dummy << endl;
            temp.tSlice.push_back(dummy);
        }
        pList.push_back(temp);
        File.close();
    }
    for (int y = 0; y < pList.size(); y++)
    {
        schedule[noq - 1].myQueue.push(pList[y]);         //filling the queue 4 with processes            
    }

    cout << endl;                                             //for output
    cout << "Output File for the Sample Run: " << endl << endl;
    cout << folderName << "/output.txt:" << endl;

    int remaining = nop;
    int S = 0;
    ofstream outFile;
    outFile.open(folderName + "\\output.txt");
    while (remaining > 0)
    {
        if (S == sos)
        {
            for (int x = noq - 2; x > -1; x--)      // make noq -2 since we dont need to check the first queue
            {
                while (schedule[x].myQueue.size() > 0)
                {
                    process temp = schedule[x].myQueue.front();
                    schedule[x].myQueue.pop();
                    outFile << "B,  " << "PC" << temp.pID << ",  Q" << noq << endl;
                    cout << "B,  " << "PC" << temp.pID << ",  Q" << noq << endl;
                    schedule[noq - 1].myQueue.push(temp);
                }
            }
            S = 0;
        }
        else
        {
            for (int x = noq - 1; x > -1 && S != sos; x--)
            {
                while (schedule[x].myQueue.size() > 0 && S != sos)
                {
                    process temp = schedule[x].myQueue.front();
                    int index = temp.index;
                    string value = temp.tSlice[index];
                    if (temp.tSlice[index + 1] == "-")
                    {
                        outFile << "E,  " << "PC" << temp.pID << ",  QX" <<  endl;
                        cout << "E,  " << "PC" << temp.pID << ",  QX" << endl;
                        schedule[x].myQueue.pop();
                        S++;
                        remaining--;
                    }
                    else
                    {
                        if (value == "0")
                        {
                            temp.index++;   //update the index
                            schedule[x].myQueue.pop();
                            outFile << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x].qID << endl;
                            cout << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x].qID << endl;
                            schedule[x].myQueue.push(temp);
                            S++;             //Update the time slice
                        }
                        else if (value == "1")
                        {
                            temp.index++;  //update the index
                            schedule[x].myQueue.pop();
                            //output
                            if (x > 0)
                            {
                                schedule[x - 1].myQueue.push(temp);
                                outFile << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x-1].qID << endl;
                                cout << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x - 1].qID << endl;
                            }
                            else
                            {
                                schedule[x].myQueue.push(temp);
                                outFile << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x].qID << endl;
                                cout << value << ",  " << "PC" << temp.pID << ",  Q" << schedule[x].qID << endl;
                            }
                            S++;
                        }
                        else
                        {
                            cout << "value is not correct" << endl;
                        }
                    }

                }
            }
        }
       
    }
    /*
    for (int y = 0; y < pList.size(); y++)
    {
        cout << "process" << pList[y].pID << endl;
        for (int x= 0; x < pList[y].tSlice.size(); x++)
        {
            cout << pList[y].tSlice[x] << endl;

        }
        
    }
    */

}
    

