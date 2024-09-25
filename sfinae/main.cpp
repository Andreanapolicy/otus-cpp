#include <string>
#include <vector>
#include <list>
#include <iostream>

template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T number)
{
    std::cout << number << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same_v<T, std::string>, void>::type
print_ip(const T& str)
{
    std::cout << str << std::endl;
}

template <typename T>
typename std::enable_if<std::disjunction_v<
    std::is_same<T, std::vector<typename T::value_type>>,
    std::is_same<T, std::list<typename T::value_type>>>, void>::type
print_ip(const T& container)
{
    if (container.empty())
    {
        return;
    }
    std::string s = std::to_string(*(container.begin()));
    for (auto it = ++(container.cbegin()); it != container.cend(); it++)
    {
        s += "." + std::to_string(*(it));
    }

    print_ip(s);
}

int main()
{
    print_ip( int8_t{-1} ); // 255
    print_ip( int16_t{0} ); // 0.0
    print_ip( int32_t{2130706433} ); // 127.0.0.1
    print_ip( int64_t{8875824491850138409} );// 123.45.67.89.101.112.131.41
    print_ip( std::string{"Hello, World!"} ); // Hello, World!
    print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
    print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
    return 0;
}