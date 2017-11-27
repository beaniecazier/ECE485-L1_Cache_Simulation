#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
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
void printCachesStats();

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

	verbose = true;

	cout << "Initializing Instruction Cache\n";
	instructionCache = new Cache(NUM_SETS, INSTR_ASSOC, verbose);
	cout << "Initializing Data Cache\n";
	dataCache = new Cache(NUM_SETS, DATA_ASSOC, verbose);

	verbose = false;
	for (int i = 0; i < argc; i++)
	{
		verbose = verbose | checkFlags(argv[i], "-A");
	}

	verbose = true;
	
	if (verbose) cout << "Opening file\n";

	try
	{
		file.open(/*argv[1]*/"traceFile.txt");
		if (file.is_open())
		{
			//if (verbose) cout << argv[1] << " was opened successfully\n";
			while (getline(file, line))
			{
				istringstream iss(line);
				int instruction, address;
				// process pair (a,b)
				if (!(iss >> instruction >> hex >> address)) { break; } // error

				// this is were we actually handle cache instructions
				if (verbose) cout << instruction << ',' << hex << address << '\n';

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
					printCaches();
					break;
				default:
					cout << instruction << " found at line " << count << ", is not a valid instruction for a cache" << endl;
					break;
				}
				count++;

				if (verbose)
				{
					printCaches();
				}
			}
		}
	}
	catch (exception e)
	{
		cout << e.what() << "\n\n";
	}
	printCachesStats();
	file.close();
	getchar();
	return 0;
}

void printCaches()
{
	cout << "Here is are the valid contents of the L1 Instruction Cache\n";
	instructionCache->printCache();
	cout << "\n\n";
	cout << "Here is are the valid contents of the L1 Data Cache\n";
	dataCache->printCache();
	cout << "\n\n";
}

void printCachesStats()
{
	cout << "The statistics for the L1 Instruction Cache are ";
	instructionCache->printStatistics();
	cout << "The statistics for the L1 Data Cache are ";
	dataCache->printStatistics();
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
