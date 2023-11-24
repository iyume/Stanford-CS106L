#include <algorithm>
#include <array>
#include <fstream>
#include <ios>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

using StudentInfo = std::pair<std::string, int>;

// signature as said in assignment
auto createMap(const std::string& filename) -> std::map<std::string, StudentInfo> {
  std::ifstream file(filename, std::ios::binary);
  if (!file.is_open()) {
    throw std::runtime_error("file not exists");
  }

  decltype(createMap("")) res;
  std::string line;
  std::string cell;

  while (std::getline(file, line)) {
    std::vector<std::string> cells;
    auto offset = line.begin();
    decltype(offset) offset_end;
    while ((offset_end = std::find(offset, line.end(), ',')) != line.end()) {
      cells.emplace_back(offset, offset_end);
      offset = offset_end + 1;
    }
    cells.emplace_back(offset, line.end());
    if (cells.size() == 3) {
      std::string name = cells.at(0);
      std::string university = cells.at(1);
      int year = std::stoi(cells.at(2));  // \r is implicitly removed here
      res[name] = std::make_pair(university, year);
    }
  }

  return res;
}

// signature as said in assignment
void printMap(std::map<std::string, StudentInfo>& csMap) {
  for (const auto& [name, info] : csMap) {
    if (!(info.first == "Stanford University")) {
      continue;
    }
    std::cout << name << ',' << info.first << ',' << info.second << '\n';
  }
}

auto main() -> int {
  auto map = createMap("lecture6_exercise_w23.csv");
  printMap(map);
}