#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <functional>

namespace ip_address
{

using IP = std::vector<int>;
using Data = std::vector<IP>;

class IPList
{
using FilterFn = std::function<bool(const IP& ip)>;

public:
    IPList() = default;
    IPList(const IPList&) = default;

    [[nodiscard]] bool Empty() const;
    void SortInReverseLexicographicOrder();

    friend std::istream& operator>>(std::istream& istream, IPList& ipList);
    friend std::ostream& operator<<(std::ostream& ostream, const IPList& ipList);

    IPList FilterByFirstByte(int byte);
    IPList FilterByFirstTwoByte(int first, int second);
    IPList FilterByAnyByte(int byte);

private:
    IPList FilterBy(FilterFn filterFn);

    Data m_data;
};
}