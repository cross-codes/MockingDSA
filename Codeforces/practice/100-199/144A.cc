#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _144A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::pair<int, int> minMax = {INT_MAX, INT_MIN};
  std::pair<usize, usize> minMaxIdx{};
  for (ssize i = 0Z; i < n; i++) {
    int num;
    std::cin >> num;
    if (num > minMax.second) {
      minMax.second = num;
      minMaxIdx.second = i + 1UZ;
    }

    if (num <= minMax.first) {
      minMax.first = num;
      minMaxIdx.first = i + 1UZ;
    }
  }

  ssize swaps = 0Z;
  if (minMaxIdx.first < minMaxIdx.second)
    swaps = n - minMaxIdx.first + minMaxIdx.second - 2Z;
  else
    swaps = n - minMaxIdx.first + minMaxIdx.second - 1Z;

  std::println("{}", swaps);
}

} // namespace _144A

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
    _144A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
