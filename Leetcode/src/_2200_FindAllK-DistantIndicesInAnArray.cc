#include <cstring>
#include <vector>

class Solution
{
public:
  std::vector<int> findKDistantIndices(std::vector<int> &nums, int key, int k)
  {
    int n = static_cast<int>(nums.size());

    bool good[n];
    std::memset(good, false, sizeof(bool) * n);

    int rm{-1}, lm{-1};
    for (int i = 0; i < n; i++)
      if (nums[i] == key)
      {
        rm = i;
        break;
      }

    for (int i = n - 1; i >= 0; i--)
      if (nums[i] == key)
      {
        lm = i;
        break;
      }

    for (int i = rm; i < n; i++)
    {
      if (nums[i] == key)
        rm = i;

      if (i - rm <= k)
        good[i] = true;
    }

    for (int i = lm; i >= 0; i--)
    {
      if (nums[i] == key)
        lm = i;

      if (lm - i <= k)
        good[i] = true;
    }

    std::vector<int> res{};
    for (int i = 0; i < n; i++)
      if (good[i])
        res.push_back(i);

    return res;
  }
};
