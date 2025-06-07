#include <stack>
#include <string>

class Solution
{
public:
  bool checkValidString(std::string s)
  {
    int n{static_cast<int>(s.length())};
    std::stack<int> lefts{}, stars{};

    for (int i = 0; i < n; i++)
    {
      if (s[i] == '(')
        lefts.push(i);
      else if (s[i] == '*')
        stars.push(i);
      else
      {
        if (!lefts.empty())
          lefts.pop();
        else if (!stars.empty())
          stars.pop();
        else
          return false;
      }
    }

    while (!(lefts.empty() || stars.empty()))
    {
      if (lefts.top() < stars.top())
      {
        lefts.pop();
        stars.pop();
      }
      else
        return false;
    }

    return lefts.empty();
  }
};
