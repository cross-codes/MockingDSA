#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _224A {

auto run() -> void {
  i64 ab, bc, ca;
  std::cin >> ab >> bc >> ca;

  i64 abc = static_cast<int>(std::sqrt(ab * bc * ca));
  i64 a = abc / bc, b = abc / ca, c = abc / ab;

  std::println("{}", (a + b + c) << 2);
}

}  // namespace _224A

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

  while (t-- > 0) _224A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
