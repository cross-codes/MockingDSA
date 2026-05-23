#include <algorithm>
#include <vector>

class Solution
{
private:
  auto greedy_positive_(std::vector<int> &nums) -> int
  {
    int n{static_cast<int>(nums.size())};
    int num_steps{};
    for (int i = 0; i < n - 1; i++)
    {
      if (nums[i] == -1)
      {
        nums[i]     = 1;
        nums[i + 1] = -nums[i + 1];
        num_steps += 1;
      }
    }

    if (std::all_of(nums.begin(), nums.end(), [](int num) { return num == 1; }))
      return num_steps;
    else
      return -1;
  }

  auto greedy_negative_(std::vector<int> &nums) -> int
  {
    int n{static_cast<int>(nums.size())};
    int num_steps{};
    for (int i = 0; i < n - 1; i++)
    {
      if (nums[i] == 1)
      {
        nums[i]     = -1;
        nums[i + 1] = -nums[i + 1];
        num_steps += 1;
      }
    }

    if (std::all_of(nums.begin(), nums.end(),
                    [](int num) { return num == -1; }))
      return num_steps;
    else
      return -1;
  }

public:
  bool canMakeEqual(std::vector<int> &nums, int k)
  {
    if (nums.size() == 1)
      return true;

    if (nums.size() == 2)
      return nums[0] == nums[1];

    auto nums_cpy = nums;
    int a         = greedy_positive_(nums);
    if (a != -1 && a <= k)
      return true;

    int b = greedy_negative_(nums_cpy);
    if (b != -1 && b <= k)
      return true;

    return false;
  }
};
