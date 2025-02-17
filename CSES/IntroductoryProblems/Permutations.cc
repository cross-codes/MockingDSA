#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  if (n == 1) [[unlikely]]
    std::cout << "1";
  else if (n < 4) [[unlikely]]
    std::cout << "NO SOLUTION";
  else if (n & 1) {
    for (int i = 1; i <= n; i += 2)
      std::cout << i << " ";
    for (int i = 2; i <= n - 1; i += 2)
      std::cout << i << " ";
  } else {
    for (int i = 2; i <= n; i += 2)
      std::cout << i << " ";
    for (int i = 1; i <= n - 1; i += 2)
      std::cout << i << " ";
  }
  std::cout << "\n";

  return 0;
}
