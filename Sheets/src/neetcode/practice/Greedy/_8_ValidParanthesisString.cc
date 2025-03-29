#include <algorithm>
#include <stack>
#include <string>

class Solution
{
public:
  bool checkValidString(std::string s)
  {
    if (s.size() & 1)
      return false;

    auto numLeft  = std::count(s.begin(), s.end(), ')');
    auto numRight = std::count(s.begin(), s.end(), '(');

    std::stack<char> store{};
    for (const auto &c : s)
    {
      switch (c)
      {
      case '(':
        store.push('(');
        break;

      case ')':
        if (!store.empty() && store.top() == '(')
          store.pop();
        else
          return false;
        break;

      case '*':
        if (store.empty())
          store.push('(');
        else if (store.top() == '(')
          store.pop();
        break;
      }
    }
  }
};
