#include <set>
#include "hashmap.hpp"

// UNCOMMENT THESE FOR MILESTONE 2
#include <iostream>
#include "test_settings.cpp"
#include "tests.cpp"

using std::cin;
using std::cout;
using std::string;

// declaring functions now so we can use them befpre we implement them!
auto student_main() -> int;

// student_main helpers. Remember to change the necessary function signatures here and
// where they are implemented for milestone 1!
void init_map(HashMap<string, int>& map);
void print_difference(const HashMap<string, int>& lecturer_record,
                      const string& lecturer1,
                      const string& lecturer2);
template <typename KeyType, typename MappedTyped>
auto find_keys(const HashMap<KeyType, MappedTyped>& map) -> std::set<KeyType>;

auto main() -> int {
  int answer;
  cout << "Please enter a number and then hit ENTER\n1) Milestone 1 code\n2) Milestone 2 tests"
       << '\n';
  cin >> answer;
  if (answer == 1) {
    student_main();
  } else if (answer == 2) {
    cout << ":P" << '\n';
    // UNCOMMENT THIS FOR MILESTONE 2
    run_test_harness();
  } else {
    cout << "Please run your code again and hit 1 or 2 only!";
  }
}

auto student_main() -> int {
  cout << "This is student main. You can try using HashMap as a client by editing the code here!"
       << '\n';
  HashMap<string, int> map;
  init_map(map);
  const std::set<string> keys = find_keys(map);
  cout << "Find the difference in time between two lecturers! \n"
       << "Please enter two names from this list, separated by a space. Then hit ENTER\n"
       << '\n';
  for (const auto& key : keys) {
    cout << key << '\n';
  }
  string name1;
  string name2;
  cin >> name1;
  cin >> name2;
  print_difference(map, name1, name2);
  return 0;
}

// This will fill parameter map with lecturer -> year they lectured pairs
void init_map(HashMap<string, int>& map) {
  cout << "Hello from your past and current lecturers!" << '\n';
  map.insert({"Anna", 2019});
  map.insert({"Avery", 2019});
  map.insert({"Nikhil", 2020});
  map.insert({"Ethan", 2020});
  map.insert({"Frankie", 2021});
  map.insert({"Sathya", 2021});
  map.insert({"aAnna", 2019});
  map.insert({"aAvery", 2019});
  map.insert({"aNikhil", 2020});
  map.rehash(2);
  map.insert({"aEthan", 2020});
  map.insert({"aFrankie", 2021});
  map.insert({"aSathya", 2021});
  // demonstrate the map in action!
  map.debug();
  map.rehash(5);
  map.debug();
}

// this will return a set of all the keys in parameter map
template <typename KeyType, typename MappedTyped>
auto find_keys(const HashMap<KeyType, MappedTyped>& map) -> std::set<KeyType> {
  std::set<KeyType> res;
  for (auto it = map.begin(); it != map.end(); ++it) {
    // Remember structured binding? :)
    auto [key, val] = *it;  // at iterator points to a key, value pair in a map!
    res.insert(key);
  }
  return res;
}

// this will find and print which lecturer lectured first, and how long after them the
// second lecturer lectured
void print_difference(const HashMap<string, int>& lecturer_record,
                      const string& lecturer1,
                      const string& lecturer2) {
  int year1 = lecturer_record.at(lecturer1);
  int year2 = lecturer_record.at(lecturer2);
  if (year1 < year2) {
    cout << lecturer1 << " lectured first and " << year2 - year1 << " year(s) later, " << lecturer2
         << " lectured" << '\n';
  } else if (year1 > year2) {
    cout << lecturer2 << " lectured first and " << year1 - year2 << " year(s) later, " << lecturer1
         << " lectured" << '\n';
  } else {
    cout << lecturer1 << " and " << lecturer2 << " lectured the same year, " << year1 << '\n';
  }
}