#ifndef TETRACRAWLER_LOG_HPP
#define TETRACRAWLER_LOG_HPP

#include <ctime>
#include <iostream>

// time stamp of when the program started,
// or more precisely, when the LOG was first used.
static const std::time_t TIME_ORIGIN = std::time(nullptr);

class LOG
{
      public:
    explicit LOG(std::string _name);

    enum log_level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    typedef struct log_colors
    {
        const std::string CBLACK   = "\033[30m";
        const std::string CRED     = "\033[31m";
        const std::string CGREEN   = "\033[32m";
        const std::string CYELLOW  = "\033[33m";
        const std::string CBLUE    = "\033[34m";
        const std::string CMAGENTA = "\033[35m";
        const std::string CCYAN    = "\033[36m";
        const std::string CWHITE   = "\033[37m";
        const std::string CRESET   = "\033[0m";
    } log_colors;

    const log_colors COLOR;

    void debug(const std::string& message);

    void info(const std::string& message);

    void warning(const std::string& message);

    void error(const std::string& message);

    void fatal(const std::string& message);

    void print(log_level level, const std::string& message);

    log_level   glevel = DEBUG;
    std::string name   = "none";
};



#endif  // TETRACRAWLER_LOG_HPP
