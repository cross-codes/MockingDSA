#include <algorithm>
#include <array>
#include <climits>
#include <vector>

class Solution
{
public:
  int minCost(int n, std::vector<int> &cuts)
  {
    auto m = cuts.size();
    cuts.insert(cuts.begin(), 0);
    cuts.push_back(n);

    std::ranges::sort(cuts);
    std::array<std::array<int, 102>, 102> d{};
    for (std::size_t diff = 2UZ; diff < m + 2; diff++)
    {
      for (std::size_t i = 0; i < m + 2 - diff; i++)
      {
        std::size_t j{i + diff};
        int minDiff{INT_MAX};
        for (std::size_t k = i + 1; k < j; k++)
          minDiff = std::min(minDiff, d[i][k] + d[k][j]);

        d[i][j] = cuts[j] - cuts[i] + minDiff;
      }
    }

    return d[0][m + 1];
  }
};
