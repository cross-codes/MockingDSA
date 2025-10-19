#include <algorithm>
#include <array>
#include <string>

class Solution
{
public:
  bool closeStrings(std::string word1, std::string word2)
  {
    std::array<int, 26> freq1{}, freq2{};
    for (char c : word1)
      freq1[c - 'a'] += 1;

    for (char c : word2)
      freq2[c - 'a'] += 1;

    for (int i = 0; i < 26; i++)
      if ((freq1[i] != 0 && freq2[i] == 0) || (freq1[i] == 0 && freq2[i] != 0))
        return false;

    std::sort(freq1.begin(), freq1.end());
    std::sort(freq2.begin(), freq2.end());

    return freq1 == freq2;
  }
};
