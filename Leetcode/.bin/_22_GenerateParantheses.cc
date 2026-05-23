#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::string> generateParenthesis(int n)
  {
    std::vector<std::string> res{};

    auto dfs = [&res, &n](auto &&dfs, int n_open, int n_closed,
                          std::string &curr) -> void {
      if (n_open == n_closed && n_open == n)
      {
        res.emplace_back(curr);
        return;
      }

      if (n_open < n)
      {
        curr += '(';
        dfs(dfs, n_open + 1, n_closed, curr);
        curr.pop_back();
      }

      if (n_closed < n_open)
      {
        curr += ')';
        dfs(dfs, n_open, n_closed + 1, curr);
        curr.pop_back();
      }
    };

    std::string curr{};
    dfs(dfs, 0, 0, curr);

    return res;
  }
};
