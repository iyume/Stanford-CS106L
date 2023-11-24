#ifndef WIKISCRAPER_H
#define WIKISCRAPER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class WikiScraper {
public:
  WikiScraper();

  /*
   * This method takes the page name of a Wikipedia page and
   * returns an unordered_set containing all the links on this page.
   */
  auto getLinkSet(const std::string& page_name) -> std::unordered_set<std::string>;

private:
  auto getPageSource(const std::string& page_name) -> std::string;
  std::unordered_map<std::string, std::string> _page_cache;
  std::unordered_map<std::string, std::unordered_set<std::string>> _linkset_cache;
};

auto findWikiLadder(const std::string& start_page, const std::string& end_page)
    -> std::vector<std::string>;
auto validWikilink(const std::string& link) -> bool;
auto findWikiLinks(const std::string& inp) -> std::unordered_set<std::string>;

#endif  // WIKISCRAPER_H
