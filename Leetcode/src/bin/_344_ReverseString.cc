#include <vector>

class Solution
{
public:
  void reverseString(std::vector<char> &s)
  {
    int n = static_cast<int>(s.size());
    int l{}, r{n - 1};
    while (l <= r)
    {
      std::swap(s[l], s[r]);
      l += 1;
      r -= 1;
    }
  }
};
