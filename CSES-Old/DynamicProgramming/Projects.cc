#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _Projects {

auto constexpr TUPLE_ORDER = [](const std::tuple<int, int, int> &a,
                                const std::tuple<int, int, int> &b) -> bool {
  return std::get<1>(a) < std::get<1>(b);
};

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::unique_ptr<ssize[]> compatible(new ssize[n + 1]);
  std::unique_ptr<i64[]> maxCost(new i64[n + 1]);
  std::unique_ptr<std::tuple<int, int, int>[]> intervals(
      new std::tuple<int, int, int>[n + 1]);

  for (ssize i = 1; i <= n; i++) {
    int start, end, cost;
    std::cin >> start >> end >> cost;
    intervals[i] = std::make_tuple(start, end, cost);
  }

  std::sort(&intervals[1], &intervals[n + 1], TUPLE_ORDER);

  for (ssize i = 1; i <= n; i++) {
    int start{std::get<0>(intervals[i])};
    auto it{std::lower_bound(&intervals[1], &intervals[n + 1],
                             std::make_tuple(0, start, 0), TUPLE_ORDER)};

    compatible[i] = std::distance(&intervals[1], --it) + 1;
  }

  for (ssize i = 1; i <= n; i++) {
    int cost{std::get<2>(intervals[i])};
    maxCost[i] = std::max(cost + maxCost[compatible[i]], maxCost[i - 1]);
  }

  std::cout << maxCost[n] << "\n";
}

}  // namespace _Projects

int main() {
#ifdef ANTUMBRA
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

  while (t-- > 0) _Projects::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
