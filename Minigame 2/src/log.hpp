#ifndef LOG_HPP
#define LOG_HPP
#include "types.hpp"
#include <iostream>

/// Log on the new line
void log(std::string str);
void log(i32 str);
void log(u32 str);
void log(usize str);
/// Log on the same line
void logsl(std::string str);
void logsl(i32 str);
void logsl(u32 str);
void logsl(usize str);

#endif  // LOG_HPP
