#include "src/controller/PackageController.h"
#include <exception>
#include <iostream>
#include <optional>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		throw std::runtime_error("Wrong input. Example: ./bulk <blocks capacity>");
	}

	std::optional<int> blockCapacity;
	try
	{
		blockCapacity = std::make_optional(std::stoi(argv[1]));
	}
	catch (const std::exception& e)
	{
	}

	if (!blockCapacity.has_value())
	{
		throw std::runtime_error("Wrong input. Example: ./bulk <blocks capacity>");
	}

	PackageController packageController(std::cin, std::cout, *blockCapacity);

	packageController.StartProcessCommand();

	return 0;
}