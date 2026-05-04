#include <unordered_map>
#include <vector>

class Solution
{
public:
  bool containsNearbyDuplicate(std::vector<int> &nums, int k)
  {
    int n{static_cast<int>(nums.size())};
    std::unordered_map<int, int> window{};

    int r{};
    while (r < k + 1 && r < n)
    {
      window[nums[r]] += 1;
      r += 1;
    }

    if (static_cast<int>(window.size()) < std::min(n, k + 1))
      return true;

    int window_start{};
    while (r < n)
    {
      int remove = nums[window_start];
      if (window[remove] == 1)
        window.erase(remove);
      else
        window[remove] -= 1;

      window_start += 1;

      window[nums[r]] += 1;
      r += 1;

      if (static_cast<int>(window.size()) < k + 1)
        return true;
    }

    return false;
  }
};
