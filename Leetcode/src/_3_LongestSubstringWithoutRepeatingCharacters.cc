#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <string>

class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    if (s.empty())
      return 0;

    std::size_t n = s.size(), bestSize = 1;
    __gnu_pbds::gp_hash_table<char, std::size_t> charToIndex{};
    charToIndex[s[0]] = 0;

    std::size_t l = 0;
    for (std::size_t i = 1; i < n; i++) {
      char c = s[i];
      auto it = charToIndex.find(c);
      if (it != charToIndex.end()) {
        bestSize = std::max(bestSize, charToIndex.size());
        std::size_t newPos = it->second;
        for (std::size_t j = l; j <= newPos; j++)
          charToIndex.erase(s[j]);
        l = newPos + 1;
      }

      charToIndex[c] = i;
    }

    return static_cast<int>(std::max(bestSize, charToIndex.size()));
  }
};
