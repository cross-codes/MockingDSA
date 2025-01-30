#include <cstdint>
#include <iostream>
#include <set>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

auto constexpr QUERY_PAIR_ORDER = [](std::pair<int, int> a,
                                     std::pair<int, int> b) -> bool {
  int cmp = (a.first - a.second) - (b.first - b.second);
  return (cmp == 0) ? a.first < b.first : cmp < 0;
};

auto constexpr REFERENCE_PAIR_ORDER = [](std::pair<int, int> a,
                                         std::pair<int, int> b) -> bool {
  return a.first < b.first;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int x, n;
  std::cin >> x >> n;

  std::set<std::pair<int, int>, decltype(::QUERY_PAIR_ORDER)> range;
  std::set<std::pair<int, int>, decltype(::REFERENCE_PAIR_ORDER)> ref;

  range.insert({x, 0}), ref.insert({x, 0});

  while (n-- > 0) {
    int newPos;
    std::cin >> newPos;

    auto interval = *(ref.lower_bound({newPos, -1}));
    int end = interval.first, start = interval.second;
    std::pair<int, int> div1 = {end, newPos}, div2 = {newPos, start};

    range.erase(interval), range.insert(div1), range.insert(div2);
    ref.erase(interval), ref.insert(div1), ref.insert(div2);

    auto bestPair = *(std::prev(range.end()));
    std::cout << bestPair.first - bestPair.second << " ";
  }

  return 0;
}
