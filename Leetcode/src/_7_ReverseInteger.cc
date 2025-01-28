#include <climits>

class Solution {
public:
  int reverse(int x) {
    bool negative = false;
    if (x == INT_MIN) [[unlikely]]
      return 0;

    if (x < 0)
      negative = true, x = -x;

    int res = 0;
    while (x != 0) {
      if (res >= INT_MAX / 10.0) [[unlikely]]
        return 0;
      res = (10 * res) + (x % 10);
      x /= 10;
    }

    return (negative) ? -res : res;
  }
};
