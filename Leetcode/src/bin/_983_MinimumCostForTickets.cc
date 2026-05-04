#include <array>
#include <vector>

class Solution
{
public:
  int mincostTickets(std::vector<int> &days, std::vector<int> &costs)
  {
    int n = static_cast<int>(days.size());

    std::array<int, 366> cost{};
    int i{};

    for (int day = 1; day <= 365; day++)
    {
      if (i == n)
        break;

      if (day < days[i])
        cost[day] = cost[day - 1];
      else
      {
        cost[day] = cost[day - 1] + costs[0];
        cost[day] = std::min(cost[day], cost[std::max(0, day - 7)] + costs[1]);
        cost[day] = std::min(cost[day], cost[std::max(0, day - 30)] + costs[2]);
        i += 1;
      }
    }

    return cost[days[n - 1]];
  }
};
