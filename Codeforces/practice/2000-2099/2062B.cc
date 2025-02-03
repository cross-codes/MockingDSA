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

auto run() -> void {
  int n;
  std::cin >> n;

  bool bad = false;
  for (int i = 0; i < n; i++) {
    int num;
    std::cin >> num;
    if (num <= std::max(i, n - i - 1) << 1)
      bad = true;
  }

  std::println("{}", (bad) ? "NO" : "YES");
}

int main() {
#ifdef CROSS
  FILE *c = std::freopen("input.txt", "r", stdin);
  if (c == nullptr) {
    std::println(stderr, "{}", "Input file not found");
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
