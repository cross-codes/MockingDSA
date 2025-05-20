#include <vector>

class Solution
{
private:
  auto find_pivot_(std::vector<int> &nums) -> int
  {
    int n{static_cast<int>(nums.size())};
    if (nums[0] <= nums[n - 1])
      return 0;

    int l{-1}, r{n};
    while (r - l > 1)
    {
      int m{l + ((r - l) >> 1)};
      ((nums[m] < nums[0]) ? r : l) = m;
    }

    return r;
  }

  auto equiv_index_(int idx, int pivot_idx, int end_idx) -> int
  {
    if (idx <= end_idx - pivot_idx)
      return idx + pivot_idx;
    else
      return idx - end_idx + pivot_idx - 1;
  }

public:
  int search(std::vector<int> &nums, int target)
  {
    int n{static_cast<int>(nums.size())};
    if (n == 1)
      return (nums[0] == target) ? 0 : -1;

    int pivot = find_pivot_(nums);

    int l{-1}, r{n};
    while (r - l > 1)
    {
      int m{l + ((r - l) >> 1)};
      (target < nums[equiv_index_(m, pivot, n - 1)] ? r : l) = m;
    }

    if (l == -1)
      return -1;

    int potential_idx{equiv_index_(l, pivot, n - 1)};
    return (nums[potential_idx] == target) ? potential_idx : -1;
  }
};
