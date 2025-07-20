#include <cstring>
#include <vector>

class Solution
{
public:
  std::vector<int> productExceptSelf(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int behind[n], infront[n];
    std::memset(behind, 0x00, sizeof behind);
    std::memset(infront, 0x00, sizeof infront);

    behind[0] = nums[0];
    for (int i = 1; i < n; i++)
      behind[i] = behind[i - 1] * nums[i];

    infront[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; i--)
      infront[i] = infront[i + 1] * nums[i];

    std::vector<int> res(n);
    res[0]     = infront[1];
    res[n - 1] = behind[n - 2];
    for (int i = 1; i < n - 1; i++)
      res[i] = behind[i - 1] * infront[i + 1];

    return res;
  }
};
