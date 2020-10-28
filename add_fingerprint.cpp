#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>

using namespace std;

#define PAGE_SIZE 4  //KB
#define PAGE_NUM 16777216
#define GB_CAP (1024 * 1024)    //KB

int *unique_lpn;

int main(int argc, char const *argv[])
{
    int ssd_size = (PAGE_SIZE * PAGE_NUM) / GB_CAP;
    cout << "ssd capacity = " << ssd_size << " (GB)" << endl;
    return 0;
    cout << "begin..." << endl;
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
            return 0;
        }
        while(getline(fin, line))
        {
            fout << line << " " << lable << endl;
        }
        fout.close();
        fin.close();
    }
    cout << "end..." << endl;
    return 0;
}
