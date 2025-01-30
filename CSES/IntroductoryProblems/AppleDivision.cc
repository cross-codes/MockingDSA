#include <climits>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  std::vector<i64> apples(n);
  for (int i = 0; i < n; i++)
    std::cin >> apples[i];

  i64 minDiff = INT64_MAX;
  for (int i = 1; i < (1 << n); i++) {
    i64 sumGroup1 = 0LL, sumGroup2 = 0LL;
    for (int j = 0; j < n; j++) {
      if ((i & (1 << j)) != 0)
        sumGroup1 += apples[j];
      else
        sumGroup2 += apples[j];
    }
    minDiff = std::min(minDiff, std::abs(sumGroup1 - sumGroup2));
  }

  std::cout << minDiff << "\n";

  return 0;
}
