#include <algorithm>
#include <array>
#include <climits>
#include <string>

class Solution
{
public:
  int minimumDeletions(const std::string &word, int k)
  {
    std::array<int, 26> freq{};
    for (const char &c : word)
      freq[c - 'a'] += 1;

    int min_deletions{INT_MAX};
    for (int i = 0; i < 26; i++)
    {
      if (freq[i] == 0)
        continue;

      int deletions{};
      for (int j = 0; j < 26; j++)
      {
        if (freq[j] == 0)
          continue;

        if (freq[j] < freq[i])
          deletions += freq[j];
        else
          deletions += std::max(freq[j] - freq[i] - k, 0);
      }

      min_deletions = std::min(deletions, min_deletions);
    }

    return min_deletions;
  }
};
