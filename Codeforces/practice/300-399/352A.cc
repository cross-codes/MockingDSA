#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _352A {

auto run() -> void {
  usize n;
  std::cin >> n;

  u32 fives{}, zeroes{};
  for (usize i = 0UZ; i < n; i++) {
    int x;
    std::cin >> x;
    if (x == 5)
      fives++;
    else
      zeroes++;
  }

  if (zeroes == 0) {
    std::println("{}", -1);
    return;
  }

  u32 quotient = fives / 9;
  if (quotient == 0U) {
    std::println("{}", 0);
    return;
  }

  for (usize i = 0UZ; i < quotient; i++)
    for (int j = 0; j < 9; j++) std::print("{}", 5);

  for (usize i = 0UZ; i < zeroes; i++) std::print("{}", 0);

  std::println();
}

}  // namespace _352A

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

  while (t-- > 0) _352A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
