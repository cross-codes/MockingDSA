#include <algorithm>
#include <string>

class Solution
{
public:
  std::string getPermutation(int n, int k)
  {
    std::string a;
    for (int i = 1; i <= n; i++)
      a.push_back(static_cast<char>('0' + i));

    int cnt{0};
    do
    {
      cnt += 1;
      if (cnt == k)
        break;
    } while (std::next_permutation(a.begin(), a.end()));

    return a;
  }
};
