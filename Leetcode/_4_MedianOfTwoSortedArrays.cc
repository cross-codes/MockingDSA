#include <set>
#include <vector>

class Solution {
public:
  double findMedianSortedArrays(std::vector<int> &nums1,
                                std::vector<int> &nums2) {
    size_t m = nums1.size(), n = nums2.size();
    if (m == 0 && n == 0)
      return 0.0;

    std::multiset<int> bag{};
    std::multiset<int>::iterator medianIt;
    size_t medianIdx;
    bool odd = false, once = false;

    for (int num : nums1) {
      bag.insert(num);

      if (!once) {
        medianIdx = 1;
        medianIt = bag.begin();
        once = true;
        odd = true;
        continue;
      }

      if (num < *medianIt)
        medianIdx++;

      size_t idx = (bag.size() + 1) / 2;

      if (medianIdx < idx)
        ++medianIt;
      if (medianIdx > idx)
        --medianIt;

      medianIdx = idx;
      odd = !odd;
    }

    for (int num : nums2) {
      bag.insert(num);

      if (!once) {
        medianIdx = 1;
        medianIt = bag.begin();
        once = true;
        odd = true;
        continue;
      }

      if (num < *medianIt)
        medianIdx++;

      size_t idx = (bag.size() + 1) / 2;

      if (medianIdx < idx)
        ++medianIt;
      if (medianIdx > idx)
        --medianIt;

      medianIdx = idx;
      odd = !odd;
    }

    if (!odd)
      return (*medianIt + *(++medianIt)) / 2.0;
    else
      return static_cast<double>(*medianIt);
  }
};
