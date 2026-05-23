#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution
{
public:
  int reversePairs(std::vector<int> &nums)
  {
    using namespace __gnu_pbds;

    tree<std::pair<int, int>, null_type, std::less<>, rb_tree_tag,
         tree_order_statistics_node_update>
        ost{};

    int gcnt{}, res{};
    int n = static_cast<int>(nums.size());
    for (int i = n - 1; i >= 0; i--)
    {
      if (nums[i] & 1)
        res += ost.order_of_key({nums[i] >> 1, INT_MAX});
      else
        res += ost.order_of_key({nums[i] >> 1, INT_MIN});

      ost.insert({nums[i], gcnt++});
    }

    return res;
  }
};
