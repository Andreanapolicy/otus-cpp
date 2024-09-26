#include <string>
#include <vector>
#include <list>
#include <iostream>

/// <summary>
/// Prints string type value.
/// </summary>
/// <typeparam name="T">.The type of the input value Must be an string type</typeparam>
/// <param name="value">The string value to be printed</param>
template <typename T>
typename std::enable_if<std::is_same_v<T, std::string>, void>::type
print_ip(const T& str)
{
    std::cout << str << std::endl;
}

/// <summary>
/// Construct the IP address of integral type to string.
/// </summary>
/// <typeparam name="T">The type of the input value. Must be an integral type</typeparam>
/// <param name="value">The integral value to be printed as an IP address.</param>
///  
/// Example usage:
/// \code{.cpp}
/// print_ip(int8_t{-1}); // 255
/// print_ip(int16_t{0}); // 0.0
/// print_ip(int32_t{2130706433}); // 127.0.0.1
/// print_ip(int64_t{8875824491850138409});// 123.45.67.89.101.112.131.41
/// \endcode
template <typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
print_ip(T number)
{
    const auto size = sizeof(T);
    
    const auto value = static_cast<std::make_unsigned_t<T>>(number);

    if (size == 1)
    {
        print_ip(std::to_string(static_cast<std::uint16_t>(value)));
        return;
    }

    std::string result;
    for (auto i = size - 1; i > 0; i--)
    {
        const auto byte = static_cast<uint8_t>(value >> 0 >> 8 * i);        
        result += std::to_string(static_cast<std::uint16_t>(byte)) + ".";
    }
    
    const auto byte = static_cast<uint8_t>(value);
    result += std::to_string(static_cast<std::uint16_t>(byte));
    print_ip(result);
}

/// <summary>
/// Construct the IP address representation of elements in a container to string.
/// </summary>
/// <typeparam name="T">The type of the container. Must be either std::vector or std::list.</typeparam>
/// <param name="container">The container whose elements are to be printed as an IP address.</param>
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

    auto result = std::to_string(*(container.begin()));
    for (auto it = ++(container.cbegin()); it != container.cend(); it++)
    {
        result += "." + std::to_string(*(it));
    }

    print_ip(result);
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