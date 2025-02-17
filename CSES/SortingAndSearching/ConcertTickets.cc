#include <cstdint>
#include <iostream>
#include <set>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n, m;
  std::cin >> n >> m;

  std::multiset<u64> prices{};

  for (std::size_t i = 0; i < n; i++) {
    u64 price;
    std::cin >> price;
    prices.insert(price);
  }

  for (std::size_t i = 0; i < m; i++) {
    u64 maxPrice;
    std::cin >> maxPrice;

    if (prices.size() == 0)
      std::cout << "-1 ";
    else {
      auto it = prices.upper_bound(maxPrice);
      if (it != prices.begin())
        it--;

      u64 offer = *it;
      if (offer > maxPrice)
        std::cout << "-1 ";
      else {
        std::cout << offer << " ";
        prices.erase(it);
      }
    }
  }

  std::cout << "\n";

  return 0;
}
