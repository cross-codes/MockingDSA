#include <climits>
#include <vector>

class Solution
{
public:
  int maxSumDivThree(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    // max inclusion with respective mods upto [0...i], 1-idx;
    // if mod == 0, mod_0[i] = mx(mod_0[i - 1]+ num), same for mod_1, mod_2;
    // if mod == 1, mod_0[i] = mx(mod_2[i - 1] + num, mod_0[i - 1]), mod_1[i] =
    // mx(mod_0[i - 1] + num, mod_1[i - 1]), mod_2[i] = mx(mod_1[i - 1] + num,
    // mod_2[i - 1])
    // if mod == 2, similar

    int mod_0[n + 1], mod_1[n + 1], mod_2[n + 1];
    mod_0[0] = 0, mod_1[0] = mod_2[0] = INT_MIN;

    for (int i = 1; i <= n; i++)
    {
      int num = nums[i - 1], mod = num % 3;
      if (mod == 0)
      {
        mod_0[i] = mod_0[i - 1] + num;
        mod_1[i] = mod_1[i - 1] + num;
        mod_2[i] = mod_2[i - 1] + num;
      }
      else if (mod == 1)
      {
        mod_0[i] = std::max(mod_0[i - 1], mod_2[i - 1] + num);
        mod_1[i] = std::max(mod_1[i - 1], mod_0[i - 1] + num);
        mod_2[i] = std::max(mod_2[i - 1], mod_1[i - 1] + num);
      }
      else
      {
        mod_0[i] = std::max(mod_0[i - 1], mod_1[i - 1] + num);
        mod_1[i] = std::max(mod_1[i - 1], mod_2[i - 1] + num);
        mod_2[i] = std::max(mod_2[i - 1], mod_0[i - 1] + num);
      }
    }

    return mod_0[n];
  }
};
