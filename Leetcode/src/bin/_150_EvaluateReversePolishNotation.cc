#include <stack>
#include <string>
#include <vector>

class Solution
{
public:
  int evalRPN(std::vector<std::string> &tokens)
  {
    std::stack<int> operands{};

    for (const auto &str : tokens)
    {
      if (str == "+" || str == "-" || str == "*" || str == "/")
      {
        int operand1 = operands.top();
        operands.pop();
        int operand2 = operands.top();
        operands.pop();

        switch (str[0])
        {
        case '+':
          operands.push(operand2 + operand1);
          break;

        case '-':
          operands.push(operand2 - operand1);
          break;

        case '*':
          operands.push(operand2 * operand1);
          break;

        case '/':
          operands.push(operand2 / operand1);
          break;

        default:
          throw str[0];
        }
      }
      else
        operands.push(std::stoi(str));
    }

    return operands.top();
  }
};
