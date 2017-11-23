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

Cache* instructionCache;
Cache* dataCache;

int main(int argc, char* argv[])
{
	string line;
	ifstream file;
	bool verbose = false;
	
	for (int i = 0; i < argc; i++)
	{
		verbose |= checkFlags(argv[i]);
	}

	instructionCache = new Cache(NUM_SETS, INSTR_ASSOC);
	dataCache = new Cache(NUM_SETS, DATA_ASSOC);

	try
	{
		file.open(argv[1]);
		if (file.is_open())
		{
			while (getline(file, line))
			{
				istringstream iss(line);
				int a, b;
				// process pair (a,b)
				if (!(iss >> a >> hex >> b)) { break; } // error


														// this is were we actually handle cache instructions
				cout << a << ',' << hex << b << '\n';
				//
			}
		}
	}
	catch (exception e)
	{
		cout << e.what() << "\n\n";
	}

	file.close();
	return 0;
}

bool checkFlags(char* arg)
{
}

void ResetCache()
{
	if (instructionCache->resetAll() < 0)
	{
		cout << "ERROR RESETING INSTRUCTION CACHE\n";
	}
	if (dataCache->resetAll() < 0)
	{
		cout << "ERROR RESETING DATA CACHE\n";
	}
}
