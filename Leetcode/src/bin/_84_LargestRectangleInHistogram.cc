#include <stack>
#include <vector>

class Solution
{
public:
  int largestRectangleArea(std::vector<int> &heights)
  {
    int n = static_cast<int>(heights.size());

    int lnxt[n], rnxt[n];
    std::stack<std::pair<int, int>> stack{};
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && stack.top().first >= heights[i])
        stack.pop();

      if (stack.empty())
        lnxt[i] = -1;
      else
        lnxt[i] = stack.top().second;

      stack.emplace(heights[i], i);
    }

    std::stack<std::pair<int, int>> new_stack{};
    for (int i = n - 1; i >= 0; i--)
    {
      while (!new_stack.empty() && new_stack.top().first >= heights[i])
        new_stack.pop();

      if (new_stack.empty())
        rnxt[i] = n;
      else
        rnxt[i] = new_stack.top().second;

      new_stack.emplace(heights[i], i);
    }

    int mx{};
    for (int i = 0; i < n; i++)
    {
      int ls = lnxt[i], rs = rnxt[i];
      mx = std::max((rs - ls - 1) * heights[i], mx);
    }

    return mx;
  }
};
