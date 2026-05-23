#include <cstdint>
#include <vector>

class Solution
{
public:
  int numOfSubarrays(std::vector<int> &arr)
  {
    int n             = static_cast<int>(arr.size());

    constexpr int MOD = static_cast<int>(1e9 + 7);

    int64_t prefix[n + 1], ne[n + 1], no[n + 1];
    prefix[0] = 0, ne[0] = 1, no[0] = 0;
    for (int i = 1; i <= n; i++)
    {
      prefix[i] = prefix[i - 1] + arr[i - 1];
      ne[i]     = ne[i - 1] + (prefix[i] % 2 == 0);
      no[i]     = no[i - 1] + (prefix[i] % 2 != 0);
    }

    int64_t cnt{};
    for (int i = 1; i <= n; i++)
    {
      if (prefix[i] & 1)
        cnt += ne[i - 1];
      else
        cnt += no[i - 1];

      cnt %= MOD;
    }

    return static_cast<int>(cnt);
  }
};
