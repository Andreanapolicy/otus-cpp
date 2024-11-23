#include "src/InputData.h"
#include <iostream>

int main(int argc, char** argv)
{
	InputData data(argc, argv);

	std::cout << data.ScanAllDirs() << std::endl;
	return 0;
}