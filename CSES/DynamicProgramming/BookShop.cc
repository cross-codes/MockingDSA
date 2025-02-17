#include <algorithm>
#include <climits>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  ssize n, sum;
  std::cin >> n >> sum;

  std::unique_ptr<int[]> prices(new int[n + 1]), pages(new int[n + 1]),
      maxPages(new int[sum + 1]);

  for (ssize i = 1; i <= n; i++)
    std::cin >> prices[i];

  for (ssize i = 1; i <= n; i++)
    std::cin >> pages[i];

  std::memset(maxPages.get(), -1, sizeof(int) * (sum + 1));
  maxPages[0] = 0;

  int res = INT_MIN;
  for (ssize k = 1; k <= n; k++) {
    for (ssize x = sum; x >= 0; x--) {

      if (maxPages[x] != -1 && x + prices[k] <= sum) {
        maxPages[x + prices[k]] =
            std::max(pages[k] + maxPages[x], maxPages[x + prices[k]]);
        res = std::max(maxPages[x + prices[k]], res);
      }

      res = std::max(maxPages[x], res);
    }
  }

  std::cout << res << "\n";

  return 0;
}
