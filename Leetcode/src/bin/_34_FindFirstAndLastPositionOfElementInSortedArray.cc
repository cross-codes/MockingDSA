#include <algorithm>
#include <vector>

class Solution
{
public:
  std::vector<int> searchRange(std::vector<int> &nums, int target)
  {
    std::vector<int> res{};

    auto first = std::lower_bound(nums.begin(), nums.end(), target);
    if (first != nums.end() && *first == target)
      res.push_back(static_cast<int>(std::distance(nums.begin(), first)));
    else
      res.push_back(-1);

    auto last = std::upper_bound(nums.begin(), nums.end(), target);
    if (last != nums.begin() && *(--last) == target)
      res.push_back(static_cast<int>(std::distance(nums.begin(), last)));
    else
      res.push_back(-1);

    return res;
  }
};
