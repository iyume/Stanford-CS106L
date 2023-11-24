#include "wikiscraper.hpp"
#include <cpr/cpr.h>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include "error.hpp"

using std::string;
using std::unordered_set;

/*
 * You should delete the code in this function and
 * fill it in with your code from part A of the assignment.
 *
 * If you used any helper functions, just put them above this function.
 */

// TODO: ASSIGNMENT 2 TASK 4:
// Please implement a function that can determine if a wiki link is valid or
// not. As a reminder, it needs to take in a string and return whether or not #
// or : is contained in the string. Estimated length: ~5-10 lines

///////////////////////////////////////////////////////////////////////////////////////////////////
// BEGIN STUDENT CODE HERE
auto validWikilink(const string& link) -> bool {
  // replace these lines!
  return (std::all_of(link.begin(), link.end(), [](auto c) -> bool { return c != ':' && c != '#'; }
                      // current clangd can't infer auto lambda.
                      // See: https://github.com/clangd/clangd/issues/493
                      ));
}
// END STUDENT CODE HERE
///////////////////////////////////////////////////////////////////////////////////////////////////

auto findWikiLinks(const string& inp) -> unordered_set<string> {
  /* Delimiter for start of a link  */
  static const string Delim = "href=\"/wiki/";

  unordered_set<string> ret;

  auto url_start = inp.begin();
  auto end = inp.end();

  while (true) {
    // TODO: ASSIGNMENT 2 TASK 1:
    // Set url_start to the next location of "delim" (starting your search at
    // url_start), using std::search. After doing so, break out of the while
    // loop if there are no occurrences of delim left (use your work from the
    // line above). Estimated length: 2-3 lines

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE
    // Please delete this line when you start working!
    url_start = std::search(url_start, end, Delim.begin(),
                            Delim.end());  // or string.find as well
    if (url_start == end) {                // end refers to '\0'
      break;
    }
    url_start += static_cast<long>(Delim.length());
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO: ASSIGNMENT 2 TASK 2:
    // Set url_end to the end of the wikilink. Start searching after the
    // delimeter you found above. Make sure to use std::find! (std::find looks
    // for a single element in a container, e.g. character in a
    // string—std::search looks for a series of elements in a container, like a
    // substring in a string. remember that a string is represented as an array
    // of characters, and is also a container!) Estimated length: 1 lines

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE (delete/edit this line)
    auto url_end = std::find(url_start, end, '"');
    if (url_end == inp.end()) {
      throw std::runtime_error("invalid format");
    }
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // TODO: ASSIGNMENT 2 TASK 3:
    // Last exercise of this function! Create a string from the two iterators
    // (url_start and url_end) above using a string constructor. Make sure you
    // start the string AFTER the delimiter you found in task 5! Estimated
    // length: 1 lines

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    // BEGIN STUDENT CODE HERE (delete/edit this line)
    auto link = string(url_start, url_end);
    // END STUDENT CODE HERE
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    /*
     * Only add link to the set if it is valid i.e. doesn't
     * contain a ':' or a '#'.
     */
    if (validWikilink(link)) {
      ret.insert(link);
    }

    url_start = url_end;
  }
  return ret;
}

/*
 * ==================================================================================
 * |                Don't edit anything below here, but take a peek! |
 * ==================================================================================
 */
auto WikiScraper::getLinkSet(const string& page_name) -> unordered_set<string> {
  if (this->_linkset_cache.find(page_name) == this->_linkset_cache.end()) {
    auto links = findWikiLinks(getPageSource(page_name));
    this->_linkset_cache[page_name] = links;
  }
  return this->_linkset_cache[page_name];
}

WikiScraper::WikiScraper() {
  (void)getPageSource("Main_Page");
}

auto createPageUrl(const string& page_name) -> string {
  return "https://en.wikipedia.org/wiki/" + page_name;
}

void notFoundError(const string& msg, const string& page_name, const string& url) {
  const string title = "    AN ERROR OCCURED DURING EXECUTION.    ";
  const string border(title.size() + 4, '*');
  std::cerr << '\n';
  mylog::error(border);
  mylog::error("* " + title + " *");
  mylog::error(border);
  mylog::error("Reason: " + msg);
  mylog::error("Debug Information:");
  mylog::error("\t- Input parameter: " + page_name);
  mylog::error("\t- Attempted url: " + url);
}

auto WikiScraper::getPageSource(const string& page_name) -> string {
  const static string NotFound = "Wikipedia does not have an article with this exact name.";
  if (this->_page_cache.find(page_name) == this->_page_cache.end()) {
    string url = createPageUrl(page_name);
    // using the cpr library to get the HTML content of a webpage!
    // we do so by aking a GET REST request to a wikipedia webpage, which
    // returns the content of the webpage. when this assignment was on
    // QtCreator, we had a whole separate assignment for making sure an
    // alternate Internet Library (not cpr) was working on your personal pc.
    // look how simple it is now!
    cpr::Response r = cpr::Get(cpr::Url{url});

    string ret = r.text;
    if (r.status_code != 200) {
      notFoundError("Couldn't get page source. Have you entered a valid link?", page_name, url);
      return "";
    }
    if (std::search(ret.begin(), ret.end(), NotFound.begin(), NotFound.end()) != ret.end()) {
      notFoundError("Page does not exist!", page_name, url);
      return "";
    }
    size_t indx = ret.find("plainlinks hlist navbar mini");
    if (indx != string::npos) {
      return ret.substr(0, indx);
    }
    this->_page_cache[page_name] = ret;
  }
  return this->_page_cache[page_name];
}
