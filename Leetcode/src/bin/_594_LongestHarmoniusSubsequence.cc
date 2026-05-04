#include <unordered_map>
#include <vector>

class Solution
{
public:
  int findLHS(std::vector<int> &nums)
  {
    std::unordered_map<int, int> freq{};
    for (int e : nums)
      freq[e] += 1;

    int res{};
    for (const auto &[e, f] : freq)
      if (freq.contains(e + 1))
        res = std::max(res, f + freq[e + 1]);

    return res;
  }
};
