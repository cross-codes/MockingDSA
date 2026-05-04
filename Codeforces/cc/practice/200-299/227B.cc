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

namespace _227B {

auto run() -> void {
  usize n;
  std::cin >> n;

  std::array<usize, 100001> positions{};

  for (usize i = 1UZ; i <= n; i++) {
    int num;
    std::cin >> num;
    positions[num] = i;
  }

  ssize m;
  std::cin >> m;

  u64 fwd{}, back{};
  while (m-- > 0) {
    usize b;
    std::cin >> b;
    fwd += positions[b];
    back += n - positions[b] + 1;
  }

  std::println("{} {}", fwd, back);
}

} // namespace _227B

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
    _227B::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
