#include <stack>

class MinStack
{
private:
  std::stack<int> mainStack_{};
  std::stack<int> minStack_{};

public:
  MinStack() : mainStack_(), minStack_()
  {
  }

  void push(int val)
  {
    mainStack_.push(val);
    if (minStack_.empty() || val <= minStack_.top())
      minStack_.push(val);
  }

  void pop()
  {
    int val = mainStack_.top();
    mainStack_.pop();
    if (!minStack_.empty() && val == minStack_.top())
      minStack_.pop();
  }

  int top()
  {
    return mainStack_.top();
  }

  int getMin()
  {
    return minStack_.top();
  }
};
