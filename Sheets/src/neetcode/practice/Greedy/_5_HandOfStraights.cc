#include <set>
#include <vector>

class Solution
{
public:
  bool isNStraightHand(std::vector<int> &hand, int groupSize)
  {
    std::multiset<int> set(hand.begin(), hand.end());
    if (set.size() % groupSize != 0)
      return false;

    while (!set.empty())
    {
      int size{1};
      int current = *set.begin();
      set.erase(set.begin());
      for (; size < groupSize; size++)
      {
        auto next = set.find(current + 1);
        if (next == set.end())
          return false;

        current = *next;
        set.erase(next);
      }
    }

    return true;
  }
};
