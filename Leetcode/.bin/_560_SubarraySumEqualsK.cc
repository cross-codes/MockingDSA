#include <memory>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  int subarraySum(std::vector<int> &nums, int k) {
    std::size_t n{nums.size()};
    std::unique_ptr<int[]> prefixSum(new int[n + 1]);

    prefixSum[0] = 0;
    for (std::size_t i = 1UZ; i <= n; i++)
      prefixSum[i] = nums[i - 1] + prefixSum[i - 1];

    int numSubArrays{};
    std::unordered_map<int, size_t> numToIndex{};
    numToIndex.reserve(n + 1);

    for (std::size_t i = 0UZ; i <= n; i++) {
      auto it = numToIndex.find(prefixSum[i] - k);
      if (it != numToIndex.end()) numSubArrays += it->second;

      numToIndex[prefixSum[i]]++;
    }

    return numSubArrays;
  }
};
