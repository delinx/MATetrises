#include "log.hpp"
#include <string>

void log(std::string str)
{
    std::cout << str << std::endl;
}

void log(i32 str)
{
    std::cout << std::to_string(str) << std::endl;
}

void log(u32 str)
{
    std::cout << std::to_string(str) << std::endl;
}

void log(usize str)
{
    std::cout << std::to_string(str) << std::endl;
}

void logsl(std::string str)
{
    std::cout << str;
}

void logsl(i32 str)
{
    std::cout << std::to_string(str);
}

void logsl(u32 str)
{
    std::cout << std::to_string(str);
}

void logsl(usize str)
{
    std::cout << std::to_string(str);
}
