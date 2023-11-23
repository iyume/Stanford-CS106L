#include "error.hpp"
#include <iostream>

namespace mylog {
void info(const std::string& msg, const std::string& leftDisp) {
  std::clog << leftDisp << ' ' << msg << '\n';
}
void error(const std::string& msg, const std::string& leftDisp) {
  std::cerr << leftDisp << ' ' << msg << '\n';
}
}  // namespace mylog
