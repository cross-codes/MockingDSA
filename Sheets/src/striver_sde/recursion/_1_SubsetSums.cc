#include <cstring>
#include <iostream>
#include <vector>

class Solution
{
public:
  bool isSubsetSum(std::vector<int> arr, int target)
  {
    int n{static_cast<int>(arr.size())};

    bool possible[n + 1][target + 1]; // sum j using [0..i]
    std::memset(possible, false, sizeof(possible));

    for (int i = 0; i <= n; i++)
      possible[i][0] = true;

    for (int i = 1; i <= n; i++)
    {
      int num = arr[i - 1];

      for (int sum = 1; sum <= target; sum++)
      {
        bool res{};
        res |= possible[i - 1][sum];

        if (sum >= num)
          res |= possible[i - 1][sum - num];

        possible[i][sum] = res;
      }
    }

    return possible[n][target];
  }
};

int main()
{
  std::cout << Solution().isSubsetSum({1, 2, 7, 3}, 6) << "\n";
}
