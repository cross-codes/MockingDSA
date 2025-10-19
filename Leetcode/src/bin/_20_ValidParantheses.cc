#include <stack>
#include <string>

class Solution {
public:
  bool isValid(std::string s) {
    std::stack<char> stk;
    for (const char &c : s) {
      switch (c) {
      case '(':
      case '[':
      case '{':
        stk.push(c);
        break;

      case ')':
        if (stk.empty() || stk.top() != '(')
          return false;
        else
          stk.pop();

        break;

      case ']':
        if (stk.empty() || stk.top() != '[')
          return false;
        else
          stk.pop();

        break;

      case '}':
        if (stk.empty() || stk.top() != '{')
          return false;
        else
          stk.pop();

        break;

      default:
        throw c;
      }
    }

    return stk.empty();
  }
};
