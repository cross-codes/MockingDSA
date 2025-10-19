#include <algorithm>
#include <vector>

class Solution
{
public:
  int minSwaps(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    std::vector<int> even{}, odd{};

    for (int i = 0; i < n; i++)
    {
      nums[i] %= 2;
      if (nums[i] == 0)
        even.push_back(i);
      else
        odd.push_back(i);
    }

    int ne = static_cast<int>(std::count(nums.begin(), nums.end(), 0));
    int no = static_cast<int>(std::count(nums.begin(), nums.end(), 1));

    if (std::abs(ne - no) > 1)
      return -1;

    if (!(n & 1))
    {
      if (ne != no)
        return -1;

      else
      {
        int E{}, O{};
        int pos{};
        for (int e : even)
        {
          E += std::abs((e - pos));
          pos += 2;
        }

        pos = 0;
        for (int e : odd)
        {
          O += std::abs((e - pos));
          pos += 2;
        }
        return std::min(O, E);
      }
    }
    else
    {
      if (std::abs(ne - no) != 1)
        return -1;

      if (ne > no)
      {
        int E{};
        int pos{};
        for (int e : even)
        {
          E += std::abs((e - pos));
          pos += 2;
        }

        return E;
      }
      else
      {
        int O{};
        int pos{};
        for (int e : odd)
        {
          O += std::abs((e - pos));
          pos += 2;
        }

        return O;
      }
    }
  }
};
