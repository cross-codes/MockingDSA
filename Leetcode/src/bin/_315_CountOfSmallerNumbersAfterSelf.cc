#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution
{
public:
  std::vector<int> countSmaller(std::vector<int> &nums)
  {
    using namespace __gnu_pbds;

    int n = static_cast<int>(nums.size());
    tree<std::pair<int, int>, null_type, std::less<>, rb_tree_tag,
         tree_order_statistics_node_update>
        ost{};

    std::vector<int> counts(n, 0);
    int gcnt{};
    for (int i = n - 1; i >= 0; i--)
    {
      counts[i] = static_cast<int>(ost.order_of_key({nums[i], INT_MIN}));
      ost.insert({nums[i], gcnt++});
    }

    return counts;
  }
};
