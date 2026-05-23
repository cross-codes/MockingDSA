#include <vector>

class Solution
{
public:
  bool canJump(std::vector<int> &nums)
  {
    int target{static_cast<int>(nums.size()) - 1};
    while (true)
    {
      int test{target - 1};
      while (test != -1)
      {
        if (nums[test] >= target - test)
        {
          target = test;
          break;
        }
        else
          test--;
      }

      if (target == 0)
        return true;

      if (test == -1)
        return false;
    }
  }
};
