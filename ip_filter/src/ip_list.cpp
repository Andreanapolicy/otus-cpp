#include "ip_list.h"
#include <algorithm>

namespace ip_address
{

namespace
{
IP split(const std::string& line, char delimeter)
{
    IP ip;

    auto start = 0;
    auto stop = line.find_first_of(delimeter);
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

std::ostream& operator<<(std::ostream& ostream, IPList& ipList)
{
    for(const auto& ip : ipList.m_data)
    {
        ostream << ip.at(0) << '.' << ip.at(1) << '.' << ip.at(2) << '.' << ip.at(3) << std::endl;
    }

    return ostream;
}

IPList IPList::SortInReverseLexicographicOrder()
{
    return SortBy([](const IP& lhs, const IP& rhs){
        return std::stoi(lhs.at(0)) > std::stoi(rhs.at(0)) 
            || std::stoi(lhs.at(1)) > std::stoi(rhs.at(1)) 
            || std::stoi(lhs.at(2)) > std::stoi(rhs.at(2)) 
            || std::stoi(lhs.at(3)) > std::stoi(rhs.at(3));
    });
}

IPList IPList::FilterByFirstByte(int byte)
{
    return FilterBy([byte](const IP& ip){
        return std::stoi(ip.at(0)) == byte;
    });
}

IPList IPList::FilterByFirstTwoByte(int first, int second)
{
    return FilterBy([first, second](const IP& ip){
        return std::stoi(ip.at(0)) == first 
            && std::stoi(ip.at(1)) == second;
    });
}

IPList IPList::FilterByAnyByte(int byte)
{
    return FilterBy([byte](const IP& ip){
        return std::stoi(ip.at(0)) == byte 
            || std::stoi(ip.at(1)) == byte 
            || std::stoi(ip.at(2)) == byte 
            || std::stoi(ip.at(3)) == byte;
    });
}

IPList IPList::SortBy(const Comparator& comparator)
{
    IPList newIpList(*this);
    
    std::sort(newIpList.m_data.begin(), newIpList.m_data.end(), comparator);

    return newIpList;
}

IPList IPList::FilterBy(const FilterFn& filterFn)
{
    IPList newIpList;
    std::copy_if(m_data.begin(), m_data.end(), std::back_inserter(newIpList.m_data), filterFn);

    return newIpList;
}
}
