#include "Set.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

Set::Set(int a, bool v)
{
 	verbose = v;
	associativity = a;
 	lines = new Line[associativity];
	//for (int i = 0; i < associativity; i++)
	//{
		//lines[i] = *(new Line());
	//}
}

Set::~Set()
{
	//for (int i = 0; i < associativity; i++)
	//{
		//delete &(lines[i]);
	//}
 	delete [] lines;
}

int Set::read(int tag, int address)
{
	//Check for a valid in the set of data
	if (count > 0)
	{
		//For loop to check validility of data from the sets
		for (int i = 0; i < associativity; i++)
		{
			//Check to see if any of the tags match
			if (lines[i].mesi != INVALID && tag == lines[i].tag)
			{
				updateLRU(tag);
				// update hit count
				return 1;
			}
		}
		if (isFull())
		{
			readEvict(address);
		}
		if (verbose)
		{
			//read from L2
			cout << "Read from L2 " << hex << address << endl;
		}
		for (int i = 0; i < associativity; i++)
		{
			if (lines[i].mesi = INVALID)
			{
				lines[i].tag = tag;
				lines[i].mesi = SHARED;
				count++;
			}
		}
	} 
	else 
	{
		lines[0].tag = tag;
		lines[0].mesi = SHARED;
		if (verbose)
		{
			//read from L2
			cout << "Read from L2 " << hex << address << endl;
		}
		count++;
	}
	updateLRU(tag);
	return 0;
}

int Set::write(int tag, int address)
{
	if (count == 0)		// if invalid set
	{
		handleWriteMiss(tag, address);
		return MISS;
	}
	else
	{
		for (int i = 0; i < associativity; i++)
		{
			if (lines[i].tag == tag)		// find a hit
			{
				lines[i].mesi = MODIFIED;
				updateLRU(tag);
				return HIT;
			}
		}
		if (isFull())
		{
			writeEvict();
		}
		handleWriteMiss(tag, address);
	}
}

void Set::handleWriteMiss(int tag, int address)
{
	for (int i = 0; i < associativity; i++)
	{
		// find the first empty
		if (lines[i].mesi == INVALID)
		{
			lines[i].tag = tag;		// set tag
			
			if (verbose)
			{
				// msg: RFO
				cout << "Read from L2 " << hex << address << " for ownership\n";
			}
			// read data from L2
			lines[i].mesi = SHARED;	// set mesi for that data

			if (verbose)
			{
				//msg: Write to L2
				cout << "Write to L2 " << hex << address << endl;
			}
			// write new data in that spot
			lines[i].mesi = EXCLUSIVE;

			updateLRU(tag);			// say that tag is newest touch
			count++;				// increase the count
			return;
		}
	}
}

void Set::invalidate(int tag, int address)
{
	for(int i = 0; i < associativity; i++)
	{
		if (lines[i].tag == tag)
		{
			switch (lines[i].mesi)
			{
			case MODIFIED:
			case EXCLUSIVE:
				if (verbose)
				{
					// write through
					// msg: write to L2
					cout << "write to L2 " << hex << address;
				}
				break;
			case SHARED:
				break;
			default:
				// cout error cant invalidate invalid line dumbass
				break;
			}
			lines[i].invalidate();
			count--;
		}
	}
	if (count <= 0)
	{
		count = 0;
	}
}

void Set::invalidate(int address)
{
	for(int i = 0; i < associativity; i++)
	{
		invalidate(lines[i].tag, address);
	}
}

int Set::readFromL2(int tag, int address)
{
	// called on 4
	// have to set mesi to shared

	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].tag == tag)
		{
			if (lines[i].mesi == MODIFIED /*|| lines[i].mesi == EXCLUSIVE*/)
			{
				cout << "Return data to L2 " << hex << address << endl;
			}
			lines[i].mesi = SHARED;
			updateLRU(tag);
			return HIT;
		}
	}
}

void Set::reset()
{
	for (int i = 0; i < associativity; i++)
	{
		lines[i].invalidate();
	}
}

void Set::print(int address)
{
	//Check if the current set is valid
	if (count > 0)
	{
		//For loop to print data from the sets
		for (int i = 0; i < associativity; i++)
		{	
			if (lines[i].mesi != INVALID)
			{
				cout << setw(7) << hex << address 
					 << "\t" << setfill(' ') 
					 << setw(3) << lines[i].LRU 
					 << setw(7) << hex << lines[i].tag 
					 << setw(10) << lines[i].printMESI();
			}
		}
		cout << endl;
	}
}

void Set::updateLRU(int tag)
{
	int lastLRU;
	// find most recently used
	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].mesi != INVALID && lines[i].tag == tag)
		{
			lastLRU = lines[i].LRU;
			lines[i].LRU = count -1;
		}
	}
	//update other most recently used lines
	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].mesi != INVALID && lines[i].LRU > lastLRU && lines[i].tag != tag)
		{
			lines[i].LRU--;
		}
	}
}

int Set::checkLRU()
{
	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].LRU == 0) return i;
	}
}

void Set::readEvict(int address)
{
	if (verbose)
	{
		// write message
	}
	lines[checkLRU()].invalidate();
	count--;
}

void Set::writeEvict()
{
	lines[checkLRU()].invalidate();
	count--;
}

bool Set::isFull()
{
	int count = 0;
	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].mesi == INVALID)
		{
			count++;
		}
	}
	return (count > 0) ? false : true;
}
