#include <string>

class Solution
{
public:
  int minSteps(std::string s, std::string t)
  {
    int n = static_cast<int>(s.size());
    int freq[26]{};
    for (int i = 0; i < n; i++)
    {
      freq[s[i] - 'a'] -= 1;
      freq[t[i] - 'a'] += 1;
    }

    int cnt{};
    for (int e : freq)
      if (e > 0)
        cnt += e;

    return cnt;
  }
};
