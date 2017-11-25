#include "Line.h"
#define MISS 0
#define HIT 1

#ifndef SET_H_20171123
#define SET_H_20171123
class Set
{
public:
	//Constructor and deconstructor function
	Set(int a, bool v);
	~Set();

	//Public functions
	int read(int tag);
	int write(int tag);
	void invalidate();
	void invalidate(int tag);
	int readFromL2(int tag);
	void reset();
	void print();

	//Public variable
	bool valid;

private:
	//Private variables
	Line* lines;
	int associativity;
	bool verbose;
	int count;

	//Private functions
	void updateLRU(int tag);
	int checkLRU();
	void readEvict();
	void handleWriteMiss(int tag);
	void writeEvict();
	bool isFull();
};
#endif SET_H_20171123