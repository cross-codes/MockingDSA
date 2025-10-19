#include <string>

class Solution
{
public:
  std::string makeFancyString(std::string s)
  {
    int n = static_cast<int>(s.size());

    if (s.size() <= 2)
      return s;

    std::string res{};

    for (int i = 0; i < n - 2; i++)
    {
      if ((s[i] == s[i + 1]) && (s[i + 1] == s[i + 2]))
        continue;
      else
        res.push_back(s[i]);
    }

    res += s.substr(n - 2, s.npos);
    return res;
  }
};
