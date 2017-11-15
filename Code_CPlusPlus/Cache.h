#include "Set.h"
#include <math.h>

#define NUM_SETS 16384

#pragma once
class Cache
{
public:
	Cache(int associativity);
	~Cache();

private:
	// 16k sets
	Set sets[NUM_SETS];
};

Cache::Cache(int associativity)
{
	for each (Set set in sets)
	{
		set = new Set(associativity);
	}
}

Cache::~Cache()
{
}