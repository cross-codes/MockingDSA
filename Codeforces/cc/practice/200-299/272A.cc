#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _272A {

auto run() -> void {
  ssize n;
  std::cin >> n;

  int s{}, k{};
  for (ssize i = 0Z; i < n; i++) {
    int num;
    std::cin >> num;
    s += num;
  }

  for (ssize i = 1Z; i <= 5; i++)
    if ((s + i - 1Z) % (n + 1Z))
      k++;

  std::println("{}", k);
}

} // namespace _272A

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

  while (t-- > 0)
    _272A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
