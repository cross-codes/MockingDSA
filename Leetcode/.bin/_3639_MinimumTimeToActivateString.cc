#include <numeric>
#include <set>
#include <string>
#include <vector>

class Solution
{
public:
  int minTime(std::string s, std::vector<int> &order, int k)
  {
    int n = static_cast<int>(order.size());

    // number of valid substrings >= k
    auto pred = [&n, &order, &k](int t) -> bool {
      std::set<int> set{};

      for (int i = 0; i <= t; i++)
        set.insert(order[i]);

      int64_t cnt{};
      for (int i = 0; i < n; i++)
      {
        if (set.empty())
          break;
        cnt += n - *set.begin();
        set.erase(i);
      }

      return cnt >= k;
    };

    int L{-1}, R{n};
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return R == n ? -1 : R;
  }
};
