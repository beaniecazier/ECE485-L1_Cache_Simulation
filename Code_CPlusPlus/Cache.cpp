#include "Cache.h"

Cache::Cache(int associativity, bool verbose)
{
	this.verbose = verbose;
	sets = new Set[NUM_SETS];
	for (int i = 0; i < NUM_SETS; i++) //classes are defined with uppercase; sets is a variable
	{
		sets[i] = new Set(associativity, verbose);
	}
}

Cache::~Cache()
{
	// delete dynamic variables
	for (int i = 0; i < NUM_SETS; i++)
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
	for( int i = NUM_SETS; i>0; --i)
	{
		if( sets[ i].reset() ) //expects a 0 for normal, -1 (or any value but 0) for failure
			--failures;
	}
	return failures; //0 if no failues, a negative number for the number of failures.
}

int Caches::printCache()
{
	int setsContainingData = 0;
	for( int i = NUM_SETS; i>0; --i)
	{
		setsContainingData = setsContainingData + sets[ i].print();
	}
	return setsContainingData; //0 if no sets contain data
	//If sets.print passes back a 1 when that set contains data, then the return value for this function
	//will be number of sets containing data
	//If sets.print instead passes back the number of ways in that set which contain data, then the return 
	//value for this function will be the number of total ways across the cache that contain data.
}

int Caches::clearCache()
{
	int failures = 0;
	for( int i = NUM_SETS; i>0; --i)
	{
		if( sets[ i].clear() ) //expects a 0 for normal, -1 (or any value but 0) for failure
			--failures;
	}
	return failures; //0 if no failues, a negative number for the number of failures.
}





				     
				     
