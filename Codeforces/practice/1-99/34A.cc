#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _34A {

auto run() -> void {
  usize n;
  std::cin >> n;

  int first, last, prev, minDiff = INT_MAX;
  std::cin >> first;
  prev = first;

  std::pair<int, int> minCouple;

  for (usize i = 1UZ; i < n - 1; i++) {
    int current;
    std::cin >> current;

    int diff = std::abs(current - prev);
    if (diff < minDiff) {
      minDiff   = diff;
      minCouple = {i + 1, i};
    }

    prev = current;
  }

  std::cin >> last;

  int diff = std::abs(last - prev);
  if (diff < minDiff) {
    minCouple = {n, n - 1};
    minDiff   = diff;
  }
  if (std::abs(last - first) < minDiff) minCouple = {1, n};

  std::println("{} {}", minCouple.first, minCouple.second);
}

}  // namespace _34A

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

  while (t-- > 0) _34A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
