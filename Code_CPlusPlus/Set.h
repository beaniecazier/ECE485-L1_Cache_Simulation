enum MESI
{
	MODIFIED = 0,
	INVALID = 1,
	SHARED = 2,
	EXCLUSIVE = 3,
};

struct Line 
{
	int tag;
	int LRU;
	MESI mesi;
}

class Set
{
public:
	Set(int associativity);
	~Set();

private:
	Line* lines;
};
