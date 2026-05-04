#include <climits>
#include <stack>
#include <vector>

class Solution {
public:
  inline int area(int length, int height) { return length * height; }

  int largestRectangleArea(std::vector<int> &heights) {
    int n = static_cast<int>(heights.size());
    std::stack<std::pair<int, int>> forwardStack{}, backwardStack{};
    std::vector<int> smallerValuesBehind(n);

    for (int i = 0; i < n; i++) {
      int val = heights[i];
      if (forwardStack.empty() || forwardStack.top().first >= val) {
        while (!forwardStack.empty() && forwardStack.top().first >= val)
          forwardStack.pop();
      }

      smallerValuesBehind[i] =
          (forwardStack.empty()) ? -1 : forwardStack.top().second;
      forwardStack.push({val, i});
    }

    int maxArea = INT_MIN;
    for (int i = n - 1; i >= 0; i--) {
      int val = heights[i];
      if (backwardStack.empty() || backwardStack.top().first >= val) {
        while (!backwardStack.empty() && backwardStack.top().first >= val)
          backwardStack.pop();
      }

      int right = (backwardStack.empty()) ? n : backwardStack.top().second;
      int height = heights[i], left = smallerValuesBehind[i];
      maxArea =
          std::max(maxArea, this->area(height, right - 1 - (left + 1) + 1));

      backwardStack.push({val, i});
    }

    return maxArea;
  }
};
