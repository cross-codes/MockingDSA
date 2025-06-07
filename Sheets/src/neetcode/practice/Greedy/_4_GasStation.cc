#include <vector>

class Solution
{
private:
  auto simulate_(std::vector<int> &gas, std::vector<int> &cost, int start)
      -> bool
  {
    int tank{gas[start]};
    int n{static_cast<int>(gas.size())};

    for (int i = start; i < n - 1; i++)
    {
      if (tank < cost[i])
        return false;

      tank -= cost[i];
      tank += gas[i + 1];
    }

    if (tank < cost[n - 1])
      return false;

    tank -= cost[n - 1];
    tank += gas[0];

    for (int i = 0; i < start; i++)
    {
      if (tank < cost[i])
        return false;

      tank -= cost[i];
      tank += gas[i + 1];
    }

    return true;
  }

public:
  int canCompleteCircuit(std::vector<int> &gas, std::vector<int> &cost)
  {
    int n{static_cast<int>(gas.size())};
    int num_zeroes{};
    bool neg{false};
    for (int i = 0; i < n; i++)
    {
      if (cost[i] - gas[i] == 0)
        num_zeroes += 1;

      if (cost[i] - gas[i] < 0)
        neg = true;
    }

    if (num_zeroes == n)
      return 0;

    if (!neg)
      return -1;

    for (int i = 0; i < n; i++)
    {
      if (cost[i] - gas[i] < 0)
      {
        bool possible = simulate_(gas, cost, i);
        if (possible)
          return i;
      }
    }

    return -1;
  }
};
