#include "Set.h"
#include <math.h>

#define PROC_SIZE = 32 //because Processor is 32-bit 
#define NUM_SETS 16384 //because 16K sets = 2^14
#define OFFSET_BITS 6 //because 64B lines = (2^6)B
#define TAG_BITS 12 //because sets + lines = 14+6=20, 32-20=12

#pragma once
class Cache
{
public:
	Cache(int associativity, bool verbose);  //constructor
	~Cache(); //destructor
	
	//put primitives here (function declarations)
	int readData(int address);
	int writeData(int address);
	int invalidataData(int address);
	int readDataToL2(int address);
		//
	

private:
	// 16k sets
	Set sets[NUM_SETS];
	
	//put variables here
	bool verbose;
	
	int getIndex(int address);
	int getTag(int address); //pass this to Dustin
};
