#include <climits>
#include <vector>

class Solution {
public:
  double findMedianSortedArrays(std::vector<int> &nums1,
                                std::vector<int> &nums2) {
    std::ptrdiff_t n1 = nums1.size(), n2 = nums2.size();

    if (n1 > n2)
      return findMedianSortedArrays(nums2, nums1);

    std::ptrdiff_t n = n1 + n2;
    std::ptrdiff_t left = (n1 + n2 + 1) >> 1;
    std::ptrdiff_t low = 0Z, high = n1;

    while (low <= high) {
      std::ptrdiff_t mid1 = (low + high) >> 1;
      std::ptrdiff_t mid2 = left - mid1;

      int l1 = INT_MIN, l2 = INT_MIN, r1 = INT_MAX, r2 = INT_MAX;

      if (mid1 < n1)
        r1 = nums1[mid1];
      if (mid2 < n2)
        r2 = nums2[mid2];
      if (mid1 - 1 >= 0)
        l1 = nums1[mid1 - 1];
      if (mid2 - 1 >= 0)
        l2 = nums2[mid2 - 1];

      if (l1 <= r2 && l2 <= r1) [[unlikely]] {
        if (n & 1)
          return std::max(l1, l2);
        else
          return (std::max(l1, l2) + std::min(r1, r2)) / 2.0;
      } else if (l1 > r2)
        high = mid1 - 1;
      else
        low = mid1 + 1;
    }

    return 0;
  }
};
