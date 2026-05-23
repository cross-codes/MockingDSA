#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::vector<std::string>> partition(std::string s)
  {
    int n{static_cast<int>(s.length())};
    std::vector<std::vector<std::string>> res{};

    auto is_palindrome = [&s](int from, int to) -> bool {
      while (from < to)
      {
        if (s[from] != s[to])
          return false;

        from += 1;
        to -= 1;
      }

      return true;
    };

    auto dfs = [&res, &n, &s,
                &is_palindrome](auto &&dfs, int index,
                                std::vector<std::string> &partition) -> void {
      if (index >= n)
      {
        res.push_back(partition);
        return;
      }

      for (int i = index; i < n; i++)
      {
        if (is_palindrome(index, i))
        {
          partition.push_back(s.substr(index, i - index + 1));
          dfs(dfs, i + 1, partition);
          partition.pop_back();
        }
      }
    };

    std::vector<std::string> partition{};
    dfs(dfs, 0, partition);

    return res;
  }
};
