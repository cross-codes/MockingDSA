#include <cstdint>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <vector>

#pragma GCC target("popcnt")

class Solution
{
public:
  std::vector<int> popcountDepth(std::vector<long long> &nums,
                                 std::vector<std::vector<long long>> &queries)
  {
    int n = static_cast<int>(nums.size());
    int64_t pd[n];
    std::memset(pd, 0x00, sizeof pd);

    __gnu_pbds::tree<std::pair<int64_t, int64_t>, __gnu_pbds::null_type,
                     std::less<>, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>
        ost{};

    for (int i = 0; i < n; i++)
    {
      int64_t e = nums[i];
      int64_t cnt{};
      while (e != 1)
      {
        e = __builtin_popcountll(e);
        cnt += 1;
      }

      pd[i] = cnt;
      ost.insert({cnt, i});
    }

    std::vector<int> res{};
    for (const auto &q : queries)
    {
      int64_t type = q[0];
      if (type == 1)
      {
        int64_t l = q[1], r = q[2], d = q[3];
        auto sit = ost.order_of_key({d, l});
        auto eit = ost.order_of_key({d, r + 1});
        res.push_back(static_cast<int>(eit - sit));
      }
      else
      {
        int64_t idx = q[1], val = q[2];
        ost.erase({pd[idx], idx});
        int64_t cnt{};
        while (val != 1)
        {
          val = __builtin_popcountll(val);
          cnt += 1;
        }
        pd[idx] = cnt;
        ost.insert({cnt, idx});
      }
    }

    return res;
  }
};
