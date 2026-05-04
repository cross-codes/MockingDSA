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

namespace _2064A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::string input;
  std::cin >> input;

  u32 cnt = 0U;
  bool current1 = false;
  for (ssize i = 0; i < n; i++) {
    if (current1) {
      if (input[i] != '1') {
        current1 = false;
        cnt += 2;
      }
    } else {
      if (input[i] == '1') {
        current1 = true;
      }
    }
  }

  if (current1)
    cnt++;

  std::println("{}", cnt);
}

} // namespace _2064A

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
    _2064A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
