#include <set>
#include <vector>

class Solution {
public:
  int lengthOfLIS(std::vector<int> &nums) {
    std::set<int> sequence{};

    for (const int &num: nums) {
      auto it = sequence.lower_bound(num);
      if (it == sequence.end())
        sequence.insert(num);
      else
        sequence.erase(it), sequence.insert(num);
    }

    return static_cast<int>(sequence.size());
  }
};
