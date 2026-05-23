#include <algorithm>
#include <set>
#include <vector>

class Solution
{
public:
  int matchPlayersAndTrainers(std::vector<int> &players,
                              std::vector<int> &trainers)
  {
    std::sort(players.begin(), players.end());
    std::multiset<int> set(trainers.begin(), trainers.end());

    int cnt{};
    for (int e : players)
    {
      auto it = set.lower_bound(e);
      if (it != set.end())
      {
        set.erase(it);
        cnt += 1;
      }
    }

    return cnt;
  }
};
