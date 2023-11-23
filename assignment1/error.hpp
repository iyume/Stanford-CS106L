#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace mylog {
void info(const std::string& msg = "", const std::string& leftDisp = "Info ");
void error(const std::string& msg = "", const std::string& leftDisp = "Error");
}  // namespace mylog

#endif  // ERROR_H
