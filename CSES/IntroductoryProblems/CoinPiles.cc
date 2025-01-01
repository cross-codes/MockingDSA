#include <iostream>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t;
  std::cin >> t;
  while (t-- > 0) {
    i64 a, b;
    std::cin >> a >> b;
    if ((2LL * b - a) >= 0LL && ((2LL * b - a) % 3LL == 0LL) &&
        (2LL * a - b) >= 0LL && ((2LL * a - b) % 3LL == 0LL))
      std::cout << "YES\n";
    else
      std::cout << "NO\n";
  }

  return 0;
}
