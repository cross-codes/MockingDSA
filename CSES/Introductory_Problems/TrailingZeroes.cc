#include <cmath>
#include <cstdint>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

inline i64 exponentOfPInFactorial(const double &n, const int &p) {
  i64 ans = 0LL;
  i64 toAdd = static_cast<i64>(std::floor(n / p));

  int cnt = 1;
  while (toAdd != 0LL) {
    ans += toAdd;
    cnt++;
    toAdd = static_cast<i64>((std::floor(n / std::pow(p, cnt))));
  }

  return ans;
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  double n;
  std::cin >> n;

  i64 powerOf2 = ::exponentOfPInFactorial(n, 2);
  i64 powerOf5 = ::exponentOfPInFactorial(n, 5);

  std::cout << std::min(powerOf2, powerOf5) << "\n";

  return 0;
}
