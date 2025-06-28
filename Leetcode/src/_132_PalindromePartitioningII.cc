#include <cstring>
#include <string>

class Solution
{
public:
  int minCut(std::string inp)
  {
    int n = static_cast<int>(inp.size());
    std::string s((n << 1) + 1, '#');

    for (int i = 0; i < n; i++)
      s[(i << 1) + 1] = inp[i];

    n = static_cast<int>(s.size());
    int left{}, right{};
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
    }

    if (len[n >> 1] == (n >> 1) + 1)
      return 0;

    int cuts{}, i{1};
    while (i < n)
    {
      int jmp{};
      for (int j = i; j < n; j++)
        if (j - len[j] + 1 <= i)
          jmp = len[j] + j;

      i = jmp;
      if (i < n)
        cuts += 1;
    }

    return cuts;
  }
};
