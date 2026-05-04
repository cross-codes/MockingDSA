#include <array>
#include <string>

class Solution
{
public:
  bool isAnagram(const std::string &s, const std::string &t)
  {
    std::array<int, 26> s_freq{}, t_freq{};
    for (const char &c : s)
      s_freq[c - 'a'] += 1;

    for (const char &c : t)
      t_freq[c - 'a'] += 1;

    return s_freq == t_freq;
  }
};
