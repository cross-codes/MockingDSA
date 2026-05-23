#include <unordered_set>
#include <vector>

class Solution {
public:
  bool containsDuplicate(std::vector<int> &nums) {
    std::unordered_set<int> set{};
    for (const int &num : nums) {
      if (set.find(num) == set.end())
        set.insert(num);
      else
        return true;
    }

    return false;
  }
};
