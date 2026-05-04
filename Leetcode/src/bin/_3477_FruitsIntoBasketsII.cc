#include <cstring>
#include <vector>

class Solution
{
public:
  int numOfUnplacedFruits(std::vector<int> &fruits, std::vector<int> &baskets)
  {
    int n = static_cast<int>(baskets.size());

    bool used[n];
    std::memset(used, false, sizeof used);

    int cnt{};
    for (int i = 0; i < n; i++)
    {
      int x = fruits[i];
      bool placed{};
      for (int j = 0; j < n; j++)
      {
        if (baskets[j] >= x && !used[j])
        {
          used[j] = true;
          placed  = true;
          break;
        }
      }

      if (!placed)
        cnt += 1;
    }

    return cnt;
  }
};
