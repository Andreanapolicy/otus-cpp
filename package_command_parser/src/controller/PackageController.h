#pragma once
#include <memory>
#include <sstream>

class PackageController
{
public:
	PackageController(std::istream& input, std::ostream& defaultOutput, size_t blockCapacity);

	void StartProcessCommand();

private:
	void WriteStoredData();

	std::istream& m_input;
	std::ostream& m_defaultOutput;

	class Storage;
	std::shared_ptr<Storage> m_storage;
};