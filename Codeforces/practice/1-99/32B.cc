#include <bits/stdc++.h>

#ifdef CROSS
#include "extras/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = std::size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _32B {

auto run() -> void {
  std::string input;
  std::cin >> input;

  std::string output;
  for (usize i = 0; i < input.size(); i++) {
    if (input[i] == '.') {
      output.push_back('0');
    } else if (input[i] == '-' && i <= input.size() - 1) {
      if (input[i + 1] == '.') {
        output.push_back('1');
        i++;
      } else if (input[i + 1] == '-') {
        output.push_back('2');
        i++;
      }
    }
  }

  std::println("{}", output);
}

} // namespace _32B

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

  int t = 1;

  while (t-- > 0)
    _32B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
