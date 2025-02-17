#include <cstdint>
#include <iostream>
#include <set>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;
  std::multiset<u32> bag{};

  for (std::size_t i = 0; i < n; i++) {
    u32 tower;
    std::cin >> tower;

    auto it = bag.upper_bound(tower);
    if (it != bag.end())
      bag.erase(it);

    bag.insert(tower);
  }

  std::cout << bag.size() << "\n";

  return 0;
}
