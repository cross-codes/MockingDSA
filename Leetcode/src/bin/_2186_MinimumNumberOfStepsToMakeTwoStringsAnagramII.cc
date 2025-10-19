#include <array>
#include <string>

class Solution
{
public:
  int minSteps(std::string s, std::string t)
  {
    std::array<int, 26> freq1{}, freq2{};

    for (char c : s)
      freq1[c - 'a'] += 1;

    for (char c : t)
      freq2[c - 'a'] += 1;

    int cnt{};
    for (int i = 0; i < 26; i++)
      cnt += std::abs(freq1[i] - freq2[i]);

    return cnt;
  }
};
