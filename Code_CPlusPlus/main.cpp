#include <iomanip>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <exception>
#include <string>
#include "Cache.h"

using namespace std;

#define NUM_SETS	16384 //because 16K sets = 2^14
#define INSTR_ASSOC	2
#define DATA_ASSOC	4

void ResetCache();
bool checkFlags(char* arg, string flag);
void printCaches();

Cache* instructionCache;
Cache* dataCache;

int main(int argc, char* argv[])
{
	string line;
	ifstream file;
	bool verbose = false;
	int count = 0;
	
	for (int i = 0; i < argc; i++)
	{
		verbose = verbose | checkFlags(argv[i], "-D");
	}

	instructionCache = new Cache(NUM_SETS, INSTR_ASSOC, verbose);
	dataCache = new Cache(NUM_SETS, DATA_ASSOC, verbose);

	verbose = false;
	for (int i = 0; i < argc; i++)
	{
		verbose = verbose | checkFlags(argv[i], "-A");
	}

	verbose = true;

	try
	{
		file.open(/*argv[1]*/"traceFile.txt");
		if (file.is_open())
		{
			while (getline(file, line))
			{
				istringstream iss(line);
				int instruction, address;
				// process pair (a,b)
				if (!(iss >> instruction >> hex >> address)) { break; } // error

				// this is were we actually handle cache instructions
				//cout << a << ',' << hex << b << '\n';
				//

				switch (instruction)
				{
				case 0:
					//read data
					dataCache->readData(address);
					break;
				case 1:
					// write data
					dataCache->writeData(address);
					break;
				case 2:
					// instruction fetch
					// instruction read
					instructionCache->readData(address);
					break;
				case 3:
					// invalidate
					dataCache->invalidate(address);
					break;
				case 4:
					dataCache->readFromL2(address);
					break;
				case 8:
					// clear reset
					dataCache->resetAll();
					instructionCache->resetAll();
					break;
				case 9:
					// print all
					instructionCache->printCache();
					dataCache->printCache();
					break;
				default:
					cout << instruction << " found at line " << count << ", is not a valid instruction for a cache" << endl;
					break;
				}
				count++;

				if (verbose)
				{
					instructionCache->printCache();
					dataCache->printCache();
				}
			}
		}
	}
	catch (exception e)
	{
		cout << e.what() << "\n\n";
	}
	instructionCache->printStatistics();
	dataCache->printStatistics();
	file.close();
	getchar();
	return 0;
}

void printCaches()
{
}

bool checkFlags(char* arg, string flag)
{
	const char* s = arg;
	string str = string(s);
	if (str.find(flag) == string::npos)
	{
		int len = str.length();
		if (len == 2)
		{
			return true;
		}
	}
	return false;
}

void ResetCache()
{
	instructionCache->resetAll();
	dataCache->resetAll();
}
