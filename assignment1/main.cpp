#include <algorithm>
#include <filesystem>  // making inputting files easier
#include <fstream>     // for ifstream
#include <iostream>    // for cout, cin
#include <iterator>
#include <queue>
#include <sstream>  // for stringstream
#include <stdexcept>
#include <unordered_set>
#include <vector>
#include "wikiscraper.hpp"

using std::cin;
using std::cout;
using std::ifstream;
using std::priority_queue;
using std::string;
using std::stringstream;
using std::unordered_set;
using std::vector;
namespace fs = std::filesystem;

/*
 * This is the function you will be implementing parts of. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */

// TODO: ASSIGNMENT 2 TASK 5:
// Please implement the following function, which should take in two sets of
// strings and returns the number of common strings between the two sets. You
// should use lambdas and std::count_if. Estimated length: <4 lines

///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN STUDENT CODE HERE
auto numCommonLinks(const unordered_set<string>& curr_set, const unordered_set<string>& target_set)
    -> int {
  // replace all of these lines!
  return static_cast<int>(
      std::count_if(curr_set.begin(), curr_set.end(),
                    [&ts = target_set](const string& s) { return ts.find(s) != ts.end(); }));
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

auto findWikiLadder(const string& start_page, const string& end_page) -> vector<string> {
  WikiScraper w;

  /* Create alias for container backing priority_queue */
  using container = vector<vector<string>>;
  unordered_set<string> target_set = w.getLinkSet(end_page);

  // TODO: ASSIGNMENT 2 TASK 6:
  // Please implement the comparator function that will be used in the priority
  // queue. You'll need to consider what variables this lambda will need to
  // capture, as well as what parameters it'll take in. Be sure to use the
  // function you implemented in Task 1! Estimated length: <3 lines

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // BEGIN STUDENT CODE HERE
  auto cmp_fn = [&w, &target_set](const vector<string>& left, const vector<string>& right) {
    // replace all of these lines.
    return numCommonLinks(w.getLinkSet(left.back()), target_set) <
           numCommonLinks(w.getLinkSet(right.back()), target_set);
  };
  // END STUDENT CODE HERE
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  // TODO: ASSIGNMENT 2 TASK 7:
  // Last exercise! please instantiate the priority queue for this algorithm,
  // called "queue". Be sure to use your work from Task 2, cmp_fn, to
  // instantiate our queue. Estimated length: 1 line

  ///////////////////////////////////////////////////////////////////////////////////////////////////
  // BEGIN STUDENT CODE HERE
  // something like priority_queue<...> queue(...);
  // please delete ALL 4 of these lines! they are here just for the code to
  // compile.
  std::priority_queue<vector<string>, container, decltype(cmp_fn)> queue(cmp_fn);

  // END STUDENT CODE HERE
  ///////////////////////////////////////////////////////////////////////////////////////////////////

  queue.push({start_page});
  unordered_set<string> visited;

  while (!queue.empty()) {
    vector<string> curr_path = queue.top();
    queue.pop();
    string curr = curr_path.back();

    cout << "Optimizing path:";
    for (const auto& s : curr_path) {
      cout << ' ' << s;
    }
    cout << '\n';

    auto link_set = w.getLinkSet(curr);

    /*
     * Early check for whether we have found a ladder.
     * By doing this check up here we spead up the code because
     * we don't enqueue every link on this page if the target page
     * is in the links of this set.
     */
    if (link_set.find(end_page) != link_set.end()) {
      curr_path.push_back(end_page);
      return curr_path;
    }

    // find link on current page that has most same links compared to end_page
    for (const string& neighbour : link_set) {
      if (visited.find(neighbour) == visited.end()) {
        visited.insert(neighbour);
        vector<string> new_path = curr_path;
        new_path.push_back(neighbour);  // usually the page which contains most links
        queue.push(new_path);
      }
    }
  }
  return {};
}

auto main() -> int {
  // a quick working directory fix to allow for easier filename inputs
  auto res_path = fs::current_path() / "res";
  string filenames = "Available input files: ";

  for (const auto& entry : fs::directory_iterator(res_path)) {
    if (!entry.is_regular_file()) {
      continue;
    }
    string filename = entry.path().filename().generic_string();
    filenames += filename + ", ";
  }
  // omit last ", ".
  cout << filenames.substr(0, filenames.size() - 2) << "." << '\n';

  /* Container to store the found ladders in */
  vector<vector<string>> output_ladders;

  cout << "Enter a file name: ";
  string filename;
  getline(cin, filename);

  auto filepath = res_path / filename;
  if (!fs::is_regular_file(filepath)) {
    throw std::invalid_argument("path not exist or not a file");
  }
  ifstream file(filepath);
  int num_pairs;
  // parse the first line as the number of tokens
  file >> num_pairs;

  // loop through each line, parsing out page names and calling findWikiLadder
  string start_page;
  string end_page;
  for (int i = 0; i < num_pairs; i++) {
    // parse the start and end page from each line
    file >> start_page >> end_page;
    output_ladders.push_back(findWikiLadder(start_page, end_page));
  }

  /*
   * Print out all ladders in outputLadders.
   * We've already implemented this for you!
   */
  for (auto& ladder : output_ladders) {
    if (ladder.empty()) {
      cout << "No ladder found!" << '\n';
    } else {
      cout << "Ladder found:" << '\n';
      cout << "\t"
           << "{";

      std::copy(ladder.begin(), ladder.end() - 1, std::ostream_iterator<string>(cout, ", "));
      /*
       * The above is an alternate way to print to cout using the
       * STL algorithms library and iterators. This is equivalent to:
       *    for (size_t i = 0; i < ladder.size() - 1; ++i) {
       *        cout << ladder[i] << ", ";
       *    }
       */
      cout << ladder.back() << "}" << '\n';
    }
  }
  return 0;
}
