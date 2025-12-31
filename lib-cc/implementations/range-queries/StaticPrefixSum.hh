#include <vector>

class StaticPrefixSum {
 private:
  std::vector<int64_t> prefix_;

 public:
  StaticPrefixSum(const std::vector<int>& array) {
    prefix_ = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix_[i] = prefix_[i - 1] + array[i - 1];
    }
  }

  StaticPrefixSum(const std::vector<int64_t>& array) {
    prefix_ = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      prefix_[i] = prefix_[i - 1] + array[i - 1];
    }
  }

  auto range_sum(int a, int b) -> int64_t { return prefix_[b] - prefix_[a]; }
};
