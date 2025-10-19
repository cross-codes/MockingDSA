#include <array>
#include <string>

class Solution {
 private:
  inline static std::array<std::pair<char, char>, 7> symbols{
      std::make_pair('I', 'V'), std::make_pair('X', 'L'),
      std::make_pair('C', 'D'), std::make_pair('M', '?')};

 public:
  std::string intToRoman(int num) {
    std::string equiv{std::to_string(num)};
    std::size_t n{equiv.size()};
    std::string res{};

    std::size_t fvcnt = 0UZ;
    for (char digit : equiv) {
      if (digit == '4') {
        res.push_back(symbols[n - fvcnt - 1].first);
        res.push_back(symbols[n - fvcnt - 1].second);
        goto inc;
      }

      if (digit == '9') {
        res.push_back(symbols[n - fvcnt - 1].first);
        res.push_back(symbols[n - fvcnt].first);
        goto inc;
      }

      if (digit >= '5') {
        res.push_back(symbols[n - fvcnt - 1].second);
        for (int i = 0; i < digit - '5'; i++)
          res.push_back(symbols[n - fvcnt - 1].first);
      }

      if (digit < '5') {
        for (int i = 0; i < digit - '0'; i++)
          res.push_back(symbols[n - fvcnt - 1].first);
      }

    inc:
      fvcnt++;
    }

    return res;
  }
};
