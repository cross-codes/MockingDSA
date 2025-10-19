#include <algorithm>
#include <numeric>
#include <string>
#include <vector>

class Solution
{
public:
  int minLength(std::string s, int numOps)
  {
    std::vector<int> rl{};
    int n = static_cast<int>(s.size());
    int l{}, r{};
    while (r < n)
    {
      if (s[l] != s[r])
      {
        rl.push_back(r - l);
        l = r;
      }

      r += 1;
    }

    rl.push_back(r - l);

    if (numOps == 0)
      return *std::max_element(rl.begin(), rl.end());

    auto pred = [&s, &numOps, &n, &rl](int k) -> bool {
      if (k == 1)
      {
        int cnt1{};
        // 01...
        for (int i = 0; i < n; i++)
        {
          if (i % 2 == 0)
            cnt1 += s[i] != '0';
          else
            cnt1 += s[i] == '0';
        }

        if (cnt1 <= numOps)
          return true;

        int cnt2{};
        for (int i = 0; i < n; i++)
        {
          if (i % 2 == 0)
            cnt2 += s[i] != '1';
          else
            cnt2 += s[i] == '1';
        }

        return cnt2 <= numOps;
      }
      else
      {
        int tot{};
        for (int e : rl)
          tot += e / (k + 1);

        return tot <= numOps;
      }
    };

    if (pred(1))
      return 1;

    int L{1}, R{*std::max_element(rl.begin(), rl.end()) + 1};
    while (R - L > 1)
    {
      int M             = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return R;
  }
};
