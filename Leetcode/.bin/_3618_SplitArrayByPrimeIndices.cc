#include <climits>
#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <vector>

class Solution
{
public:
  long long splitArray(std::vector<int> &nums)
  {
    int n = static_cast<int>(nums.size());

    int sieve[100001]{};
    sieve[0] = INT_MIN;
    sieve[1] = 1;
    for (int i = 2; i < 100001; i++)
    {
      if (sieve[i] == 0)
      {
        for (int j = i << 1; j < 100001; j += i)
          sieve[j] = i;
      }
    }

    std::vector<int64_t> A{}, B{};
    for (int i = 0; i < n; i++)
      if (sieve[i] == 0)
        A.push_back(nums[i]);
      else
        B.push_back(nums[i]);

    return std::abs(std::accumulate(A.begin(), A.end(), 0LL) -
                    std::accumulate(B.begin(), B.end(), 0LL));
  }
};
