#include <bits/stdc++.h>

#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

template <>
struct std::hash<std::pair<i64, i64>> {
  std::size_t operator()(const std::pair<i64, i64> &pair) const noexcept {
    return (std::hash<i64>()(pair.first) >> 1 ^ std::hash<i64>()(pair.second)
                                                    << 1)
           << 2;
  }
};

namespace _D {
auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::unique_ptr<std::pair<i64, i64>[]> circles(new std::pair<i64, i64>[n]);
  for (ssize i = 0Z; i < n; i++) {
    i64 x;
    std::cin >> x;
    circles[i].first = x;
  }

  for (ssize i = 0Z; i < n; i++) {
    i64 r;
    std::cin >> r;
    circles[i].second = r;
  }

  std::unordered_set<std::pair<i64, i64>> points;
  for (ssize i = 0Z; i < n; i++) {
    auto &[center, r] = circles[i];

    for (i64 x = -r; x <= r; x++) {
      i64 xSquare{x * x}, ySquareMax{r * r - xSquare};
      if (ySquareMax >= 0) {
        i64 yMax = static_cast<i64>(std::sqrt(ySquareMax));
        for (i64 y = 0; y <= yMax; y++) {
          points.insert({center + x, y});
          points.insert({center + x, -y});
        }
      } else {
        break;
      }
    }
  }

  std::println("{}", points.size());
}

}  // namespace _D

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
  std::cin >> t;

  while (t-- > 0) _D::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
