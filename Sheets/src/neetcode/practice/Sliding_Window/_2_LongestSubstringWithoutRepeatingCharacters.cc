#include <cstring>
#include <string>
#include <unordered_map>

class Solution {
public:
  int lengthOfLongestSubstring(std::string s) {
    if (s.empty())
      return 0;

    std::ptrdiff_t l = 0, n = s.size(), maxLength = 1;
    std::unordered_map<char, std::ptrdiff_t> indices{};

    for (std::ptrdiff_t i = 0; i < n; i++) {
      char c = s[i];
      auto it = indices.find(c);
      if (it != indices.end()) {
        std::ptrdiff_t endIndex = it->second;
        maxLength = std::max(maxLength, i - l);
        for (std::ptrdiff_t j = l; j <= endIndex; j++)
          indices.erase(s[j]);

        l = endIndex + 1;
      }
      indices[c] = i;
    }

    return static_cast<int>(std::max(maxLength, n - l));
  }
};
