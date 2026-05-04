#include <vector>

class Solution
{
public:
  int maximumLength(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    int even{}, odd{}, even_odd{}, odd_even{};

    for (int i = 0; i < n; i++)
      if (nums[i] % 2 == 0)
        even += 1;

    for (int i = 0; i < n; i++)
      if (nums[i] % 2 != 0)
        odd += 1;

    bool flip{};
    for (int i = 0; i < n; i++)
    {
      if (flip)
      {
        if (nums[i] % 2 != 0)
        {
          even_odd += 1;
          flip = !flip;
        }
      }
      else
      {
        if (nums[i] % 2 == 0)
        {
          even_odd += 1;
          flip = !flip;
        }
      }
    }

    flip = false;
    for (int i = 0; i < n; i++)
    {
      if (flip)
      {
        if (nums[i] % 2 == 0)
        {
          odd_even += 1;
          flip = !flip;
        }
      }
      else
      {
        if (nums[i] % 2 != 0)
        {
          odd_even += 1;
          flip = !flip;
        }
      }
    }

    return std::max({even, odd, even_odd, odd_even});
  }
};
