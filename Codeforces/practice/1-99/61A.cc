#include <bits/stdc++.h>

#define dbg(a) std::println(stderr, "{}", a);

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _61A {

auto run() -> void {
  std::string A, B;
  std::cin >> A >> B;

  ssize n = A.size();

  std::string res{};

  for (ssize i = 0Z; i < n; i++)
    res.push_back((A[i] != B[i]) ? '1' : '0');

  std::println("{}", res);
}

} // namespace _61A

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
    _61A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
