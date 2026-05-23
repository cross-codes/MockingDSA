#include <cstdint>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

class Solution
{
public:
  long long goodTriplets(std::vector<int> &nums1, std::vector<int> &nums2)
  {
    using namespace __gnu_pbds;

    int n = static_cast<int>(nums1.size());

    size_t lesser[n], greater[n];

    tree<int, null_type, std::less<>, rb_tree_tag,
         tree_order_statistics_node_update>
        low{};

    int pos[100001];

    for (int i = 0; i < n; i++)
      pos[nums2[i]] = i;

    for (int i = 0; i < n; i++)
    {
      lesser[nums1[i]] = low.order_of_key(pos[nums1[i]]);
      low.insert(pos[nums1[i]]);
    }

    tree<int, null_type, std::greater<>, rb_tree_tag,
         tree_order_statistics_node_update>
        high{};

    for (int i = n - 1; i >= 0; i--)
    {
      greater[nums1[i]] = high.order_of_key(pos[nums1[i]]);
      high.insert(pos[nums1[i]]);
    }

    int64_t res{};
    for (int i = 0; i < n; i++)
      res += lesser[i] * greater[i];

    return res;
  }
};
