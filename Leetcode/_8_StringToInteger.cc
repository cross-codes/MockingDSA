#include <cstdint>
#include <iostream>
#include <string>

class Solution {
public:
  int myAtoi(std::string s) {
    int64_t res = 0LL;
    bool negative = false, leadingWhitesOver = false, onceSign = false;
    for (const char &c : s) {
      if (c == ' ' && !leadingWhitesOver) [[unlikely]]
        continue;
      else if ((c == '-' || c == '+') && !onceSign) [[unlikely]] {
        if (!leadingWhitesOver) [[unlikely]]
          leadingWhitesOver = true;

        onceSign = true;
        negative = c == '-';
      } else if (std::isdigit(c)) {
        if (!leadingWhitesOver) [[unlikely]]
          leadingWhitesOver = true;

        if (!onceSign) [[unlikely]]
          onceSign = true;

        res = (10 * res) + (c - '0');
        if (res > INT32_MAX) [[unlikely]]
          return (negative) ? INT32_MIN : INT32_MAX;
      } else
        break;
    }

    return static_cast<int>((negative) ? -res : res);
  }
};

int main() { std::cout << Solution().myAtoi("1337c0d3") << "\n"; }
