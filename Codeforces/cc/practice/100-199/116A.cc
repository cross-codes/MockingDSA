#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _116A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  int a, b;
  std::cin >> a >> b;
  int max = b;

  int curr{max};
  for (ssize i = 1Z; i < n; i++) {
    std::cin >> a >> b;
    curr -= a - b;

    max = std::max(max, curr);
  }

  std::println("{}", max);
}

} // namespace _116A

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
    _116A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
