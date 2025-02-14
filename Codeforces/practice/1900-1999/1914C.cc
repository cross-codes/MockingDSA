#include <bits/stdc++.h>

#ifdef CROSS
#include "extras/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _1914C {

auto run() -> void {
  ssize n, k;
  std::cin >> n >> k;

  std::unique_ptr<u32[]> firstClear(new u32[n]), reClear(new u32[n]);
  std::unique_ptr<u64[]> firstPrefix(new u64[n + 1]);
  std::unique_ptr<u32[]> maxReClear(new u32[n]);

  firstPrefix[0] = 0;
  for (ssize i = 0; i < n; i++) {
    std::cin >> firstClear[i];
    firstPrefix[i + 1] = firstClear[i] + firstPrefix[i];
  }

  std::cin >> reClear[0];
  maxReClear[0] = reClear[0];
  for (ssize i = 1; i < n; i++) {
    std::cin >> reClear[i];
    maxReClear[i] = std::max(reClear[i], maxReClear[i - 1]);
  }

  u64 maxScore = 0ULL;
  for (ssize idx = 0; idx < n && idx < k; idx++) {
    ssize remaining = k - 1 - idx;
    maxScore =
        std::max(maxScore, firstPrefix[idx + 1] + remaining * maxReClear[idx]);
  }

  if (n < k)
    maxScore = std::max(maxScore, firstPrefix[n] + (k - n) * maxReClear[n - 1]);

  std::println("{}", maxScore);
}

} // namespace _1914C

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
    _1914C::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
