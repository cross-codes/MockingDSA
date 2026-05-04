#include <cstring>
#include <string>
#include <vector>

class Solution
{
public:
  int possibleStringCount(std::string word, int k)
  {
    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

    int n                 = static_cast<int>(word.size());
    std::vector<int> rl{};

    int l{}, r{};
    while (r < n)
    {
      if (word[l] != word[r])
      {
        rl.push_back(r - l);
        l = r;
      }

      r += 1;
    }

    rl.push_back(n - l);

    int64_t total{1};
    for (int e : rl)
    {
      total *= e;
      total %= MOD;
    }

    total %= MOD;

    int N = static_cast<int>(rl.size());

    if (N >= k)
      return static_cast<int>(total);

    int64_t f[N + 1][k], prefix[N + 1][k];
    std::memset(f, 0x00, sizeof(f));
    std::memset(prefix, 0x00, sizeof(prefix));

    f[0][0]      = 1;
    prefix[0][0] = 1;
    for (int i = 1; i < k; i++)
      prefix[0][i] = (prefix[0][i - 1] + f[0][i]) % MOD;

    for (int i = 1; i <= N; i++)
    {
      for (int j = 0; j < k; j++)
      {
        int R     = rl[i - 1];

        int start = std::max(0, j - R);
        int end   = j - 1;

        if (start <= end)
          f[i][j] = (prefix[i - 1][end] -
                     (start > 0 ? prefix[i - 1][start - 1] : 0)) %
                    MOD;

        if (f[i][j] < 0)
          f[i][j] += MOD;
      }

      prefix[i][0] = f[i][0];
      for (int j = 1; j < k; j++)
        prefix[i][j] = (prefix[i][j - 1] + f[i][j]) % MOD;
    }

    return (total - prefix[N][k - 1] + MOD) % MOD;
  }
};
