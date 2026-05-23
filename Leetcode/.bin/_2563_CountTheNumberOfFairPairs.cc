#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution
{
public:
  long long countFairPairs(std::vector<int> &nums, int lower, int upper)
  {
    int64_t num_pairs{};
    __gnu_pbds::tree<std::pair<int, int>, __gnu_pbds::null_type, std::less<>,
                     __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>
        ost{};

    int uid = 0;
    for (const int &x : nums)
    {
      num_pairs += ost.order_of_key({upper - x + 1, 0}) -
                   ost.order_of_key({lower - x, 0});
      ost.insert({x, uid++});
    }

    return num_pairs;
  }
};
