#include <array>
#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::string> letterCombinations(std::string digits)
  {
    size_t n{digits.size()};
    if (n == 0)
      return {};

    std::array<std::string, 10> lookup = {"",    "",    "abc",  "def", "ghi",
                                          "jkl", "mno", "pqrs", "tuv", "wxyz"};

    std::vector<std::string> res{};

    auto dfs = [&n, &res, &lookup, &digits](auto &&dfs, std::string &curr,
                                            int index) -> void {
      if (curr.size() == n)
      {
        res.push_back(curr);
        return;
      }

      for (const auto &ch : lookup[digits[index] - '0'])
      {
        curr.push_back(ch);
        dfs(dfs, curr, index + 1);
        curr.pop_back();
      }
    };

    for (const auto &ch : lookup[digits[0] - '0'])
    {
      std::string curr{ch};
      dfs(dfs, curr, 1);
    }

    return res;
  }
};
