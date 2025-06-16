#include <string>
#include <vector>

class Solution
{
public:
  std::string longestCommonPrefix(std::vector<std::string> &strs)
  {
    std::string lcp{};
    size_t i{};

    while (true)
    {
      char front = strs[0][i];
      bool all_equal{true};
      for (const auto &s : strs)
      {
        if (i >= s.size() || s[i] != front)
        {
          all_equal = false;
          break;
        }
      }

      if (!all_equal)
        break;
      else
        lcp += front;

      i += 1;
    }

    return lcp;
  }
};
