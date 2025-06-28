#include <array>
#include <vector>

class Solution
{
public:
  int longestArithSeqLength(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());
    std::array<int, 1001> ones_array;
    ones_array.fill(1);

    std::vector<std::array<int, 1001>> seq_lengths(n, ones_array);

    int res{1};
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < i; j++)
      {
        int diff                   = nums[i] - nums[j];
        seq_lengths[i][diff + 500] = seq_lengths[j][diff + 500] + 1;
        res                        = std::max(res, seq_lengths[i][diff + 500]);
      }
    }

    return res;
  }
};
