#include <string>

class Solution
{
public:
  bool checkValidString(std::string s)
  {
    int n{static_cast<int>(s.length())};
    int k{}, depth{};

    for (int i = 0; i < n; i++)
    {
      if (s[i] == '(')
        depth++;

      if (s[i] == '*')
      {
        depth++;
        k++;
      }

      if (s[i] == ')')
        depth--;

      if (depth < 0)
        return false;
    }

    int x = std::max(0, depth - k);
    return depth - (x << 1) >= 0;
  }
};
