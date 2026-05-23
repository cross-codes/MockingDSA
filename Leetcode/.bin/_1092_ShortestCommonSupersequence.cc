#include <algorithm>
#include <cassert>
#include <cstring>
#include <string>
#include <vector>

class Solution
{
public:
  std::string shortestCommonSupersequence(std::string s, std::string t)
  {
    int n = static_cast<int>(s.size());
    int m = static_cast<int>(t.size());

    int l[n + 1][m + 1];
    std::memset(l, 0x00, sizeof l);

    std::vector<int> idx1{}, idx2{};

    for (int y = 1; y <= n; y++)
      for (int x = 1; x <= m; x++)
        if (s[y - 1] == t[x - 1])
          l[y][x] = 1 + l[y - 1][x - 1];
        else
          l[y][x] = std::max(l[y - 1][x], l[y][x - 1]);

    int cy{n}, cx{m};
    while (l[cy][cx] != 0)
    {
      if (s[cy - 1] == t[cx - 1])
      {
        idx1.push_back(cy - 1);
        idx2.push_back(cx - 1);

        cy -= 1;
        cx -= 1;
      }
      else
      {
        if (l[cy - 1][cx] > l[cy][cx - 1])
          cy -= 1;
        else
          cx -= 1;
      }
    }

    std::reverse(idx1.begin(), idx1.end());
    std::reverse(idx2.begin(), idx2.end());
    assert(idx1.size() == idx2.size());

    int N = static_cast<int>(idx1.size());

    std::string res{};

    int ptr1{}, ptr2{}, op{};
    while (op != N)
    {
      int end1 = idx1[op];
      int end2 = idx2[op];

      while (ptr1 != end1)
      {
        res.push_back(s[ptr1]);
        ptr1 += 1;
      }

      while (ptr2 != end2)
      {
        res.push_back(t[ptr2]);
        ptr2 += 1;
      }

      res.push_back(t[end2]);
      op += 1;
      ptr1 += 1;
      ptr2 += 1;
    }

    res += s.substr(ptr1, std::string::npos);
    res += t.substr(ptr2, std::string::npos);

    return res;
  }
};
