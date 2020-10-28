#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

void printHelp();
void initPF();
void functAddItems();
void mergeTrace();

void mf(ifstream& fin1, ifstream& fin2, ofstream& fout, int n);

inline string& trim(string &str)
{
	string::reverse_iterator rev_iter=find_if(str.rbegin(),str.rend(),not1(ptr_fun<int>(::isspace)));
    str.erase(rev_iter.base(),str.end());
    return str;
}


typedef void (*PF)();

PF pf[2];

int main(void)
{
	int mode = 0;
	initPF();			//initialize all the pf
	do{
		printHelp();
		cin >> mode;
		if(mode == 0) break;
		pf[mode-1]();

		cout << "Print any key to return." << endl;
		setbuf(stdin, NULL);
		getchar();
	}while(mode);

	return 0;
}

void initPF()
{
	pf[0] = functAddItems;
	pf[1] = mergeTrace;
}

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
				trim(line);
				fout << line << " " << lable << endl;
			}
			fout.close();
			fin.close();
		}
		return;
}

void mergeTrace()
{
	int n;
	int t1, t2;
	uint64_t temp;
	string ifile1, ifile2, ofile;
	system("clear");
	cout << "You chosed \"Merge traces\"." << endl << endl;
	cout << "The 1st filename: ";
	cin >> ifile1;
	cout << "The 2nd filename: ";
	cin >> ifile2;
	ifstream fin1(ifile1.c_str());
	ifstream fin2(ifile2.c_str());
	if(!fin1)
	{
		cout << "Error opening " << ifile1 << endl;
		return;
	}
	if(!fin2)
	{
		cout << "Error opening " << ifile2 << endl;
		fin1.close();
		return;
	}
	cout << "The Output filename: ";
	cin >> ofile;
	ofstream fout(ofile.c_str());

	cout << "n = ";
	cin >> n;

	//cout << fin1.eof() << endl;

	mf(fin1, fin2, fout, n);

	fout.close();
	fin2.close();
	fin1.close();
	return;
}

void printHelp()
{
	system("clear");
	cout << "Please select a function:" << endl;
	cout << "1. Add items in trace." << endl;
	cout << "2. Merge traces." << endl;
	cout << "Type \"0\" for quit." << endl << endl;
	cout << "Your choice: ";	
	return;
}

void mf(ifstream& fin1, ifstream& fin2, ofstream& fout, int n)
{
	long x1, x2;
	//cout << "Entered mf" << endl;
	int i;
	int64_t t1, t2;
	int64_t temp;
	if(fin1.eof())
	{
		//cout << "case 1" << endl;
		while(!fin2.eof())
		{
			for(i=0; i<n-1; i++)
			{
				fin2 >> temp;
				fout << temp << " ";
			}
			fin2 >> temp;
			fout << temp << endl;
		}
		return;
	}
	if(fin2.eof())
	{
		//cout << "case 2" << endl;
		while(!fin1.eof())
		{
			for(i=0; i<n-1; i++)
			{
				fin1 >> temp;
				fout << temp << " ";
			}
			fin1 >> temp;
			fout << temp << endl;
		}
		return;
	}
	fin1 >> t1;
	fin2 >> t2;
	if (t1 <= t2)
	{
		//cout << "t1 = " << t1 << " t2 = " << t2 << endl;
		//cout << "case 3.1." << endl;
		fout << t1 << " ";
		for(i=0; i<n-2; i++)
		{
			fin1 >> temp;
			fout << temp << " ";
		}
		fin1 >> temp;
		fout << temp << endl;
		//fin2.seekg(-1, ios::cur);
		//fin2.seekg(y2, ios::beg);
	}
	else
	{
		//cout << "case 3.2" << endl;
		fout << t1 << " ";
		for(i=0; i<n-2; i++)
		{
			fin2 >> temp;
			fout << temp << " ";
		}
		fin2 >> temp;
		fout << temp << endl; 
		//fin1.seekg(-1, ios::cur);
		//fin2.seekg(y2, ios::beg);
	}
	mf(fin1, fin2, fout, n);
}