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

auto constexpr VECTOR_ORDER =
    [](const std::pair<std::vector<i64>, std::vector<__int128>> &a,
       const std::pair<std::vector<i64>, std::vector<__int128>> &b) -> bool {
  const auto &sumsA = a.second;
  const auto &sumsB = b.second;

  for (usize i = 0; i < sumsA.size(); i++) {
    __int128 cmp = sumsA[i] - sumsB[i];
    if (cmp != 0)
      return cmp > 0;
  }

  return false;
};

auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::vector<std::pair<std::vector<i64>, std::vector<__int128>>> arrays(
      n, std::make_pair(std::vector<i64>(m), std::vector<__int128>(m)));

  for (ssize i = 0; i < n; i++) {
    __int128 specSum = 0, cnt = m + 1;
    for (ssize j = 0; j < m; j++) {
      int num;
      std::cin >> num;
      specSum += cnt * num;
      (arrays[i].first)[j] = num;
      cnt--;
    }

    auto &ref = arrays[i].first;
    auto &array = arrays[i].second;

    __int128 curSum = specSum;
    cnt = m + 1;
    for (ssize j = 0; j < m; j++) {
      array[j] = curSum;
      curSum -= (cnt)*ref[j];
      cnt--;
    }
  }

  std::sort(arrays.begin(), arrays.end(), ::VECTOR_ORDER);

  u128 totSum = 0, cnt = n * m;
  for (ssize i = 0; i < n; i++) {
    for (ssize j = 0; j < m; j++) {
      totSum += (arrays[i].first)[j] * cnt;
      cnt--;
    }
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
