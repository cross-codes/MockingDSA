#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "{}", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _DynamicRangeSumQueries {

struct FenwickTree {

  /*
   * Author: github.com/cross-codes
   */

private:
  std::size_t N_;
  std::unique_ptr<std::int64_t[]> tree_;

public:
  std::unique_ptr<std::int64_t[]> array;

  FenwickTree(std::size_t n)
      : N_(n), tree_(std::make_unique<std::int64_t[]>(n + 1)),
        array(std::make_unique<std::int64_t[]>(n + 1)) {};

  void advance(std::size_t k, std::int64_t x) {
    while (k <= N_) {
      tree_[k] += x;
      k += k & -k;
    }
  }

  std::int64_t prefixSumAt(std::size_t k) {
    std::int64_t s = 0LL;
    while (k >= 1) {
      s += tree_[k];
      k -= k & -k;
    }
    return s;
  }
};

auto run() -> void {
  std::size_t n, q;
  std::cin >> n >> q;

  FenwickTree bit(n);

  for (std::size_t i = 1; i <= n; i++) {
    i64 num;
    std::cin >> num;
    bit.advance(i, num);
    bit.array[i] = num;
  }

  while (q-- > 0) {
    u32 choice;
    std::cin >> choice;
    if (choice == 1) {
      std::size_t k;
      i64 u;
      std::cin >> k >> u;
      bit.advance(k, u - bit.array[k]);
      bit.array[k] = u;
    } else {
      std::size_t a, b;
      std::cin >> a >> b;
      std::cout << (bit.prefixSumAt(b) - bit.prefixSumAt(a - 1)) << "\n";
    }
  }
}

} // namespace _DynamicRangeSumQueries

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
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
    _DynamicRangeSumQueries::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
