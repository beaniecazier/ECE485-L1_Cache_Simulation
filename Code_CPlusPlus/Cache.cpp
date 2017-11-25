#include "Cache.h"
#include <iostream>

using namespace std;

Cache::Cache(int size, int a, bool v)
{
	setSize = size;
	associativity = a;
	verbose = v;
	//sets = new Set(a, v)[setSize];
	HitCount = 0;
	MissCount = 0;
	CacheReads = 0;
	CacheWrites = 0;
	totalOperations = 0;
	//for (int i = 0; i < setSize; i++) //classes are defined with uppercase; sets is a variable
	//{
		//sets[i] = new Set(associativity, verbose);
	//}
}

Cache::~Cache()
{
	// delete dynamic variables
	//for (int i = 0; i < setSize; i++)
	//{
		//delete set[i];
	//}
	delete [] sets;
}

//Private function definitions here
int Cache::getIndex(int address)
{
	address = address << TAG_BITS; //bitshift to left to erase tag bits
	return address = address >> (TAG_BITS + OFFSET_BITS); //bitshift to right to erase offset bits and 
							     //shift index bits back into position.
}

int Cache::getTag(int address)
{
	//bitshift to the right 20 bits (32 proc bits - 12 tag bits)
	int shiftAmount = (PROC_SIZE - TAG_BITS);
	return address = address >> shiftAmount; 
}

//Public function definitions here
void Cache::readData(int address)
{
	totalOperations++;
	CacheReads++;
	int hit = sets[ getIndex( address) ].read( getTag( address) );
	HitCount += (hit) ? 1: 0;
	MissCount += (!hit) ? 1 : 0;
}

void Cache::writeData(int address)
{
	int hit = sets[ getIndex( address) ].write( getTag( address) );
	totalOperations++;
	CacheWrites++;
	HitCount += (hit) ? 1 : 0;
	MissCount += (!hit) ? 1 : 0;
}

int Cache::invalidate(int address)
{
	sets[ getIndex( address) ].invalidate( getTag( address) );
}

int Cache::readFromL2(int address)
{
	return sets[ getIndex( address) ].readFromL2( getTag( address) );
}

int Cache::resetAll()
{
	for (int i = setSize; i > 0; --i)
	{
		sets[i].reset();
	}
	totalOperations = 0;
	CacheReads = 0;
	CacheWrites = 0;
	HitCount = 0;
	MissCount = 0;
}

void Cache::printCache()
{
	for( int i = 0; i < setSize; i++)
	{
		cout << i
		sets[ i].print();
	}
}

void Cache::printStatistics()
{
	cout << "Out of " << totalOperations << " total operations\n"
		 << "There were " << CacheReads << " cache reads and " << CacheWrites << " cache writes\n"
		 << "The hit and miss rate was " << HitCount << " and " << MissCount << "\n";
}
