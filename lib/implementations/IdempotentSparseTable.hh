#include <functional>
#include <memory>

#include "util/Algebra.hh"

template <typename T> struct IdempotentSparseTable
{
  /*
   * Author: github.com/cross-codes
   */

private:
  std::function<T(const T &, const T &)> function_;
  std::vector<std::vector<T>> table;

public:
  IdempotentSparseTable(std::function<T(const T &, const T &)> func,
                        std::unique_ptr<T[]> &array, std::size_t n)
      : function_(func)
  {
    std::size_t K = Algebra::log2(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(&array[0], &array[n], table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++)
    {
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++)
      {
        table[y][x] = function_(table[y - 1][x], table[y - 1][k]);
      }
    }
  }

  T queryRange(std::size_t fromIdx, std::size_t pastEndIdx)
  {
    std::size_t log2 = Algebra::log2(pastEndIdx - fromIdx);
    return function_(table[log2][fromIdx],
                     table[log2][pastEndIdx - (1 << log2)]);
  }
};
