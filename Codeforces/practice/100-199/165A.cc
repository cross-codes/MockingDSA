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

namespace _165A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::unique_ptr<std::pair<int, int>[]> xPairs(new std::pair<int, int>[n]);
  std::unique_ptr<std::pair<int, int>[]> yPairs(new std::pair<int, int>[n]);

  for (ssize i = 0Z; i < n; i++) {
    int x, y;
    std::cin >> x >> y;
    xPairs[i] = std::make_pair(x, y);
  }

  auto XPriority = [&](const std::pair<int, int> &a,
                       const std::pair<int, int> &b) {
    return a.first < b.first;
  };

  auto YPriority = [&](const std::pair<int, int> &a,
                       const std::pair<int, int> &b) {
    return a.second < b.second;
  };

  std::sort(&xPairs[0], &xPairs[n], XPriority);
  std::sort(&yPairs[0], &yPairs[n], YPriority);
}

} // namespace _165A

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
    _165A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
