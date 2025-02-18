#include <climits>
#include <cstdlib>
#include <vector>

class Solution {
private:
  auto calculateArea(int heightA, int heightB, std::ptrdiff_t width) -> int {
    return std::min(heightA, heightB) * static_cast<int>(width);
  }

public:
  int maxArea(std::vector<int> &heights) {
    std::ptrdiff_t n = heights.size();
    std::ptrdiff_t l = 0, r = n - 1;

    int maxArea = INT_MIN;
    while (l < r) {
      maxArea = std::max(maxArea, calculateArea(heights[l], heights[r], r - l));

      if (heights[l] > heights[r])
        r--;
      else if (heights[l] < heights[r])
        l++;
      else {
        int gainLeft = heights[l + 1] - heights[l];
        int gainRight = heights[r - 1] - heights[r];
        if (gainLeft > gainRight)
          l++;
        else
          r--;
      }
    }

    return maxArea;
  }
};
