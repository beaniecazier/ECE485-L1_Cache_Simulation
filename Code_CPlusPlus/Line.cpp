#include "Line.h"

Line::Line()
{
	mesi = MESI.INVALID;
	LRU = -1;
	tag = -1;
}

Line::~Line()
{
}

void Line::invalidate()
{
	mesi = MESI.INVALID;
	LRU = -1;
	tag = -1;
}
