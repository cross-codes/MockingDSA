#include <climits>
#include <deque>
#include <vector>

class Solution
{
public:
  int longestOnes(std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());
    std::deque<int> queue{};

    int mx{INT_MIN}, l{}, r{}, cnt{};
    while (r < n)
    {
      if (cnt < k)
      {
        if (nums[r] == 0)
        {
          queue.push_back(r);
          mx = std::max(mx, r - l + 1);
          cnt += 1;
        }
        else
          mx = std::max(mx, r - l + 1);
      }
      else
      {
        if (nums[r] == 0)
        {
          mx = std::max(mx, r - l);
          if (!queue.empty())
          {
            l = queue.front() + 1;
            queue.pop_front();
          }
          else
            l = r + 1;

          if (!queue.empty())
            queue.push_back(r);
        }
        else
          mx = std::max(mx, r - l + 1);
      }

      r += 1;
    }

    return mx;
  }
};
