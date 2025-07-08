#include <algorithm>
#include <string>

class Solution
{
private:
  auto conv(int num, int base) -> std::string
  {
    const std::string chars{"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    std::string res{};
    while (num != 0)
    {
      res.push_back(chars[num % base]);
      num /= base;
    }

    std::reverse(res.begin(), res.end());
    return res;
  };

public:
  std::string concatHex36(int n)
  {
    return conv(n * n, 16) + conv(n * n * n, 36);
  }
};
