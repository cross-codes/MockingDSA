#include <climits>
#include <vector>

class Solution
{
public:
  int minXor(const std::vector<int> &nums, int k)
  {
    int n = static_cast<int>(nums.size());

    // this prefix implementation is half open [L, R)
    int prefix[n + 1];
    prefix[0] = 0;
    for (int i = 1; i <= n; i++)
      prefix[i] = prefix[i - 1] ^ nums[i - 1];

    // min value of the maximum subarray xor when [0..i] is split into j
    // partitions
    int min_val[n][k + 1];

    // impossible to make 0 partitions
    for (int i = 0; i < n; i++)
      min_val[i][0] = INT_MAX;

    // impossible to partition nothing (non empty subarrays)
    for (int i = 1; i <= k; i++)
      min_val[0][i] = INT_MAX;

    // single partition is simply XOR of the range [0..i];
    for (int i = 0; i < n; i++)
      min_val[i][1] = prefix[i + 1] ^ prefix[0];

    // min_val[i][x] = minj(max(min_val[j][x - 1], XOR[j+1..i]))
    // because we already know the min value of the maximum subarray for the
    // smaller partitions
    for (int x = 2; x <= k; x++)
      for (int i = 1; i < n; i++)
      {
        min_val[i][x] = INT_MAX;

        for (int j = 0; j < i; j++)
        {
          int max_xor_subarray =
              std::max(min_val[j][x - 1], prefix[i + 1] ^ prefix[j + 1]);

          min_val[i][x] = std::min(max_xor_subarray, min_val[i][x]);
        }
      }

    return min_val[n - 1][k];
  }
};
