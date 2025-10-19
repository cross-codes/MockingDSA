#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

class Solution
{
public:
  std::vector<std::string> validateCoupons(
      std::vector<std::string> &code, std::vector<std::string> &businessLine,
      std::vector<bool> &isActive)
  {
    int n = static_cast<int>(code.size());

    std::vector<std::pair<std::string, int>> res{};
    for (int i = 0; i < n; i++)
    {
      bool good            = isActive[i] && !code[i].empty();
      std::string code_str = code[i];
      for (char c : code_str)
      {
        if (!std::isalnum(c) && c != '_')
          good &= false;
      }

      std::string business = businessLine[i];
      if (business != "electronics" && business != "grocery" &&
          business != "pharmacy" && business != "restaurant")
        good &= false;

      if (good)
        res.emplace_back(code_str, i);
    }

    std::unordered_map<std::string, int> ranks{};
    ranks["electronics"] = 1;
    ranks["grocery"]     = 2;
    ranks["pharmacy"]    = 3;
    ranks["restaurant"]  = 4;

    auto SORT_ORDER      = [&businessLine,
                       &ranks](const std::pair<std::string, int> &a,
                               const std::pair<std::string, int> &b) -> bool {
      int pos1 = a.second, pos2 = b.second;
      std::string b1 = businessLine[pos1], b2 = businessLine[pos2];

      int cmp = ranks[b1] - ranks[b2];
      if (cmp == 0)
        return a.first < b.first;
      else
        return cmp < 0;
    };

    std::sort(res.begin(), res.end(), SORT_ORDER);

    std::vector<std::string> final{};
    for (const auto &[str, idx] : res)
      final.emplace_back(str);

    return final;
  }
};
