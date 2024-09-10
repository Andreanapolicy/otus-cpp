#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <functional>

namespace ip_address
{

using IP = std::vector<std::string>;
using Data = std::vector<IP>;

class IPList
{
using Comparator = std::function<bool(const IP& lhs, const IP& rhs)>;
using FilterFn = std::function<bool(const IP& ip)>;

public:
    IPList() = default;
    IPList(const IPList&) = default;
    IPList(Data&& data) : m_data{ std::move(data) } {};

    [[nodiscard]] bool Empty() const;
    IPList SortInReverseLexicographicOrder();

    friend std::istream& operator>>(std::istream& istream, IPList& ipList);
    friend std::ostream& operator<<(std::ostream& ostream, IPList& ipList);

    IPList FilterByFirstByteIs1();
    IPList FilterByFirstByteIs46AndSecondIs70();
    IPList FilterByAnyByteIs46();

private:
    IPList SortBy(const Comparator& comparator);
    IPList FilterBy(const FilterFn& filterFn);

    Data m_data;
};
}