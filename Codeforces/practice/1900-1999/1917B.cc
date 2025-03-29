#include <bits/stdc++.h>

#ifdef ANTUMBRA
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

namespace _1917B {

auto run() -> void {
  usize n;
  std::cin >> n;

  std::unordered_set<char> encountered{};

  u32 cnt = 0U;
  for (usize i = 0; i < n; i++) {
    char c;
    std::cin >> c;
    encountered.insert(c);
    cnt += encountered.size();
  }

  std::println("{}", cnt);
}

} // namespace _1917B

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

  int t;
  std::cin >> t;

  while (t-- > 0)
    _1917B ::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
