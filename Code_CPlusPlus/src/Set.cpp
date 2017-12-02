#include "Set.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

Set::Set(int a, int i, bool v, int aSize, int tSize, int oSize)
{
 	verbose = v;
	associativity = a;
	index = i;
 	lines = new Line[associativity];
	first = 0;
	last = 0;
	addressBitLength = aSize;
	tagBitLength = tSize;
	offsetBitLength = oSize;
}

Set::~Set()
{
	//for (int i = 0; i < associativity; i++)
	//{
		//delete &(lines[i]);
	//}
 	delete [] lines;
}

int Set::read(unsigned int tag)
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
				touch(tag);
				return HIT;
			}
		}
		if (isFull())
		{
			evict();
		}
		handleReadMiss(tag);
	} 
	else 
	{
		handleReadMiss(tag);
	}
	return MISS;
}

void Set::handleReadMiss(unsigned int tag)
{
	if (verbose)
	{
		//read from L2
		cout << "Read from L2 " << htos(reconstructAddress(tag)) << endl;
	}
	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].mesi == INVALID)
		{
			add(tag, SHARED);
			break;
		}
	}
}

int Set::write(unsigned int tag)
{
	if (count == 0)		// if invalid set
	{
		handleWriteMiss(tag);
		return MISS;
	}
	else
	{
		for (int i = 0; i < associativity; i++)
		{
			if (lines[i].tag == tag)		// find a hit
			{
				if (lines[i].mesi == EXCLUSIVE) lines[i].mesi = MODIFIED;
				else if (lines[i].mesi != MODIFIED) lines[i].mesi = EXCLUSIVE;
				touch(tag);					// this handles LRU for this hit
				return HIT;
			}
		}
		if (isFull())
		{
			evict();
		}
		handleWriteMiss(tag);
		return MISS;
	}
}

void Set::handleWriteMiss(unsigned int tag)
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
				cout << "Read from L2 " << htos(reconstructAddress(tag)) << " for ownership\n";
			}
			// read data from L2
			lines[i].mesi = SHARED;	// set mesi for that data

			if (verbose)
			{
				//msg: Write to L2
				cout << "Write to L2 " << htos(reconstructAddress(tag)) << endl;
			}
			// write new data in that spot
			add(tag, EXCLUSIVE);
			return;
		}
	}
}

void Set::readFromL2(unsigned int tag)
{
	// called on 4
	// have to set mesi to shared

	for (int i = 0; i < associativity; i++)
	{
		if (lines[i].tag == tag)
		{
			if (lines[i].mesi == MODIFIED || lines[i].mesi == EXCLUSIVE)
			{
				cout << "Return data to L2 " << htos(reconstructAddress(tag)) << endl;
			}
			lines[i].mesi = SHARED;
			touch(tag);
		}
	}
}

void Set::evict()
{
	int indexToEvict;
	for (indexToEvict = 0; indexToEvict < associativity; indexToEvict++)
	{
		if (lines[indexToEvict].LRU == count - 1) break;
	}
	invalidate(lines[indexToEvict].tag);
}

void Set::invalidate(unsigned int tag)
{
	for(int i = 0; i < associativity; i++)
	{
		if (lines[i].tag == tag)
		{
			switch (lines[i].mesi)
			{
			case MODIFIED:
			//case EXCLUSIVE:
				if (verbose)
				{
					// write through
					// msg: write to L2
					cout << "write to L2 " << htos(reconstructAddress(tag)) << endl;
				}
				break;
			case SHARED:
				break;
			default:
				//cerr << "error cant invalidate invalid line dumbass\n";
				break;
			}
			remove(tag);
			lines[i].invalidate();
		}
	}
}

void Set::reset()
{
	for (int i = 0; i < associativity; i++)
	{
		invalidate(lines[i].tag);
	}
}

void Set::print()
{
	//Check if the current set is valid
	if (count > 0)
	{
		cout << setw(7) << htos(index) << setfill(' ') << "\t | ";
		//For loop to print data from the sets
		for (int i = 0; i < associativity; i++)
		{	
			if (lines[i].mesi != INVALID)
			{
				cout << setw(7) << htos(lines[i].tag) << " : "
					 << setw(4) << lines[i].LRU << " : "
					 << setw(10) << lines[i].printMESI() << " | ";
			}
			else 
			{
				cout << "        :      :            | ";
			}
		}
		cout << endl;
	}
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

void Set::add(unsigned int tag, MESI state)
{
	// add to front
	int indexToAdd;
	for (indexToAdd = 0; indexToAdd < associativity; indexToAdd++)
	{
		if (lines[indexToAdd].tag == tag)
		{
			break;
		}
	}
	if (first == 0)
	{
		first = &lines[indexToAdd];
		first->next = first->prev = 0;
		last = first;
		lines[indexToAdd].LRU = 0;
		lines[indexToAdd].mesi = state;
		count++;
		return;
	}
	lines[indexToAdd].next = first;
	first->prev = &lines[indexToAdd];
	first = &lines[indexToAdd];
	lines[indexToAdd].prev = 0;
	count++;
	lines[indexToAdd].mesi = state;

	Line* temp = first;
	int lru = 0;
	while (temp != 0)
	{
		temp->LRU = lru;
		lru++;
		temp = temp->next;
	}
}

void Set::remove(unsigned int tag)
{
	// remove from last
	last = last->prev;
	last->next = 0;
	count--;
	if (count < 0)
	{
		cerr << htos(tag) << " was being removed and brought the overall valid line count of " 
			 << htos(reconstructAddress(tag)) << " to " << count << endl;
		count = 0;
	}
}

void Set::touch(unsigned int tag)
{
	Line* temp = first;
	while (temp)
	{
		if (temp->tag == tag) break;
	}
	if (temp == 0)
	{
		return;
	}
	temp->prev = temp->next;
	temp->next = first;
	first = temp;
}

string Set::htos(unsigned int n)
{
	string ret;
	stringstream ss;
	ss << hex << n;
	ret = ss.str();
	
	for(int i = 0; i < ret.size(); i++) 
	{
		if (ret.at(i) != 'd' && ret.at(i) != 'b')
		{
			ret.at(i) = toupper(ret.at(i));
		}
		else if (ret.at(i) != 'D' || ret.at(i) != 'B')
		{
			ret.at(i) = tolower(ret.at(i));
		}
	}
	return ret;
}

unsigned int Set::reconstructAddress(unsigned int tag)
{
	return tag << offsetBitLength + tagBitLength + index << offsetBitLength;
}