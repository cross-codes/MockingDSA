#include <vector>

class StaticPrefixSum {
 public:
  StaticPrefixSum(const std::vector<int>& array) {
    m_prefix = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      m_prefix[i] = m_prefix[i - 1] + array[i - 1];
    }
  }

  StaticPrefixSum(const std::vector<int64_t>& array) {
    m_prefix = std::vector<int64_t>(array.size() + 1);
    for (size_t i = 1; i <= array.size(); i++) {
      m_prefix[i] = m_prefix[i - 1] + array[i - 1];
    }
  }

  auto range_sum(int a, int b) -> int64_t { return m_prefix[b] - m_prefix[a]; }

 private:
  std::vector<int64_t> m_prefix;
};
