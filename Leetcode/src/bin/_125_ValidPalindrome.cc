#include <string>

class Solution {
public:
  bool isPalindrome(std::string s) {
    std::ptrdiff_t n = s.size();
    std::ptrdiff_t l = 0, r = n - 1;
    while (l < n && !std::isalnum(s[l]))
      l++;
    while (r >= 0 && !std::isalnum(s[r]))
      r--;

    if (l == n || r == -1)
      return true;

    while (l < r) {
      char leftc = static_cast<char>(std::tolower(s[l]));
      char rightc = static_cast<char>(std::tolower(s[r]));
      if (leftc != rightc)
        return false;
      else {
        l++, r--;
        while (!std::isalnum(s[l]))
          l++;
        while (!std::isalnum(s[r]))
          r--;
      }
    }

    return true;
  }
};
