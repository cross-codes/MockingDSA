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

namespace _2065C1 {

auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::unique_ptr<int[]> a(new int[n]);

  for (ssize i = 0; i < n; i++)
    std::cin >> a[i];

  int b;
  std::cin >> b;

  for (ssize i = 0; i < n - 1; i++) {
    if (i == 0 && b - a[i] <= a[i]) [[unlikely]] {
      a[i] = b - a[i];
      continue;
    }

    if (b - a[i] <= a[i] && i > 0 && (b - a[i] >= a[i - 1]))
      a[i] = b - a[i];
    else if (b - a[i] > a[i] && i > 0 && (a[i] < a[i - 1]))
      a[i] = b - a[i];
  }

  if (b - a[n - 1] > a[n - 1])
    a[n - 1] = b - a[n - 1];

  for (ssize i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      std::println("NO");
      return;
    }
  }

  std::println("YES");
}

} // namespace _2065C1

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
    _2065C1::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
