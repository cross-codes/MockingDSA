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
  std::unordered_set<std::vector<int>, VectorHash, IsEqualToVector> res;
  int target;

  void search(int sum, const std::vector<int> &nums, std::vector<int> cur,
              std::size_t idx, ...) {
    if (sum == target) {
      res.insert(cur);
      return;
    }

    if (sum > target || idx == nums.size())
      return;

    cur.push_back(nums[idx]);
    search(sum + nums[idx], nums, cur, idx + 1);
    cur.pop_back();
    search(sum, nums, cur, idx + 1);
  }

  std::vector<std::vector<int>> combinationSum2(std::vector<int> &candidates,
                                                int target) {
    this->target = target;
    search(0, candidates, {}, 0);

    return std::vector<std::vector<int>>(res.begin(), res.end());
  }
};
