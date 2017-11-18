#include "Set.h"
#include <math.h>

#define NUM_SETS 16384

#pragma once
class Cache
{
public:
	Cache(int associativity, bool verbose);
	~Cache();

private:
	// 16k sets
	Set sets[NUM_SETS];
};
