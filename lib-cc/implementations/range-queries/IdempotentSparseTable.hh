#include <bit>
#include <concepts>
#include <vector>

template <typename T, typename Op>
  requires std::invocable<Op, T, T>
struct IdempotentSparseTable {
 public:
  IdempotentSparseTable(Op func, const std::vector<T>& array)
      : m_function(func), m_n(array.size()) {
    std::size_t K = std::bit_width(m_n) - 1;

    m_table.resize(K + 1, std::vector<T>(m_n));
    std::copy(array.begin(), array.end(), m_table[0].begin());

    for (std::size_t y = 1; y < m_table.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= m_n - (1 << y); x++, k++)
        m_table[y][x] = m_function(m_table[y - 1][x], m_table[y - 1][k]);
  }

  [[nodiscard]] auto range_query(std::size_t a, std::size_t b) const -> T {
    std::size_t row = std::bit_width(b - a) - 1;
    return m_function(m_table[row][a], m_table[row][b - (1 << row)]);
  }

 private:
  [[no_unique_address]] Op m_function;
  std::vector<std::vector<T>> m_table;
  std::size_t m_n;
};
