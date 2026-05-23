#include <vector>

class CustomStack
{
private:
  std::vector<int> vec;
  int n;

public:
  CustomStack(int n) : n{n}
  {
  }

  void push(int x)
  {
    int N = static_cast<int>(vec.size());
    if (N >= n)
      return;
    vec.push_back(x);
  }

  int pop()
  {
    if (vec.empty())
      return -1;
    else
    {
      int x = vec.back();
      vec.pop_back();
      return x;
    }
  }

  void increment(int k, int val)
  {
    int N = static_cast<int>(vec.size());
    for (int i = 0; i < std::min(N, k); i++)
      vec[i] += val;
  }
};
