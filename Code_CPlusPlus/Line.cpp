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

Line::Invalidate()
{
	mesi = MESI.INVALID;
	LRU = -1;
	tag = -1;
}
