#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _233A {

auto run() -> void {
  int n;
  std::cin >> n;

  if (n & 1)
    std::println("-1");
  else {
    for (int i = 1; i <= n; i += 2)
      std::print("{} {} ", i + 1, i);
    std::println();
  }
}

} // namespace _233A

int main() {
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t = 1;

  while (t-- > 0)
    _233A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
