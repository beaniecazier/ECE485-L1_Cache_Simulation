#include "Line.h"

#ifndef SET_H_20171123
#define SET_H_20171123
class Set
{
public:
	//Constructor and deconstructor function
	Set(int associativity);
	~Set();

	//Public functions
	void read(int tag);
	void write(int tag);
	void invalidate(int tag);
	void readFromL2();
	void reset();
	void print();

	//Public variable
	bool valid;

private:
	//Private variables
	Line* lines;
	int associativity;
	bool verbose;
	
	//Private functions
	void updateLRU();
	void checkLRU();
	bool findSpot();
	void evict();
	void updateMESI();
};
#endif SET_H_20171123
