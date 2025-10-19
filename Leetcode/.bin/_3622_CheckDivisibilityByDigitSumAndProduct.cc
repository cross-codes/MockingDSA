#include <numeric>
#include <vector>

class Solution
{
public:
  bool checkDivisibility(int n)
  {
    std::vector<int> digits{};
    int N = n;
    while (N != 0)
    {
      digits.push_back(N % 10);
      N /= 10;
    }

    int sum = std::accumulate(digits.begin(), digits.end(), 0);
    int prod{1};
    for (int e : digits)
      prod *= e;

    if (sum + prod == 0)
      return false;

    if (n % (sum + prod) == 0)
      return true;
    else
      return false;
  }
};
