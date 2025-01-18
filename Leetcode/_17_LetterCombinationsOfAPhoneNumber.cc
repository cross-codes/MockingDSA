#include <string>
#include <vector>

class Solution {
public:
  std::vector<std::string> res{};
  std::vector<std::string> lookup = {"",    "",    "abc",  "def", "ghi",
                                     "jkl", "mno", "pqrs", "tuv", "wxyz"};

  void search(std::string cur, char currentDigit, std::string digits,
              size_t digitIndex) {
    if (currentDigit == '0') {
      res.push_back(cur);
      return;
    }

    for (char c : lookup[currentDigit - '0']) {
      cur.push_back(c);

      if (digitIndex == digits.size() - 1)
        currentDigit = '0';
      else
        currentDigit = digits[digitIndex + 1];

      search(cur, currentDigit, digits, digitIndex + 1);
      cur.pop_back();
    }
  }

  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.size() == 0) [[unlikely]]
      return {};

    search("", digits[0], digits, 0);
    return res;
  }
};
