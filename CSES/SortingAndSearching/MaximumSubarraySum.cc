#include <climits>
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

  i64 currentSum = 0LL, bestSum = LLONG_MIN;
  for (int i = 0; i < n; i++) {
    i64 num;
    std::cin >> num;
    currentSum = std::max(currentSum + num, num);
    bestSum = std::max(bestSum, currentSum);
  }

  std::cout << bestSum << "\n";

  return 0;
}
