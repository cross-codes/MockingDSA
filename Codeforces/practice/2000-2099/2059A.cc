#include <bits/stdc++.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _2059A {

auto run() -> void {
  usize n;
  std::cin >> n;

  std::unordered_set<int> a, b;

  for (size_t i = 0; i < n; i++) {
    int num;
    std::cin >> num;
    a.insert(num);
  }

  for (size_t i = 0; i < n; i++) {
    int num;
    std::cin >> num;
    b.insert(num);
  }

  if (a.size() >= 3 || b.size() >= 3)
    std::println("{}", "YES");
  else if (a.size() == 2 && b.size() == 2) {
    std::unordered_set<int> sums{};
    int num1 = *a.begin(), num2 = *(++a.begin());
    int num3 = *b.begin(), num4 = *(++b.begin());

    sums.insert(num1 + num3);
    sums.insert(num1 + num4);
    sums.insert(num2 + num3);
    sums.insert(num2 + num4);

    if (sums.size() >= 3)
      std::println("{}", "YES");
    else
      std::println("{}", "NO");
  } else {
    std::println("{}", "NO");
  }
}

} // namespace _2059A

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

  int t;
  std::cin >> t;

  while (t-- > 0)
    _2059A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
