#include <array>
#include <string>

class Solution
{
public:
  bool checkInclusion(std::string s1, std::string s2)
  {
    int n = static_cast<int>(s2.size());
    int k = static_cast<int>(s1.size());

    if (k > n)
      return false;

    std::array<int, 26> freq2{}, freq1{};
    for (const char &c : s1)
      freq1[c - 'a'] += 1;

    int win_start{};
    for (int i = 0; i < k; i++)
      freq2[s2[i] - 'a'] += 1;

    if (freq2 == freq1)
      return true;

    for (int i = k; i < n; i++)
    {
      freq2[s2[win_start] - 'a'] -= 1;
      freq2[s2[i] - 'a'] += 1;

      win_start += 1;
      if (freq2 == freq1)
        return true;
    }

    return false;
  }
};
