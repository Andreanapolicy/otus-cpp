#include <stdexcept>

class ParseException : public std::runtime_error
{
public:
	ParseException(std::string message)
		: std::runtime_error(std::move(message))
	{
	}
};