#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <vector>

class Solution
{
public:
  int64_t kthSmallestProduct(std::vector<int> &nums1, std::vector<int> &nums2,
                             int64_t k)
  {
    if (nums1.size() > nums2.size())
      std::swap(nums1, nums2);

    int m = static_cast<int>(nums2.size());

    // num_products less than or equal to val >= k
    auto pred = [&nums1, &nums2, &m, &k](int64_t val) -> bool {
      int64_t products{};
      for (int64_t e : nums1)
      {
        if (e == 0)
          products += (val >= 0) ? m : 0;
        else if (e > 0)
        {
          auto exact        = static_cast<long double>(val) / e;
          int64_t floor_val = static_cast<int64_t>(std::floor(exact));
          auto it = std::upper_bound(nums2.begin(), nums2.end(), floor_val);
          products += m - std::distance(it, nums2.end());
        }
        else
        {
          auto exact       = static_cast<long double>(val) / e;
          int64_t ceil_val = static_cast<int64_t>(std::ceil(exact));
          auto it = std::lower_bound(nums2.begin(), nums2.end(), ceil_val);
          products += std::distance(it, nums2.end());
        }
      }

      return products >= k;
    };

    int64_t L = static_cast<int64_t>(-1e10) - 1;
    int64_t R = static_cast<int64_t>(1e10) + 1;

    while (R - L > 1)
    {
      int64_t M         = std::midpoint(L, R);
      (pred(M) ? R : L) = M;
    }

    return R;
  }
};
