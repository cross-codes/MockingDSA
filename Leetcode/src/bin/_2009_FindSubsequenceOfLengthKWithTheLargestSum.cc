#include <algorithm>
#include <set>
#include <vector>

class Solution
{
public:
  std::vector<int> maxSubsequence(std::vector<int> &nums, int k)
  {
    int n                  = static_cast<int>(nums.size());
    std::vector<int> clone = nums;

    std::nth_element(nums.begin(), nums.begin() + n - k, nums.end());
    std::multiset<int> set(nums.begin() + n - k, nums.end());

    std::vector<int> res{};
    for (int i = 0; i < n; i++)
    {
      if (set.empty())
        break;

      if (set.contains(clone[i]))
      {
        res.push_back(clone[i]);
        set.erase(set.find(clone[i]));
      }
    }

    return res;
  }
};
