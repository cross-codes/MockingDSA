#include <vector>

class Solution
{
public:
  int countHillValley(std::vector<int> &nums)
  {
    std::vector<int> dedup{};
    int prev{};
    for (int e : nums)
    {
      if (e == prev)
        continue;
      else
      {
        dedup.push_back(e);
        prev = e;
      }
    }

    int n = static_cast<int>(dedup.size());
    int cnt{};
    for (int i = 1; i < n - 1; i++)
    {
      if ((dedup[i] > dedup[i - 1] && dedup[i] > dedup[i + 1]) ||
          (dedup[i] < dedup[i - 1] && dedup[i] < dedup[i + 1]))
        cnt += 1;
    }

    return cnt;
  }
};
