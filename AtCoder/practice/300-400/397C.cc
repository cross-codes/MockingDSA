#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _C
{

struct FenwickTree
{
  /*
   * Author: github.com/cross-codes
   */

private:
  std::size_t N_;
  std::unique_ptr<std::int64_t[]> tree_;

public:
  std::unique_ptr<std::int64_t[]> array;

  explicit FenwickTree(std::size_t n)
      : N_(n), tree_(std::make_unique<std::int64_t[]>(n + 1)),
        array(std::make_unique<std::int64_t[]>(n + 1))
  {
  }

  void advanceValue(std::size_t k, std::int64_t x)
  {
    while (k <= N_)
    {
      tree_[k] += x;
      k += k & -k;
    }
  }

  std::int64_t prefixSumAt(std::size_t k)
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

auto run() -> void
{
  usize N;
  std::cin >> N;

  std::unique_ptr<int[]> A(new int[N]);
  std::unique_ptr<std::pair<int, int>[]> distinct(new std::pair<int, int>[N]);

  std::unordered_set<int> distinctElements{};

  for (usize i = 0; i < N; i++)
  {
    std::cin >> A[i];
    distinct[i].first = static_cast<int>(distinctElements.size());
    distinctElements.insert(A[i]);
  }

  FenwickTree fenwickTree(N);
  std::unordered_map<int, ssize> firstOcc{};
  firstOcc.reserve(N);

  for (ssize i = N - 1; i >= 0; i--)
  {
    int num = A[i];
    if (firstOcc.contains(num))
      fenwickTree.advanceValue(firstOcc[num], -1);

    firstOcc[num] = i + 1;
    fenwickTree.advanceValue(i + 1, 1);
    distinct[i].second = static_cast<int>(fenwickTree.prefixSumAt(N));
  }

  int maxSum{INT_MIN};
  for (usize i = 0; i < N; i++)
    maxSum = std::max(maxSum, distinct[i].first + distinct[i].second);

  std::cout << maxSum << "\n";
}

} // namespace _C

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0)
    _C::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
