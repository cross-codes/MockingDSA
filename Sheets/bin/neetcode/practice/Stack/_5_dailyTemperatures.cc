#include <stack>
#include <vector>

class Solution {
public:
  std::vector<int> dailyTemperatures(std::vector<int> &temperatures) {
    int n = static_cast<int>(temperatures.size());

    std::stack<std::pair<int, int>> stk{};
    std::vector<int> res(n);
    for (int i = n - 1; i >= 0; i--) {
      int val = temperatures[i];

      if (stk.empty() || stk.top().first <= val) {
        while (!stk.empty() && stk.top().first <= val)
          stk.pop();
      }

      res[i] = (stk.empty()) ? 0 : stk.top().second - i;
      stk.push({val, i});
    }

    return res;
  }
};
