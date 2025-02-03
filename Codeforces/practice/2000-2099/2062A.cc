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
  std::string input;
  std::cin >> input;

  int cnt = 0;
  for (char c : input) {
    if (c == '1')
      cnt++;
  }

  std::println("{0}", cnt);
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
