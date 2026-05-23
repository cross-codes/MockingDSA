#include <cstring>
#include <string>

class Solution
{
public:
  int countSubstrings(std::string input)
  {
    int n  = static_cast<int>(input.size());

    auto s = std::string((n << 1) + 1, '#');
    for (int i = 0; i < n; i++)
      s[(i << 1) + 1] = input[i];

    n = (n << 1) + 1;
    int left{}, right{}, pos{};

    int len[n];
    std::memset(len, 0x00, sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
      int l{1};
      if (i <= right)
        l = std::min(right - i + 1, len[left + right - i]);

      while (i >= l && i + l < n && s[i - l] == s[i + l])
      {
        l += 1;
        left  = i - l + 1;
        right = i + l - 1;
      }

      len[i] = l;
      if (len[i] > len[pos])
        pos = i;
    }

    int res{};
    for (int i = 0; i < n; i++)
    {
      int end = std::min(i, std::min(n - i - 1, len[i]));
      res += ((end - 1 - ((i & 1) ^ 1)) >> 1) + 1;
    }

    return res;
  }
};
