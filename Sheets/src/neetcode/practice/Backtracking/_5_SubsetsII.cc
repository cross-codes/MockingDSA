#include <algorithm>
#include <unordered_set>
#include <vector>

struct VectorHash {
  std::size_t operator()(const std::vector<int> &vec) const {
    std::size_t hash = 0U;

    auto copy = vec;
    std::sort(copy.begin(), copy.end());

    for (int num : copy)
      hash ^= std::hash<int>()(num) + 0x9e3779b9 + (hash << 6) + (hash >> 2);

    return hash;
  }
};

struct IsEqualToVector {
  bool operator()(const std::vector<int> &lhs,
                  const std::vector<int> &rhs) const {
    auto lhsCopy = lhs, rhsCopy = rhs;

    std::sort(lhsCopy.begin(), lhsCopy.end());
    std::sort(rhsCopy.begin(), rhsCopy.end());

    return lhsCopy == rhsCopy;
  }
};

class Solution {
public:
  std::unordered_set<std::vector<int>, VectorHash, IsEqualToVector> res{};

  void search(std::size_t idx, const std::vector<int> &nums, std::vector<int> cur,
              ...) {
    if (idx == nums.size()) {
      res.insert(cur);
      return;
    }

    cur.push_back(nums[idx]);
    search(idx + 1, nums, cur);
    cur.pop_back();
    search(idx + 1, nums, cur);
  }

  std::vector<std::vector<int>> subsetsWithDup(std::vector<int> &nums) {
    search(0, nums, {});
    return std::vector<std::vector<int>>(res.begin(), res.end());
  }
};
