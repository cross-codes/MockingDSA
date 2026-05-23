#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution
{
public:
  int createSortedArray(std::vector<int> &instructions)
  {
    using namespace __gnu_pbds;

    constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

    tree<std::pair<int, int>, null_type, std::less<>, rb_tree_tag,
         tree_order_statistics_node_update>
        ost{};

    int gcnt{};
    int64_t cost{};
    for (int e : instructions)
    {
      size_t lesser  = ost.order_of_key({e, INT_MIN});
      size_t greater = ost.size() - ost.order_of_key({e, INT_MAX});
      cost           = (cost + std::min(lesser, greater)) % MOD;
      ost.insert({e, gcnt++});
    }

    return static_cast<int>(cost);
  }
};
