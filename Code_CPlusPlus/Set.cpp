Set::Set(int associativity, bool verbose)
{
 	this.verbose = verbose;
	this.associativity = associativity;
	this.valid = false;
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

void Set::read(int tag)
{
	//Check for a valid in the set of data
	if(valid)
	{
		//For loop to check validility of data from the sets
		for (int i = 0; i < this.associativity; i++)
		{
			//Check to see if any of the tags match
			if (tag == lines[i].tag)
			{
				//Check to see if it hasn't been modified (Shared)
				if (Line->MESI == 2)
				{
					//Update the LRU bits
					updateLRU();
				}

				//Check to see if its been modified once (Exclusive)
				if (Line->MESI == 3)
				{
					//Update the LRU bits
					updateLRU();
				}

				//Check to see if its been modified more than once (Modified)
				if (Line->MESI == 0)
				{
					//Update the LRU bits
					updateLRU();
				}
			}
		}

		//For loop to check the to see if all ways are valid
		for (int i = 0; i < this.associativity; i++)
		{
			//The current line in the set is invalide
			if (lines[i].mesi == 1)
			{
				//Read cache line from L2
				line[i] == tag;

				//Set the mesi state to shared
				updateMESI();

				//Exit the for loop
				break;
			}

			//Otherwise evict the LRU from the set
			evict();

			//Read cache line from L2
			line[i] == tag;

			//Set the mesi state to shared
			updateMESI();
		}
	}
}

void Set::write(int tag)
{

}

void Set::invalidate(int tag)
{

}

void Set::readFromL2()
{

}

void Set::reset()
{

}

void Set::print()
{
	//For loop to print data from the sets
	for (int i = 0; i < this.associativity; i++)
	{
		//Check if the current set is valid
		if (valid)
		{
			cout >> LRU >> mesi >> \t;
		}
	}
}

bool Set::findSpot()
{

}

void Set::updateLRU()
{

}

void Set::checkLRU()
{

}

void Set::evict()
{

}

void Set::updateMESI()
{

}
