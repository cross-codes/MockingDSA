#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _200B {

auto run() -> void {
  int n;
  std::cin >> n;

  double sum = 0.00;

  for (int i = 0; i < n; i++) {
    double num;
    std::cin >> num;
    sum += num / 100;
  }

  std::println("{}", sum / n * 100);
}

} // namespace _200B

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
    _200B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
