#include <string>

class Solution {
public:
  bool isPalindrome(std::string s) {
    ptrdiff_t n = s.size();
    ptrdiff_t l = 0, r = n - 1;
    while (!std::isalnum(s[l]))
      l++;
    while (!std::isalnum(s[r]))
      r--;

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
