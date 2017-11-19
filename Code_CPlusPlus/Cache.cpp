#include "Cache.h"


Cache::Cache(int associativity, bool verbose)
{
	
	for each (Set set in sets) //classes are defined with uppercase; sets is a variable
	{
		set = new Set(associativity, verbose);
	}
}

Cache::~Cache()
{
	//delete everything!! Maybe?
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


				     
				     
