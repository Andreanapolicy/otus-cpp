#include "ip_list.h"

namespace ip_address
{

namespace
{

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
IP split(const std::string line, char delimeter)
{
    IP ip;

    std::string::size_type start = 0;
    std::string::size_type stop = line.find_first_of(delimeter);
    while(stop != std::string::npos)
    {
        ip.push_back(line.substr(start, stop - start));

        start = stop + 1;
        stop = line.find_first_of(delimeter, start);
    }

    ip.push_back(line.substr(start));

    return ip;
}
}

bool IPList::Empty() const
{
    return m_data.empty();
}

std::istream& operator>>(std::istream& istream, IPList& ipList)
{
    for(std::string line; std::getline(std::cin, line);)
    {
        auto ip = split(line, '\t');
        ipList.m_data.push_back(split(ip.at(0), '.'));
    }

    return istream;
}

void IPList::SortInReverseLexicographicOrder()
{
}
}
