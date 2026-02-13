#include <bit>
#include <concepts>
#include <vector>

template <typename T, typename Op>
  requires std::invocable<Op, T, T>
class SegmentTree {
 public:
  SegmentTree(std::vector<T> array, T default_value, Op function)
      : m_n(array.size()),
        m_function(function),
        m_default_value(default_value) {
    m_offset = std::size_t(1) << std::bit_width(m_n - 1);
    m_tree.assign(m_offset << 1, m_default_value);
    std::copy(array.begin(), array.end(), m_tree.begin() + m_offset);

    std::size_t i = m_offset;
    while (i != 1) {
      std::size_t j = i;
      while (j < i << 1) {
        m_tree[j >> 1] = m_function(m_tree[j], m_tree[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  void set_at_index(std::size_t index, T value) {
    index += m_offset;
    m_tree[index] = value;

    while (index != 1) {
      m_tree[index >> 1] = m_function(m_tree[index], m_tree[index ^ 1]);
      index >>= 1;
    }
  }

  [[nodiscard]] auto range_query(std::size_t a, std::size_t b) const -> T {
    a += m_offset, b += m_offset;

    T result{m_default_value};
    while (a < b) {
      if (a & 1)
        result = m_function(result, m_tree[a++]);
      if (b & 1)
        result = m_function(result, m_tree[--b]);

      a >>= 1, b >>= 1;
    }

    return result;
  }

 private:
  std::size_t m_n, m_offset;
  std::vector<T> m_tree;

  [[no_unique_address]] Op m_function;
  T m_default_value;
};
