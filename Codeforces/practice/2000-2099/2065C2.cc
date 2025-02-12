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

namespace _2065C2 {

auto run() -> void {
  ssize n, m;
  std::cin >> n >> m;

  std::unique_ptr<int[]> a(new int[n]), b(new int[m]);

  for (ssize i = 0; i < n; i++)
    std::cin >> a[i];

  for (ssize i = 0; i < m; i++)
    std::cin >> b[i];

  std::sort(&b[0], &b[m]);

  if (b[0] - a[0] < a[0])
    a[0] = b[0] - a[0];

  for (ssize i = 1; i < n - 1; i++) {
    auto it = std::lower_bound(&b[0], &b[m], a[i] + a[i - 1]);
    if (it == &b[m]) [[unlikely]]
      continue;

    if (a[i] >= a[i - 1]) {
      if (*it - a[i] < a[i])
        a[i] = *it - a[i];
    } else {
      a[i] = *it - a[i];
    }
  }

  if (b[m - 1] - a[n - 1] > a[n - 1])
    a[n - 1] = b[m - 1] - a[n - 1];

  for (ssize i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      std::println("NO");
      return;
    }
  }

  std::println("YES");
}

} // namespace _2065C2

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
    _2065C2::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
