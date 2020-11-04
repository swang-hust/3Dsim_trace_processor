#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <cmath>

using namespace std;

#define PAGE_SIZE 4  //KB
#define PAGE_NUM 16777216
#define GB_CAP (1024 * 1024)    //KB
#define SECTOR_PER_PAGE 8
#define USER_ID 0

int *unique_lpn = nullptr;
int *fingerprint = nullptr;
double *Pzipf = nullptr;

string ifilename = "/home/nvm/traces/fileserver64.trace";
string ofilename = "/home/nvm/dealed_traces/fileserver64.trace";

int get_unique_lpn_nb(const string tracefile_name);
void init_fingerprint(int unique_lpn_nb);
int fp_generator(int lpn, int unique_lpn_nb);
void process(int unique_lpn_nb);

int main(int argc, char const *argv[])
{
    int ssd_size = (PAGE_SIZE * PAGE_NUM) / GB_CAP;
    cout << "ssd capacity = " << ssd_size << " (GB)" << endl;

    string line, lable;
    int unique_lpn_nb = get_unique_lpn_nb(ifilename);
    cout << "unique lpn number = " << unique_lpn_nb << endl;
    
    init_fingerprint(unique_lpn_nb);

    cout << "begin..." << endl;
    process(unique_lpn_nb);
    cout << "end" << endl;
    return 0;
}

int get_unique_lpn_nb(const string tracefile_name) {
    int res = 0;

    int64_t time_t;
    int device, lsn, size, ope;
    int lpn;

    //Malloc unique_lpn
    unique_lpn = (int *)malloc(sizeof(int) * PAGE_NUM);
    if (unique_lpn == nullptr) {
        cout << "Error: unique_lpn malloc error!" << endl;
        exit(0);
    }
    memset(unique_lpn, 0, sizeof(int) * PAGE_NUM);  

    ifstream fin(tracefile_name.c_str());
    if(!fin)
    {
        cout << "Error opening " << tracefile_name << endl;
    }
    while(fin >> time_t >> device >> lsn >> size >> ope) {
        assert(size % SECTOR_PER_PAGE == 0);
        assert(lsn % SECTOR_PER_PAGE == 0);
        while (size != 0) {
            lpn = lsn / SECTOR_PER_PAGE;
            if (unique_lpn[lpn] == 0) {
                unique_lpn[lpn] = 1;
                res ++;
            }
            lsn += SECTOR_PER_PAGE;
            size -= SECTOR_PER_PAGE;
        }
    }
    fin.close();
    return res;
}

void init_fingerprint(int unique_lpn_nb) {
    int i;
	double a=0.2, sum = 0.0;
    
    Pzipf=(double *)calloc(unique_lpn_nb + 1, sizeof(double));
    fingerprint=(int *)calloc(unique_lpn_nb + 1, sizeof(int));

    assert (Pzipf != nullptr);
    assert(fingerprint != nullptr);

    for(i=0; i<=unique_lpn_nb; i++)
	{
		Pzipf[i]=0.0;
		fingerprint[i]=-1;
	}

	for(i=1; i<=unique_lpn_nb; i++)
	{
		sum+=1/pow((double)i, a);
	}

	for(i=1; i<=unique_lpn_nb; i++)
	{
		Pzipf[i]=Pzipf[i-1]+1/pow((double)i, a)/sum;
	}
}

int fp_generator(int lpn, int unique_lpn_nb) {
    int fp = -1;

    double data = ((double)rand() + 1) / ((double)RAND_MAX + 2);
	int64_t low = 0, high = unique_lpn_nb, mid;
	while (low < high) {
		mid = low + (high - low + 1) / 2;

		if (data <= Pzipf[mid]) {
			if (data > Pzipf[mid - 1]) {
				fp = mid;
				break;
			}
			high = mid - 1;
		}
		else {
			low = mid;
		}
	}
    assert(fp != -1);
    return fp;
}

void process(int unique_lpn_nb) {
    ifstream fin(ifilename.c_str());
    if(!fin)
    {
        cout << "Error opening " << ifilename << endl;
    }
    ofstream fout(ofilename.c_str());
    if(!fout)
    {
        cout << "Error opening " << ofilename << endl;
    }

    int64_t time_t;
    int device, lsn, size, ope;
    int lpn, fp;

    while(fin >> time_t >> device >> lsn >> size >> ope) {
        assert(size % SECTOR_PER_PAGE == 0);
        assert(lsn % SECTOR_PER_PAGE == 0);
        while (size != 0) {
            lpn = lsn / SECTOR_PER_PAGE;
            fp = fp_generator(lpn, unique_lpn_nb);
            fout << time_t << " " << device << " " << lsn << " " << SECTOR_PER_PAGE << " " << ope << " " << USER_ID << " " << fp << endl;
            lsn += SECTOR_PER_PAGE;
            size -= SECTOR_PER_PAGE;
        }
    }

    fin.close();
    fout.close();
}

// void trace_(const string tracefile_name) {
//     int64_t time_t;
//     int device, lsn, size, ope;
//     int lpn;

//     //Malloc unique_lpn
//     unique_lpn = (int *)malloc(sizeof(int) * PAGE_NUM);
//     if (unique_lpn == nullptr) {
//         cout << "Error: unique_lpn malloc error!" << endl;
//         exit(0);
//     }
//     memset(unique_lpn, 0, sizeof(int) * PAGE_NUM);  

//     ifstream fin(tracefile_name.c_str());
//     string lpn;
//     string tmp;
//     if(!fin)
//     {
//         cout << "Error opening " << tracefile_name << endl;
//     }
//     while(fin >> time_t >> device >> lsn >> size >> ope) {
//         assert(size % SECTOR_PER_PAGE == 0);
//         assert(lsn % SECTOR_PER_PAGE == 0);
//         while (size != 0) {
            
//         }
//     }

//     fin.close();
// }