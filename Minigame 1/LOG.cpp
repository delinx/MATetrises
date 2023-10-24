//
// Created by del on 17/09/22.
//

#include "LOG.hpp"

void LOG::debug(const std::string& message)
{
    if(glevel <= DEBUG)
    {
        print(DEBUG, message);
    }
}

void LOG::info(const std::string& message)
{
    if(glevel <= INFO)
    {
        print(INFO, message);
    }
}

void LOG::warning(const std::string& message)
{
    if(glevel <= WARNING)
    {
        print(WARNING, message);
    }
}

void LOG::error(const std::string& message)
{
    if(glevel <= ERROR)
    {
        print(ERROR, message);
    }
}

void LOG::fatal(const std::string& message)
{
    if(glevel <= FATAL)
    {
        print(FATAL, message);
    }
}


void LOG::print(log_level level, const std::string& message)
{
    std::cout << "[" << std::time(nullptr) - TIME_ORIGIN << "] ";
    switch(level)
    {
        case DEBUG:
            std::cout << "(" << name << ")" << COLOR.CGREEN << "[DEBUG]: " << COLOR.CRESET;
            break;
        case INFO:
            std::cout << "(" << name << ")" << COLOR.CBLUE << "[INFO]: " << COLOR.CRESET;
            break;
        case WARNING:
            std::cout << "(" << name << ")" << COLOR.CYELLOW << "[WARNING]: " << COLOR.CRESET;
            break;
        case ERROR:
            std::cout << "(" << name << ")" << COLOR.CRED << "[ERROR]: " << COLOR.CRESET;
            break;
        case FATAL:
            std::cout << "(" << name << ")" << COLOR.CMAGENTA << "[FATAL]: " << COLOR.CRESET;
            break;
    }
    std::cout << message << std::endl;
}

LOG::LOG(const std::string _name)
{
    name = _name;
}
