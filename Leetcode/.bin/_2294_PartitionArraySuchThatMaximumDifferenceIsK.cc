#include <algorithm>
#include <vector>

class Solution
{
public:
  int partitionArray(std::vector<int> &nums, int k)
  {
    std::sort(nums.begin(), nums.end());
    int win_mn{nums[0]}, paritions{1};

    for (int i = 0; i < static_cast<int>(nums.size()); i++)
    {
      if (nums[i] - win_mn > k)
      {
        paritions += 1;
        win_mn = nums[i];
      }
    }

    return paritions;
  }
};
