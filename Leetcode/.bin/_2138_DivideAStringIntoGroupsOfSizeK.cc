#include <string>
#include <vector>

class Solution
{
public:
  std::vector<std::string> divideString(std::string s, int k, char fill)
  {
    int n = static_cast<int>(s.length());
    std::vector<std::string> res{};

    while (n % k != 0)
      s += fill, n += 1;

    for (int i = 0; i < n - k + 1; i += k)
      res.push_back(s.substr(i, k));

    return res;
  }
};
