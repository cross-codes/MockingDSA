#include <stack>
#include <string>

class Solution
{
public:
  bool parseBoolExpr(std::string expression)
  {
    int n = static_cast<int>(expression.size());
    std::stack<char> stack{};
    for (int i = n - 1; i >= 0; i--)
    {
      if (expression[i] == '(')
      {
        if (expression[i - 1] == '&')
        {
          bool res{true};
          while (stack.top() != ')')
          {
            char op = stack.top();
            stack.pop();
            bool eq = (op == 'f') ? false : true;
            res &= eq;
          }

          stack.pop();
          stack.push(res ? 't' : 'f');
          i -= 1;
        }
        else if (expression[i - 1] == '|')
        {
          bool res{};
          while (stack.top() != ')')
          {
            char op = stack.top();
            stack.pop();
            bool eq = (op == 'f') ? false : true;
            res |= eq;
          }

          stack.pop();
          stack.push(res ? 't' : 'f');
          i -= 1;
        }
        else
        {
          char op = stack.top();
          bool eq = (op == 'f') ? false : true;
          stack.pop();
          stack.pop();
          stack.push(!eq ? 't' : 'f');
          i -= 1;
        }
      }
      else if (expression[i] != ',')
        stack.push(expression[i]);
    }

    return stack.top() == 't';
  }
};
