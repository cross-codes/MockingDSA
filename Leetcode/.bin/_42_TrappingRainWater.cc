#include <vector>

class Solution
{
public:
  int trap(std::vector<int> &height)
  {
    if (height.empty())
      return 0;

    std::size_t n = height.size();
    std::size_t l{0}, r{n - 1};

    int left_max_height{height[l]}, right_max_height{height[r]};
    int ans{};
    while (l < r)
    {
      if (left_max_height < right_max_height)
      {
        l++;
        left_max_height = std::max(left_max_height, height[l]);
        ans += left_max_height - height[l];
      }
      else
      {
        r--;
        right_max_height = std::max(right_max_height, height[r]);
        ans += right_max_height - height[r];
      }
    }

    return ans;
  }
};
