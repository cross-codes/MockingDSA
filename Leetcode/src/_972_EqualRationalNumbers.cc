#include <cmath>
#include <string>

class Solution
{
private:
  auto expand_(std::string &s) -> std::string
  {
    int n{static_cast<int>(s.size())};
    if (s.find('.') == s.npos)
      return s;

    std::string res{s.substr(0, s.find('.'))};
    res.push_back('.');
    bool repeating{};
    for (int i = static_cast<int>(s.find('.')) + 1; i < n; i++)
    {
      if (s[i] == '(')
      {
        repeating = true;
        break;
      }
      else
        res.push_back(s[i]);
    }

    if (!repeating)
      return res;

    std::string repeat{};
    for (int i = static_cast<int>(s.find('(')) + 1; i < n - 1; i++)
      repeat.push_back(s[i]);

    for (int i = 0; i < 20; i++)
      res += repeat;

    return res;
  }

public:
  bool isRationalEqual(std::string s, std::string t)
  {
    long double a = std::stold(expand_(s));
    long double b = std::stold(expand_(t));

    a *= 1e16;
    b *= 1e16;

    return std::abs(std::trunc(a) - std::trunc(b)) <
           std::numeric_limits<long double>::epsilon();
  }
};
