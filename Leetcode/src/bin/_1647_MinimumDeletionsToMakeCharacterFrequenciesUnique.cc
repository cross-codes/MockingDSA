#include <algorithm>
#include <array>
#include <string>

class Solution
{
public:
  int minDeletions(const std::string &s)
  {
    std::array<int, 26> freq{};
    for (const char &c : s)
      freq[c - 'a'] += 1;

    std::sort(freq.begin(), freq.end(), std::greater<int>());

    int deletions{};
    for (int i = 0; i < 26; i++)
    {
      if (freq[i] == 0)
        break;

      auto equal = std::count(freq.begin(), freq.end(), freq[i]);
      deletions += equal - 1;
      for (int j = i + 1; j < 26; j++)
      {
        if (freq[j] == freq[i])
          freq[j] -= 1;
        else
          break;
      }
    }

    return deletions;
  }
};
