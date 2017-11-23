#include "Cache.h"

Cache::Cache(int setSize, int associativity, bool verbose)
{
	this.setSize = setSize;
	this.associativity = associativity;
	this.verbose = verbose;
	sets = new Set[setSize];
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
		delete set[i];
	}
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
	return address = address >> (PROC_SIZE - TAG_BITS); 
}


//Public function definitions here
int Cache::readData(int address)
{
	totalOperations++;
	return sets[ getIndex( address) ].read( getTag( address) );
}

int Cache::writeData(int address)
{
	return sets[ getIndex( address) ].write( getTag( address) );
}

int Cache::invalidataData(int address)
{
	return sets[ getIndex( address) ].invalidate( getTag( address) );
}

int Cache::readDataToL2(int address)
{
	return sets[ getIndex( address) ].readToL2( getTag( address) );
}

int Cache::resetAll()
{
	int failures = 0;
	for( int i = setSize; i>0; --i)
	{
		if( sets[ i].reset() ) //expects a 0 for normal, -1 (or any value but 0) for failure
			--failures;
	}
	return failures; //0 if no failues, a negative number for the number of failures.
}

void Cache::printCache()
{
	for( int i = 0; i < setSize; i++)
	{
		cout << i
		sets[ i].print();
	}
}

void Cahche::printStatistics()
{
	cout << "Out of " << totalOperations << " total operations\n"
		 << "There were " << CacheReads << " cache reads and " << CacheWrites << " cache writes\n";
		 << "The hit and miss rate was " << HitCount << " and " << MissCount << "\n";
}

int Cache::clearCache()
{
	int failures = 0;
	for( int i = setSize; i>0; --i)
	{
		if( sets[ i].clear() ) //expects a 0 for normal, -1 (or any value but 0) for failure
			--failures;
	}
	return failures; //0 if no failues, a negative number for the number of failures.
}
