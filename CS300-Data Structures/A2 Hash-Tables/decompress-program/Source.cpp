#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


enum EntryType { ACTIVE, EMPTY};
struct codeGeass
{
    string geass ;
    EntryType info;
    codeGeass(EntryType t = EMPTY, string g = "") :
        info(t), geass(g) {}

};
void initialize(codeGeass* array)
{
	for (int x = 0; x < 4096; x++)
	{
		if (x < 256)
		{
			char c = char(x);
			string s(1, c);
			codeGeass temp(ACTIVE); 
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
int main()
{
  
    codeGeass* dict = new codeGeass[4096];
    initialize(dict);
	int current;
	ifstream file("compout");
	int prev_code;
	string output;
	int count = 0;
	int prev_add = 255;
	ofstream outFile("decompout");
	
	while (file >> current) //eof returns true if next character 
	{
		
		if (count == 0)
		{
			cout << dict[current].geass << " ";
			outFile << dict[current].geass << " ";
			count++;
			prev_code = current;
		}
		else
		{
			if (dict[current].info != EMPTY)
			{
				cout << dict[current].geass << " ";
				outFile << dict[current].geass << " ";
				if (prev_add != 4095)
				{
					string insert = dict[prev_code].geass + dict[current].geass[0];
					codeGeass to_be_inserted(ACTIVE, insert);
					prev_add++;
					dict[prev_add] = to_be_inserted;
				}
				prev_code = current;
			}
			else
			{
				string insert = dict[prev_code].geass + dict[prev_code].geass[0];
				cout << insert << " ";
				outFile << insert << " ";
				codeGeass to_be_inserted(ACTIVE, insert);
				dict[current] = to_be_inserted;
				prev_code = current;
				prev_add = current;

			}
		}
	}
}
    

