#include <exception>
#include <ranges>
#include "src/ip_list.h"

int main(int, char const *[])
{
    try
    {
        ip_address::IPList ip_pool;
        std::cin >> ip_pool;

        ip_pool = ip_pool.SortInReverseLexicographicOrder();
        std::cout << ip_pool;
        {
            auto ip_pool_by_first_byte_is1 = ip_pool.FilterByFirstByteIs1();
            std::cout << ip_pool_by_first_byte_is1;
        }

        {
            auto ip_pool_by_first_byte_is46_and_second_is_70 = ip_pool.FilterByFirstByteIs46AndSecondIs70();
            std::cout << ip_pool_by_first_byte_is46_and_second_is_70;
        }
        {
            auto ip_pool_by_any_byte_is46 = ip_pool.FilterByAnyByteIs46();
            std::cout << ip_pool_by_any_byte_is46;
        }
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}