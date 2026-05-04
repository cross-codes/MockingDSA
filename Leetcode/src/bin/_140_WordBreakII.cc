#include <string>
#include <unordered_set>
#include <vector>

class Solution
{
public:
  std::vector<std::string> wordBreak(std::string s,
                                     std::vector<std::string> &wordDict)
  {
    int n = static_cast<int>(s.size());
    std::unordered_set<std::string> valid(wordDict.begin(), wordDict.end());

    auto dfs = [&valid, &s, &n](auto &&dfs,
                                int pos) -> std::vector<std::string> {
      if (pos == n)
        return {""};

      std::vector<std::string> res{};
      for (int i = pos + 1; i <= n; i++)
      {
        std::string portion = s.substr(pos, i - pos);
        if (valid.contains(portion))
        {
          std::vector<std::string> nxt = dfs(dfs, i);
          for (const std::string &str : nxt)
            if (str.empty())
              res.push_back(portion);
            else
              res.push_back(portion + " " + str);
        }
      }

      return res;
    };

    return dfs(dfs, 0);
  }
};
