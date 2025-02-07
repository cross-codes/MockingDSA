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
  ssize n, k;
  std::cin >> n >> k;

  std::unique_ptr<int[]> seq(new int[n]);

  for (int i = 0; i < n; i++)
    std::cin >> seq[i];

  bool match = false;
  ssize maxWindow = n - k + 1;

  if (maxWindow == 1) {
    int curNumberInSequence = 1;

    for (ssize i = 1; i < n; i += 2) {
      if (curNumberInSequence != seq[i]) {
        std::println("{}", (i + 1) >> 1);
        match = true;
        break;
      } else
        curNumberInSequence++;
    }

    if (!match)
      std::println("{}", curNumberInSequence);

  } else {

    for (ssize i = 1; i < n; i++) {
      if (seq[i] != 1) {
        ssize curWindow = i;
        if (curWindow <= maxWindow) {
          std::println("{}", 1);
          match = true;
          break;
        } else {
          std::println("{}", 2);
          match = true;
          break;
        }
      }
    }

    if (!match) {
      std::println("{}", 2);
    }
  }
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
