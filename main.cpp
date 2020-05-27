#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <sstream>
#include <math.h>

#include "dsaLib.h"
#include "dbLib.h"
#include "processData.h"

using namespace std;

int main() {
	Initialization();

	void* pData = nullptr;
	void* pOutput = nullptr;
	int     N;

	LoadData(pData);
	
	ReleaseData(pData);
	Finalization();
	return 0;
}
