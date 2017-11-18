#include "Set.h"
#include <math.h>

#define NUM_SETS 16384

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
