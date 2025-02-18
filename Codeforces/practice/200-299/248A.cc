#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _248A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  int cntLZ{}, cntRZ{};
  for (ssize i = 0Z; i < n; i++) {
    int a, b;
    std::cin >> a >> b;
    cntLZ += a;
    cntRZ += b;
  }

  int res{};
  if (cntLZ > n / 2Z)
    res += n - cntLZ;
  else
    res += cntLZ;

  if (cntRZ > n / 2Z)
    res += n - cntRZ;
  else
    res += cntRZ;

  std::println("{}", res);
}

} // namespace _248A

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
    _248A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
