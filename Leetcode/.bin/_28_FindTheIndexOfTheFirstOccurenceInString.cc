#include <cstring>
#include <string>

class Solution
{
public:
  int strStr(std::string haystack, std::string needle)
  {
    int m{static_cast<int>(haystack.size())},
        n{static_cast<int>(needle.size())};
    needle += "\u011F" + haystack;
    int pi[n + m + 2];
    std::memset(pi, 0x00, sizeof(int) * (n + m + 2));

    for (int i = 1; i < n + m + 2; i++)
    {
      int j = pi[i - 1];
      while (j > 0 && needle[i] != needle[j])
        j = pi[j - 1];

      if (needle[i] == needle[j])
        j += 1;

      pi[i] = j;
      if (i >= n + 1 && pi[i] == n)
        return i - (n << 1) - 1;
    }

    return -1;
  }
};
