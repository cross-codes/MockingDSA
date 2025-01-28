#include <string>

class Solution {
public:
  bool isPalindrome(int x) {
    if (x < 0)
      return false;
    else {
      std::string equiv = std::to_string(x);
      long long left = 0, right = equiv.size() - 1;
      while (left <= right) {
        if (equiv[left] != equiv[right])
          return false;
        left++, right--;
      }

      return true;
    }
  }
};
