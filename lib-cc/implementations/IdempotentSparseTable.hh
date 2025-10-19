#include <functional>
#include <vector>

template <typename T> struct IdempotentSparseTable
{
private:
  std::function<T(const T &, const T &)> function_;
  std::vector<std::vector<T>> table;

public:
  IdempotentSparseTable(std::function<T(const T &, const T &)> func, T array[],
                        std::size_t n)
      : function_(func)
  {
    std::size_t K = std::__lg(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(array, array + n, table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++)
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++)
        table[y][x] = function_(table[y - 1][x], table[y - 1][k]);
  }

  T query_range(std::size_t from_idx, std::size_t past_end_idx)
  {
    std::size_t row = std::__lg(past_end_idx - from_idx);
    return function_(table[row][from_idx], table[row][past_end_idx - (1 << row)]);
  }
};
