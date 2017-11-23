#include "Line.h"

#ifndef CACHE_H_20171123
#define CACHE_H_20171123
class Set
{
public:
	Set(int associativity);
	~Set();

private:
	Line* lines;
	int associativity;
	bool verbose;
};
#endif SET_H_20171123
