enum MESI
{
	MODIFIED = 0,
	INVALID = 1,
	SHARED = 2,
	EXCLUSIVE = 3,
};

class Set
{
public:
	Set(int associativity);
	~Set();

private:
	// array of tags
	int* tag;
	// array of LRU
	int* LRU;
	// MESI states
	MESI* mesi;
};

Set::Set(int associativity)
{
}

Set::~Set()
{
}