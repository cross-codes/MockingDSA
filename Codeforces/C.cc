#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "{}", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _C {

auto run() -> void {
  ssize n;
  std::cin >> n;

  i64 x;
  std::cin >> x;

  ssize count = 0Z;
  i64 curNum{0LL};
  i64 final{0LL};
  i64 latestSeenNumber = 0LL;
  bool noPoint = false;
  for (; count < n - 1; count++) {
    if (x < curNum)
      break;

    while ((curNum & ~x) != 0) {
      if (curNum > latestSeenNumber + 1) {
        noPoint = true;
        break;
      }

      if (x < curNum)
        break;
      curNum++;
    }

    if (noPoint) {
      std::print("{} ", x);
    } else {
      std::print("{} ", curNum);
      final |= curNum;
      latestSeenNumber = curNum;
      curNum++;
    }
  }

  if (noPoint) {
    while (count != n) {
      std::print("{} ", x);
      count++;
    }
  } else {
    if (count == n - 1) {
      if ((final | curNum) == x)
        std::print("{} ", curNum);
      else
        std::print("{} ", x);
    } else {
      while (count != n) {
        std::print("{} ", x);
        count++;
      }
    }
  }

  std::println("");
}

} // namespace _C

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

  while (t-- > 0)
    _C::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
