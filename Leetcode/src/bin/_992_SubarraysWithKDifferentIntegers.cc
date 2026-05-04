#include <unordered_map>
#include <vector>

class Solution
{
public:
  int subarraysWithKDistinct(std::vector<int> &nums, int k)
  {
    int n{static_cast<int>(nums.size())};
    std::unordered_map<int, int> in_window{};

    int l{}, r{};
    int at_most_k{}, at_most_k_minus{};
    while (r < n)
    {
      int x = nums[r];
      in_window[x] += 1;

      if (in_window.size() > static_cast<size_t>(k))
      {
        while (in_window.size() > static_cast<size_t>(k) && l < r)
        {
          int freq = in_window[nums[l]];
          if (freq > 1)
            in_window[nums[l]] -= 1;
          else
            in_window.erase(nums[l]);

          l += 1;
        }
      }

      at_most_k += r - l + 1;
      r += 1;
    }

    if (k > 1)
    {
      l = 0, r = 0;
      in_window = std::unordered_map<int, int>();

      while (r < n)
      {
        int x = nums[r];
        in_window[x] += 1;

        if (in_window.size() > static_cast<size_t>(k - 1))
        {
          while (in_window.size() > static_cast<size_t>(k - 1) && l < r)
          {
            int freq = in_window[nums[l]];
            if (freq > 1)
              in_window[nums[l]] -= 1;
            else
              in_window.erase(nums[l]);

            l += 1;
          }
        }

        at_most_k_minus += r - l + 1;
        r += 1;
      }
    }

    return at_most_k - at_most_k_minus;
  }
};
