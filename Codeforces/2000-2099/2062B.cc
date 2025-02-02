#include <cstdint>
#include <iostream>
#include <print>
#include <sys/types.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;

  while (t-- > 0) {
    int n;
    std::cin >> n;

    bool bad = false;
    for (int i = 0; i < n; i++) {
      int num;
      std::cin >> num;
      if (num <= std::max(i, n - i - 1) << 1)
        bad = true;
    }

    std::println("{0}", (bad) ? "NO" : "YES");
  }

  return 0;
}
