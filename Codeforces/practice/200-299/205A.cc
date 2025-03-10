#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _205A {

auto run() -> void {
  usize n;
  std::cin >> n;

  ssize minDis   = LONG_MAX, minIndex;
  bool seenTwice = false;
  for (usize i = 0UZ; i < n; i++) {
    ssize dis;
    std::cin >> dis;

    if (minDis >= dis) {
      if (minDis == dis) {
        seenTwice = true;
      } else {
        minDis    = dis;
        seenTwice = false;
        minIndex  = i + 1;
      }
    }
  }

  if (seenTwice)
    std::println("Still Rozdil");
  else
    std::println("{}", minIndex);
}

}  // namespace _205A

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

  while (t-- > 0) _205A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
