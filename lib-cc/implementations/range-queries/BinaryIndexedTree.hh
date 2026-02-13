#include <cstddef>
#include <memory>

struct BinaryIndexedTree {
 public:
  std::unique_ptr<std::int64_t[]> array;

  BinaryIndexedTree(std::size_t n)
      : array(std::make_unique<std::int64_t[]>(n + 1)),
        m_N(n),
        m_tree(std::make_unique<std::int64_t[]>(n + 1)) {};

  void advance(std::size_t k, std::int64_t x) {
    while (k <= m_N) {
      m_tree[k] += x;
      k += k & -k;
    }
  }

  std::int64_t prefix_sum_at(std::size_t k) {
    std::int64_t s = 0LL;
    while (k >= 1) {
      s += m_tree[k];
      k -= k & -k;
    }
    return s;
  }

 private:
  std::size_t m_N;
  std::unique_ptr<std::int64_t[]> m_tree;
};
