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

	std::optional<size_t> blockCapacity;
	try
	{
		if (auto value = std::stoi(argv[1]); value > 0)
		{
			blockCapacity = std::make_optional(value);
		}
	}
	catch (const std::exception& e)
	{
	}

	if (!blockCapacity.has_value())
	{
		throw std::runtime_error("Wrong input. Example: ./bulk <blocks capacity, `>0` >");
	}

	PackageController packageController(std::cin, std::cout, *blockCapacity);

	packageController.StartProcessCommand();

	return 0;
}