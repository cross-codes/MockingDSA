#include <vector>

class Solution
{
public:
  std::vector<std::vector<int>> generate(int numRows)
  {
    std::vector<std::vector<int>> res{};
    res.push_back({1});
    if (numRows == 1)
      return res;

    res.push_back({1, 1});
    if (numRows == 2)
      return res;

    for (int i = 3; i <= numRows; i++)
    {
      std::vector<int> row(i, 1);
      for (int j = 1; j < i - 1; j++)
        row[j] = res.back()[j - 1] + res.back()[j];

      res.push_back(row);
    }

    return res;
  }
};
