Set::Set(int associativity, bool verbose)
{
 	this.verbose = verbose;
	this.associativity = associativity;
 	lines = new Line[this.associativity];
	for (int i = 0; i < this.associativity; i++)
	{
		lines[i] = new Line();
	}
}

Set::~Set()
{
	for (int i = 0; i < this.associativity; i++)
	{
		delete lines[i];
	}
 	delete [] lines;
}
