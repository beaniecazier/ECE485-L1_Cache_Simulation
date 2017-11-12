#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "cache.h"

using namespace std;

void openFile(ifstream &inFile, char* fileName);
void ResetCache();

int HitCount = 0;
int MissCount = 0
int CacheReads = 0;
int CacheWrites = 0;
long totalOperations = 0;

int main(int argc, char* argv[])
{
  return 0;
}
