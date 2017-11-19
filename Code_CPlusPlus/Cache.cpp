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
int getIndex(int address)
{
	address = address << TAG_BITS; //bitshift to left to erase tag bits
	return address = addres >> (TAG_BITS + OFFSET_BITS); //bitshift to right to erase offset bits and 
							     //shift index bits back into position.
}

int getTag(int address)
{
	//bitshift to the right 20 bits (32 proc bits - 12 tag bits)
	return address = address >> ((PROC_SIZE - TAG_BITS); 
}


//Public function definitions here
Cache::readData(int address)
{
	index = getIndex(int address)
		
	
