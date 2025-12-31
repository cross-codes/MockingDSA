#include <bit>
#include <concepts>
#include <vector>

template <typename T, typename Op>
requires std::invocable<Op, T, T>
struct IdempotentSparseTable {
 private:
  [[no_unique_address]] Op function_;
  std::vector<std::vector<T>> table_;
  std::size_t n_;

 public:
  IdempotentSparseTable(Op func, const std::vector<T>& array)
      : function_(func), n_(array.size()) {
    std::size_t K = std::bit_width(n_) - 1;

    table_.resize(K + 1, std::vector<T>(n_));
    std::copy(array.begin(), array.end(), table_[0].begin());

    for (std::size_t y = 1; y < table_.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n_ - (1 << y); x++, k++)
        table_[y][x] = function_(table_[y - 1][x], table_[y - 1][k]);
  }

  [[nodiscard]] auto range_query(std::size_t a, std::size_t b) const -> T {
    std::size_t row = std::bit_width(b - a) - 1;
    return function_(table_[row][a], table_[row][b - (1 << row)]);
  }
};
