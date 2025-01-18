#include <climits>
#include <string>
#include <vector>

class Solution {
public:
  std::string longestCommonPrefix(std::vector<std::string> &strs) {
    size_t pos = 0, minLength = ULONG_LONG_MAX;
    std::string commonPrefix("");
    char c = strs[0][0];

    for (const auto &str : strs)
      minLength = std::min(minLength, str.size());

    while (pos != minLength) {
      bool mismatch = false;
      for (const auto &str : strs) {
        if (str[pos] != c) {
          mismatch = true;
          break;
        }
      }

      if (mismatch) [[likely]]
        break;
      else {
        commonPrefix += c;
        if (++pos != minLength)
          c = strs[0][pos];
      }
    }

    return commonPrefix;
  }
};
