#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <cstdint>
#include <iostream>
#include <unordered_map>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    int a1, a2, a4, a5;
    std::cin >> a1 >> a2 >> a4 >> a5;

    std::unordered_map<int, int> freq{};

    freq[a1 + a2]++;
    freq[a4 - a2]++;
    freq[a5 - a4]++;

    int max = 0;
    for (auto [x, y] : freq)
      max = std::max(max, y);

    std::cout << max << "\n";
  }

  return 0;
}
