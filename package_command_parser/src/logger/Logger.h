#pragma once
#include <exception>
#include <filesystem>
#include <fstream>

namespace logger
{
class Logger
{
public:
	static void Log(std::filesystem::path path, std::string data)
	{
		std::ofstream output;
		output.open(path);
		if (!output.is_open())
		{
			throw std::runtime_error("cannot create log file");
		}

		output << std::move(data);
		output.flush();
	}

	static void Log(std::ostream& output, std::string data)
	{
		output << std::move(data);
	}
};
} // namespace logger