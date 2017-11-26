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
	int read(int tag, int address);
	int write(int tag, int address);
	void invalidate(int address);
	void invalidate(int tag, int address);
	int readFromL2(int tag, int address);
	void reset();
	void print(int address);

private:
	//Private variables
	Line* lines;
	int associativity;
	bool verbose;
	int count;

	//Private functions
	void updateLRU(int tag);
	int checkLRU();
	void readEvict(int address);
	void handleWriteMiss(int tag, int address);
	void writeEvict();
	bool isFull();
};
#endif SET_H_20171123
