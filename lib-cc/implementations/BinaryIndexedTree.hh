#include <cstddef>
#include <memory>

struct BinaryIndexedTree
{

private:
  std::size_t N_;
  std::unique_ptr<std::int64_t[]> tree_;

public:
  std::unique_ptr<std::int64_t[]> array;

  BinaryIndexedTree(std::size_t n)
      : N_(n), tree_(std::make_unique<std::int64_t[]>(n + 1)),
        array(std::make_unique<std::int64_t[]>(n + 1)) {};

  void advance(std::size_t k, std::int64_t x)
  {
    while (k <= N_)
    {
      tree_[k] += x;
      k += k & -k;
    }
  }

  std::int64_t prefix_sum_at(std::size_t k)
  {
    std::int64_t s = 0LL;
    while (k >= 1)
    {
      s += tree_[k];
      k -= k & -k;
    }
    return s;
  }
};
