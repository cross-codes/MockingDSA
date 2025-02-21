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

namespace _450A {

auto run() -> void {
  int n, m;
  std::cin >> n >> m;

  std::deque<std::pair<int, int>> queue{};

  for (int i = 1; i <= n; i++) {
    int num;
    std::cin >> num;
    queue.push_back({i, num});
  }

  while (queue.size() != 1) {
    auto pair = queue.front();
    queue.pop_front();
    if (pair.second > m) {
      pair.second -= m;
      queue.push_back(pair);
    }
  }

  std::println("{}", queue.front().first);
}

} // namespace _450A

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

  while (t-- > 0)
    _450A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
