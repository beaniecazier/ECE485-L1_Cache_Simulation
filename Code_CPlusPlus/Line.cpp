#include "Line.h"
#include <string>

using namespace std;

Line::Line()
{
	mesi = INVALID;
	LRU = -1;
	tag = -1;
}

Line::~Line()
{
}

void Line::invalidate()
{
	mesi = INVALID;
	LRU = -1;
	tag = -1;
}

string Line::printMESI()
{
	switch (mesi)
	{
	case MODIFIED: return "MODIFIED";
	case SHARED: return "SHARED";
	case EXCLUSIVE: return "EXCLUSIVE";
	default: return "INVALID";
	}
}
