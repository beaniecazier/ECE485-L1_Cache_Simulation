#include "Set.h"
#include <math.h>

#include "Set.h"
#include <math.h>

#ifndef CACHE_H_20171123
#define CACHE_H_20171123

#define PROC_SIZE = 32 //because Processor is 32-bit 
#define OFFSET_BITS 6 //because 64B lines = (2^6)B
#define TAG_BITS 12 //because sets + lines = 14+6=20, 32-20=12

class Cache
{
public:
	Cache(int setSize, int associativity, bool verbose);  //constructor
	~Cache(); //destructor
	
	//public function declarations (primitives, prototypes)
	int readData(int address);
	int writeData(int address);
	int invalidataData(int address);
	int readDataToL2(int address);
	int resetAll();
	int printCache();
	int clearCache();
	

private:
	// 16k sets
	Set* sets;
	
	//put variables here
	bool verbose;
	
	int getIndex(int address);
	int getTag(int address); //pass this to Dustin
};


//test

#endif CACHE_H_20171123
