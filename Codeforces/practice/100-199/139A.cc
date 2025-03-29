#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _139A {

auto run() -> void {
  int n;
  std::cin >> n;

  std::array<int, 7> pages;
  for (usize i = 0UZ; i < 7UZ; i++) {
    std::cin >> pages[i];
  }

  usize res;
  usize idx = 0UZ;
  while (n > 0) {
    n -= pages[idx];
    res = idx + 1;
    idx = (idx == 6) ? 0 : idx + 1;
  }

  std::println("{}", res);
}

}  // namespace _139A

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

  while (t-- > 0) _139A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
