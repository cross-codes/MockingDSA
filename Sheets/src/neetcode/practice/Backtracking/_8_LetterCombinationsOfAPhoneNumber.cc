#include <string>
#include <vector>

class Solution {
public:
  std::string letters[10] = {"",    "",    "abc",  "def", "ghi",
                             "jkl", "mno", "pqrs", "tuv", "wxyz"};

  std::vector<std::string> res{};

  void search(std::string cur, const std::string &digits, size_t digitIdx) {
    if (digitIdx == digits.size()) {
      res.push_back(cur);
      return;
    }

    unsigned int digit = digits[digitIdx] - '0';
    std::string sequence = letters[digit];

    for (char c : sequence) {
      search(cur + c, digits, digitIdx + 1);
    }
  }

  std::vector<std::string> letterCombinations(std::string digits) {
    if (digits.empty())
      return res;

    search("", digits, 0);
    return res;
  }
};
