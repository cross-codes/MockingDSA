#include <stack>
#include <string>

class Solution {
public:
  bool isValid(std::string s) {
    std::stack<char> stk{};
    for (const auto &c : s) {
      switch (c) {
      case '(':
      case '[':
      case '{':
        stk.push(c);
        break;

      case ')':
        if (!stk.empty()) {
          char character = stk.top();
          if (character == '(') {
            stk.pop();
            break;
          } else
            return false;
        } else
          return false;

      case ']':
        if (!stk.empty()) {
          char character = stk.top();
          if (character == '[') {
            stk.pop();
            break;
          } else
            return false;
        } else
          return false;

      case '}':
        if (!stk.empty()) {
          char character = stk.top();
          if (character == '{') {
            stk.pop();
            break;
          } else
            return false;
        } else
          return false;

      default:
        return false;
      }
    }

    return stk.empty();
  }
};
