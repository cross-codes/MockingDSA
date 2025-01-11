#include <algorithm>
#include <cstdint>
#include <iostream>
#include <set>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

const size_t _ = 200000;
u32 desiredSizes[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n, m;
  u32 k;
  std::cin >> n >> m >> k;

  std::multiset<u32> apartments;

  for (size_t i = 0; i < n; i++)
    std::cin >> desiredSizes[i];

  for (size_t i = 0; i < m; i++) {
    u32 num;
    std::cin >> num;
    apartments.insert(num);
  }

  std::sort(&desiredSizes[0], &desiredSizes[n]);

  u32 count = 0U;
  for (size_t i = 0; i < n; i++) {
    u32 target = (desiredSizes[i] > k) ? desiredSizes[i] - k : 0;
    auto it = apartments.lower_bound(target);
    if (it != apartments.end() && *it <= desiredSizes[i] + k) {
      count++;
      apartments.erase(it);
    }
  }

  std::cout << count << "\n";

  return 0;
}
