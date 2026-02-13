#include <vector>

#include "./SegmentTree.hh"

class DifferenceArray {
 public:
  static std::vector<int64_t> compute_diff(const std::vector<int64_t>& array) {
    std::vector<int64_t> diff(array.size() + 1);
    diff[0] = array[0];
    for (size_t i = 1; i < array.size(); i++) {
      diff[i] = array[i] - array[i - 1];
    }
    return diff;
  }

  DifferenceArray(const std::vector<int64_t>& array)
      : m_diff(compute_diff(array)),
        m_tree(m_diff, INT64_C(0), std::plus<int64_t>()) {}

  void increase_in_range(std::size_t a, std::size_t b, int x) {
    m_tree.set_at_index(a, m_diff[a] + x);
    m_diff[a] += x;

    m_tree.set_at_index(b, m_diff[b] - x);
    m_diff[b] -= x;
  }

  auto get_underlying_value(std::size_t index) -> int64_t {
    return m_tree.range_query(0, index + 1);
  }

 private:
  std::vector<int64_t> m_diff;
  SegmentTree<int64_t, decltype(std::plus<int64_t>())> m_tree;
};
