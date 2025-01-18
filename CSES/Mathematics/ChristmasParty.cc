#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 1000000;
constexpr u64 MOD = static_cast<u64>(1e9 + 7);
u64 derangements[_ + 1];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;

  bool even = true;
  for (size_t i = 2; i <= n; i++) {
    if (even)
      derangements[i] = i * derangements[i - 1] + 1;
    else
      derangements[i] = i * derangements[i - 1] - 1;

    derangements[i] %= ::MOD;
    even = !even;
  }

  std::cout << derangements[n] << "\n";

  return 0;
}
