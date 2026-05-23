#include <stack>

class MinStack
{
  std::stack<int> mn{}, elem{};

public:
  MinStack()
  {
  }

  void push(int val)
  {
    elem.push(val);
    if (mn.empty() || mn.top() >= val)
      mn.push(val);
  }

  void pop()
  {
    int x = elem.top();
    elem.pop();
    if (x == mn.top())
      mn.pop();
  }

  int top()
  {
    return elem.top();
  }

  int getMin()
  {
    return mn.top();
  }
};
