#pragma once
#include <vector>
#include <string>
#include <iostream>

namespace ip_address
{

using IP = std::vector<std::string>;
using Data = std::vector<IP>;

class IPList
{
public:
    [[nodiscard]] bool Empty() const;
    void SortInReverseLexicographicOrder();

    friend std::istream& operator>>(std::istream& istream, IPList& ipList);

private:

    Data m_data;
};
}