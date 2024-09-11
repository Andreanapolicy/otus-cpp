#include "ip_list.h"
#include <algorithm>
#include <tuple>

namespace ip_address
{

namespace
{
std::vector<std::string> split(const std::string& line, char delimeter)
{
    std::vector<std::string> ip;

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

std::istream& operator>>(std::istream& istream, IPList& ipList)
{
    for(std::string line; std::getline(istream, line); !line.empty())
    {
        auto ip = split(line, '\t');
        auto realIp = split(ip.at(0), '.');
        ipList.m_data.push_back({std::stoi(realIp[0]), std::stoi(realIp[1]), std::stoi(realIp[2]), std::stoi(realIp[3])});
    }

    return istream;
}

std::ostream& operator<<(std::ostream& ostream, const IPList& ipList)
{
    for(const auto& ip : ipList.m_data)
    {
        ostream << ip.at(0) << '.' << ip.at(1) << '.' << ip.at(2) << '.' << ip.at(3) << '\n';
    }

    return ostream;
}

void IPList::SortInReverseLexicographicOrder()
{
    std::sort(m_data.begin(), m_data.end(), [](const IP& lhs, const IP& rhs) {
        return std::tie(lhs.at(0), lhs.at(1), lhs.at(2), lhs.at(3)) > std::tie(rhs.at(0), rhs.at(1), rhs.at(2), rhs.at(3));
    });
}

IPList IPList::FilterByFirstByte(int byte)
{
    return FilterBy([byte](const IP& ip){
        return ip.at(0) == byte;
    });
}

IPList IPList::FilterByFirstTwoByte(int first, int second)
{
    return FilterBy([first, second](const IP& ip){
        return ip.at(0) == first 
            && ip.at(1) == second;
    });
}

IPList IPList::FilterByAnyByte(int byte)
{
    return FilterBy([byte](const IP& ip){
        return ip.at(0) == byte 
            || ip.at(1) == byte 
            || ip.at(2) == byte 
            || ip.at(3) == byte;
    });
}

IPList IPList::FilterBy(FilterFn filterFn)
{
    IPList newIpList;
    std::copy_if(m_data.begin(), m_data.end(), std::back_inserter(newIpList.m_data), filterFn);

    return newIpList;
}
}
