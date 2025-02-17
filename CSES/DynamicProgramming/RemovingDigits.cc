#include <climits>
#include <cstdint>
#include <iostream>
#include <string>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  u32 n;
  std::cin >> n;

  u32 steps = 0U;
  while (n != 0) {
    std::string equiv = std::to_string(n);

    char max = CHAR_MIN;
    for (char c : equiv)
      max = std::max(max, c);

    n -= max - '0', steps++;
  }

  std::cout << steps << "\n";

  return 0;
}
