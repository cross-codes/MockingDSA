#include <bits/stdc++.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

inline auto constexpr VECTOR_ORDER =
    [](const std::pair<std::vector<i64>, i64> &a,
       const std::pair<std::vector<i64>, i64> &b) -> bool {
  return a.second > b.second;
};

auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::vector<std::pair<std::vector<i64>, i64>> arrays(
      n, std::make_pair(std::vector<i64>(m), 0LL));

  for (ssize i = 0; i < n; i++) {
    i64 &totSum = arrays[i].second;
    auto &vec = arrays[i].first;

    for (ssize j = 0; j < m; j++) {
      std::cin >> vec[j];
      totSum += vec[j];
    }
  }

  std::sort(arrays.begin(), arrays.end(), ::VECTOR_ORDER);

  u64 totSum = 0ULL, cnt = n * m;
  for (ssize i = 0; i < n; i++) {
    auto &vec = arrays[i].first;
    for (ssize j = 0; j < m; j++)
      totSum += vec[j] * cnt--;
  }

  std::println("{}", totSum);
}

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t;
  std::cin >> t;

  while (t-- > 0)
    run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
