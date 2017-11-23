Set::Set(int associativity, bool verbose)
{
  this.verbose = verbose;
  lines = new Line[associativity];
}

Set::~Set()
{
  delete [] lines;
}
