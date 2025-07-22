#include <cstring>
#include <string>

class Solution
{
public:
  int uniqueLetterString(std::string s)
  {
    int n = static_cast<int>(s.size());
    int last_two[26][2];
    std::memset(last_two, -1, sizeof last_two);

    int res{};
    for (int i = 0; i < n; i++)
    {
      res += (i - last_two[s[i] - 'A'][1]) *
             (last_two[s[i] - 'A'][1] - last_two[s[i] - 'A'][0]);
      last_two[s[i] - 'A'][0] = last_two[s[i] - 'A'][1];
      last_two[s[i] - 'A'][1] = i;
    }

    for (int i = 0; i < 26; i++)
      res += (n - last_two[i][1]) * (last_two[i][1] - last_two[i][0]);

    return res;
  }
};
