#include "Cache.h"
#include <iostream>
#include <iomanip>

using namespace std;

Cache::Cache(int size, int a, bool v)
{
	setSize = size;
	associativity = a;
	verbose = v;
	sets = new Set*[setSize];
	HitCount = 0;
	MissCount = 0;
	CacheReads = 0;
	CacheWrites = 0;
	totalOperations = 0;
	for (int i = 0; i < setSize; i++) //classes are defined with uppercase; sets is a variable
	{
		sets[i] = new Set(associativity, verbose);
	}
}

Cache::~Cache()
{
	// delete dynamic variables
	for (int i = 0; i < setSize; i++)
	{
		delete sets[i];
	}
	delete [] sets;
}

//Private function definitions here
unsigned int Cache::getIndex(unsigned int address)
{
	address = address << TAG_BITS; //bitshift to left to erase tag bits
	return address = address >> (TAG_BITS + OFFSET_BITS); //bitshift to right to erase offset bits and 
							     //shift index bits back into position.
}

unsigned int Cache::getTag(unsigned int address)
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
	unsigned int tag = getTag(address);
	unsigned int index = getIndex(address);
	if (verbose) cout << "INDEX: " << hex << index << ", TAG: " << hex << tag << endl;
	int hit = sets[index]->read(tag, address);
	HitCount += (hit) ? 1: 0;
	MissCount += (!hit) ? 1 : 0;
}

void Cache::writeData(int address)
{
	int hit = sets[ getIndex( address) ]->write( getTag( address), address);
	totalOperations++;
	CacheWrites++;
	HitCount += (hit) ? 1 : 0;
	MissCount += (!hit) ? 1 : 0;
}

void Cache::invalidate(int address)
{
	sets[ getIndex( address) ]->invalidate( getTag( address) );
}

void Cache::readFromL2(int address)
{
	int hit = sets[ getIndex( address) ]->readFromL2( getTag( address), address);
	totalOperations++;
	CacheWrites++;
	HitCount += (hit) ? 1 : 0;
	MissCount += (!hit) ? 1 : 0;
}

void Cache::resetAll()
{
	for (int i = setSize; i > 0; --i)
	{
		sets[i]->reset();
	}
	totalOperations = 0;
	CacheReads = 0;
	CacheWrites = 0;
	HitCount = 0;
	MissCount = 0;
}

void Cache::printCache()
{
    for (int i = 0; i < associativity; i++)
	{
		cout << setw(7) << "INDEX" << "\t" << setfill(' ') 
			<< setw(3) << "LRU" 
			<< setw(7) << "TAG" 
			<< setw(10) << "MESI";
	}
	cout << endl;
	for( int i = 0; i < setSize; i++)
	{
		sets[ i]->print(i);
	}
}

void Cache::printStatistics()
{
	double hitRate = ((double)HitCount) / ((double)totalOperations) * 100.0;
	double missRate = ((double)MissCount) / ((double)totalOperations) * 100.0;
	
	cout << "out of " << totalOperations << " total operations\n"
		 << "There were " << CacheReads << " cache reads and " << CacheWrites << " cache writes\n"
		 << "The hit and miss rate was " << setprecision(2) << hitRate << "% and " << missRate << "%\n";
}
