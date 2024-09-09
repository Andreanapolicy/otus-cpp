#include <exception>
#include "src/ip_list.h"

int main(int, char const *[])
{
    try
    {
        ip_address::IPList ip_pool;
        std::cin >> ip_pool;
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}