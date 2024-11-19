#pragma once
#include <filesystem>
#include <fstream>

namespace logger
{
class Logger
{
public:
	static void Log(const std::filesystem::path& path, const std::string& data)
	{
		std::ofstream output{ path.c_str() };

		output << data << std::endl;
		output.close();
	}
};
} // namespace logger