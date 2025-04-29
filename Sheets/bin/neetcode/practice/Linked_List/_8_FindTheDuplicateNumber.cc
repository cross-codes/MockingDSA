#include <unordered_set>
#include <vector>

class Solution {
public:
  int findDuplicate(std::vector<int> &nums) {
    std::unordered_set<int> set{};

    for (const int &num : nums) {
      if (set.find(num) != set.end())
        return num;
      else
        set.insert(num);
    }

    return -1;
  }
};
