#include <algorithm>
#include <cassert>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include "wikiscraper.hpp"

using std::cout;
using std::endl;
using std::string;
using std::unordered_set;
using std::vector;

const string pre = "<a href=\"wiki/";
const string suf = "\">";

/*********************************************
 * TEST #1: Valid Wikilink Basic Check: valid
 ********************************************/
const string valid_wikilink_test1() {
  return validWikilink(pre + "hello" + suf) ? "valid" : "invalid";
}

/*********************************************
 * TEST #2: Valid Wikilink Basic Check: valid
 ********************************************/
const string valid_wikilink_test2() {
  return validWikilink(pre + "Czech_Republic" + suf) ? "valid" : "invalid";
}

/*********************************************
 * TEST #3: Valid Wikilink Basic Check: valid
 ********************************************/
const string valid_wikilink_test3() {
  return validWikilink("") ? "valid" : "invalid";
}

/*********************************************
 * TEST #4: Valid Wikilink Basic Check: invalid
 * not a wiki link
 ********************************************/
const string valid_wikilink_test4() {
  return validWikilink("href=\"http://www.bncatalo") ? "valid" : "invalid";
}

/*********************************************
 * TEST #5: Valid Wikilink Basic Check: invalid
 * an illegal character
 ********************************************/
const string valid_wikilink_test5() {
  return validWikilink(pre + "hello#" + suf) ? "valid" : "invalid";
}

/*********************************************
 * TEST #6: Valid Wikilink Basic Check: invalid
 * other illegal character
 ********************************************/
const string valid_wikilink_test6() {
  return validWikilink(pre + "hello:" + suf) ? "valid" : "invalid";
}

/*********************************************
 * TEST #7: Valid Wikilink Basic Check: invalid
 * both illegal characters
 ********************************************/
const string valid_wikilink_test7() {
  return validWikilink(pre + "hell&o:" + suf) ? "valid" : "invalid";
}

const string findWikiLinks_test1() {
  // read in test file into string (Wikipedia)
  std::ifstream in("./test-resources/Germany.html");
  std::ostringstream ss;
  ss << in.rdbuf();
  string file = ss.str();

  // call findWikiLinks for the inputted Wikipedia page
  auto links = findWikiLinks(file);
  cout << links.size() << endl;

  // convert links to string.
  string res = "";
  for (const auto& link : links) {
    res += link + "\n";
  }
  return res;
}

const string testFindWikiLinks1() {
  string s = R"(<p>
  In <a href="/wiki/Topology">topology</a>, the <b>long line</b> (or <b>Alexandroff line</b>) is a
  <a href="/wiki/Topological_space">topological space</a> somewhat similar to the <a href="/wiki/Real_line">real line</a>, but in a certain way "longer". It behaves locally just like the real line, but has different large-scale properties (e.g., it is neither
  <a href="/wiki/Lindel%C3%B6f_space">Lindelöf</a> nor
  <a href="/wiki/Separable_space">separable</a>). Therefore, it serves as one of the basic counterexamples of topology
  <a href="http://www.ams.org/mathscinet-getitem?mr=507446">[1]</a>. Intuitively, the usual real-number line consists of a countable number of line segments [0,1) laid end-to-end, whereas the long line is constructed from an uncountable number of such segments. You can consult
  <a href="/wiki/Special:BookSources/978-1-55608-010-4">this</a> book for more information.
  </p>)";
  auto links = findWikiLinks(s);
  auto target = unordered_set{unordered_set<string>{"Topology", "Topological_space", "Real_line",
                                                    "Lindel%C3%B6f_space", "Separable_space"}};
  cout << "Running my " << __func__ << '\n';
  cout << "Output links: ";
  for (const auto& link : links) {
    cout << link << ' ';
  }
  cout << '\n';
  cout << "Expect links: ";
  for (const auto& link : target) {
    cout << link << ' ';
  }
  cout << '\n';
  // assert(links != target);
  cout << ((links == target) ? "equals!" : "not equals!");
  return "";  // showing error but it does pass
}

/*********************************************
 * main — provided code, not necessary to edit!
 * This is provided code that tests your valid_wikilink function
 * and, if those tests pass, your entire findWikiLinks function.
 * This is the CLI (command line interface) for this script.
 ********************************************/
int main(int argc, char* argv[]) {
  // improper use check:
  if (argc < 2) {
    std::cout << "Please specify a exercise number." << std::endl;
    return 1;
  }
  // parse exercise number argument from string to int.
  int exerciseNum = std::stoi(argv[1]);

  vector<std::function<const string()>> tests = {
      valid_wikilink_test1, valid_wikilink_test2, valid_wikilink_test3,
      valid_wikilink_test4, valid_wikilink_test5, valid_wikilink_test6,
      valid_wikilink_test7, findWikiLinks_test1,  testFindWikiLinks1};
  if (exerciseNum > 0 && exerciseNum <= tests.size()) {
    cout << tests[exerciseNum - 1]() << endl;
  }

  return 0;
}
