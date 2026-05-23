#include <cstring>
#include <string>
#include <vector>

class Solution
{
public:
  bool wordBreak(std::string s, std::vector<std::string> &dict)
  {
    size_t n = s.size();

    bool possible[n + 1 + 20]; // can create [1..i]
    std::memset(possible, false, sizeof(bool) * (n + 1 + 20));
    possible[20] = true;

    for (size_t i = 1; i <= n; i++)
    {
      bool can_construct{};
      for (const auto &word : dict)
      {
        if (possible[i - word.length() + 20])
          can_construct = can_construct ||
                          s.substr(i - word.length(), word.length()) == word;
      }

      possible[i + 20] = can_construct;
    }

    return possible[n + 20];
  }
};
