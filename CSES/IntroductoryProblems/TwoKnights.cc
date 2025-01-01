#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;

  for (u64 i = 1; i <= n; i++) {
    std::cout << (i * i) * (i * i - 1ULL) / 2ULL -
                     4ULL * (i - 1ULL) * (i - 2ULL)
              << "\n";
  }

  return 0;
}
