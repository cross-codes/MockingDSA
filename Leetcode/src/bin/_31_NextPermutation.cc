#include <algorithm>
#include <vector>

class Solution
{
public:
  void nextPermutation(std::vector<int> &nums)
  {
    auto r_first = std::make_reverse_iterator(nums.end());
    auto r_last  = std::make_reverse_iterator(nums.begin());
    auto left    = std::is_sorted_until(r_first, r_last);

    if (left != r_last)
    {
      auto right = std::upper_bound(r_first, left, *left);
      std::iter_swap(left, right);
    }

    std::reverse(left.base(), nums.end());
  }

  void prevPermutation(std::vector<int> &nums)
  {
    auto r_first = std::make_reverse_iterator(nums.end());
    auto r_last = std::make_reverse_iterator(nums.begin());
    auto left = std::is_sorted_until(r_first, r_last, std::greater<>());

    if (left != r_last)
    {
      auto right = std::upper_bound(r_first, left, *left, std::greater<>());
      std::iter_swap(left, right);
    }

    std::reverse(left.base(), nums.end());
  }
};
