#include <algorithm>
#include <array>
#include <vector>

class Solution
{
public:
  int longestSubsequence(std::vector<int> &arr, int d)
  {
    int n = static_cast<int>(arr.size());
    // l[i] -> length of longest AP ending at nums[i] with diff d
    // l[i] = max(1, l[i - d] + 1)
    constexpr int N = 10000;
    std::array<int, (N << 1) + 1> l{};

    if (d >= 0)
    {
      for (int i = 0; i < n; i++)
      {
        if (d != 0)
          l[arr[i] + N] = std::max(1, l[arr[i] + N]);
        if (arr[i] - d + N >= 0)
          l[arr[i] + N] = std::max(l[arr[i] + N], l[arr[i] - d + N] + 1);
      }
    }
    else
    {
      d = -d;
      for (int i = n - 1; i >= 0; i--)
      {
        l[arr[i] + N] = 1;
        if (arr[i] - d + N >= 0)
          l[arr[i] + N] = std::max(l[arr[i] + N], l[arr[i] - d + N] + 1);
      }
    }

    return *std::max_element(l.begin(), l.end());
  }
};
