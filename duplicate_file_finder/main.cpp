#include "src/InputData/InputData.h"
#include "src/DuplicateFileFinder/DuplicateFileFinder.h"
#include <iostream>

int main(int argc, char** argv)
{
	InputData data(argc, argv);

	DuplicateFileFinder finder(std::move(data));
	finder.Find();

	return 0;
}