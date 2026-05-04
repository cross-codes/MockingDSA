#include <algorithm>
#include <stack>
#include <string>

class Solution
{
public:
  int maximumGain(std::string s, int x, int y)
  {
    int res{};
    if (x > y)
    {
      std::stack<char> stack{};
      for (char c : s)
      {
        if (c == 'b')
        {
          if (!stack.empty() && stack.top() == 'a')
          {
            stack.pop();
            res += x;
          }
          else
            stack.push(c);
        }
        else
          stack.push(c);
      }

      std::string rem{};
      while (!stack.empty())
      {
        char c = stack.top();
        stack.pop();
        rem += c;
      }

      std::reverse(rem.begin(), rem.end());
      std::stack<char> next{};
      for (char c : rem)
      {
        if (c == 'a')
        {
          if (!stack.empty() && stack.top() == 'b')
          {
            stack.pop();
            res += y;
          }
          else
            stack.push(c);
        }
        else
          stack.push(c);
      }
    }
    else
    {
      std::stack<char> stack{};
      for (char c : s)
      {
        if (c == 'a')
        {
          if (!stack.empty() && stack.top() == 'b')
          {
            stack.pop();
            res += y;
          }
          else
            stack.push(c);
        }
        else
          stack.push(c);
      }

      std::string rem{};
      while (!stack.empty())
      {
        char c = stack.top();
        stack.pop();
        rem += c;
      }

      std::reverse(rem.begin(), rem.end());
      std::stack<char> next{};
      for (char c : rem)
      {
        if (c == 'b')
        {
          if (!stack.empty() && stack.top() == 'a')
          {
            stack.pop();
            res += x;
          }
          else
            stack.push(c);
        }
        else
          stack.push(c);
      }
    }

    return res;
  }
};
