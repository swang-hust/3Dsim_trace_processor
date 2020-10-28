#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

void functAddItems()
{
		string ifilename;
		string ofilename;
		string line, lable;
		system("clear");
		cout << "You chosed \"Add items\"." << endl << endl;
		cout << "Input filename name: ";
		cin >> ifilename;
		ifstream fin(ifilename.c_str());
		if(!fin)
		{
			cout << "Error opening " << ifilename << endl;
		}
		else
		{
			cout << "Output filename :";
			cin >> ofilename;
			cout << "label :";
			cin >> lable;
			ofstream fout(ofilename.c_str());
			if(!fout)
			{
				cout << "Error opening " << ifilename << endl;
				fin.close();
				return;
			}
			while(getline(fin, line))
			{
				fout << line << " " << lable << endl;
			}
			fout.close();
			fin.close();
		}
		return;
}

int main(int argc, char const *argv[])
{
    functAddItems();
    return 0;
}
