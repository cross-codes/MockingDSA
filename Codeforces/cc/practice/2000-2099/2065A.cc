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

namespace _2065A {

auto run() -> void {
  std::string input;
  std::cin >> input;

  if (input.size() <= 2) {
    std::println("i");
  } else {
    std::println("{}", input.substr(0, input.size() - 2) + "i");
  }
}

} // namespace _2065A

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
    _2065A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
