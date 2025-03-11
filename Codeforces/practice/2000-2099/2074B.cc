#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _B {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::vector<i64> a;
  for (ssize i = 0Z; i < n; i++) {
    i64 elem;
    std::cin >> elem;
    a.push_back(elem);
  }

  while (a.size() != 1) {
    i64 ai = a[a.size() - 1], aj = a[a.size() - 2];
    a.pop_back(), a.pop_back();
    a.push_back(ai + aj - 1);
  }

  std::println("{}", a.front());
}

}  // namespace _B

int main() {
#ifdef CROSS
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
  std::cin >> t;

  while (t-- > 0) _B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
