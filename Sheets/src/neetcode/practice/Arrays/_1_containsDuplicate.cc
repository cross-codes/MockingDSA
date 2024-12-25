#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution {
public:
  bool hasDuplicate(std::vector<int> &nums) {
    __gnu_pbds::gp_hash_table<int, void *> set{};
    for (int num: nums) {
      if (set.find(num) == set.end()) {
        set.insert({num, nullptr});
      } else
        return true;
    }
    return false;
  }
};