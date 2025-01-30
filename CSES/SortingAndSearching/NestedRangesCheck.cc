#include <climits>
#include <cstdint>
#include <iostream>
#include <map>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200000;
std::pair<int, int> intervals[_];

auto constexpr SUPERINTERVAL = [](const std::pair<int, int> &a,
                                  const std::pair<int, int> &b) -> bool {
  int cmp = a.first - b.first;
  if (cmp == 0)
    return a.second < b.second;
  else
    return cmp > 0;
};

auto constexpr SUBINTERVAL = [](const std::pair<int, int> &a,
                                const std::pair<int, int> &b) -> bool {
  int cmp = a.first - b.first;
  if (cmp == 0)
    return a.second > b.second;
  else
    return cmp < 0;
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  std::map<std::pair<int, int>, int, decltype(::SUPERINTERVAL)>
      mapToSuperInterval{};
  std::map<std::pair<int, int>, int, decltype(::SUBINTERVAL)>
      mapToSubInterval{};

  for (size_t i = 0; i < n; i++) {
    int left, right;
    std::cin >> left >> right;
    auto pair = std::make_pair(left, right);
    ::intervals[i] = pair;
    mapToSuperInterval.insert({pair, 0});
    mapToSubInterval.insert({pair, 0});
  }

  int minHeight = INT_MAX;
  bool first = true;
  for (auto &[pair, value] : mapToSuperInterval) {
    if (first) [[unlikely]] {
      minHeight = pair.second;
      first = false;
    } else {
      if (pair.second < minHeight)
        minHeight = pair.second;
      else
        value = 1;
    }
  }

  for (size_t i = 0; i < n; i++)
    std::cout << mapToSuperInterval[::intervals[i]] << " ";

  std::cout << "\n";

  int maxHeight = INT_MIN;
  first = true;
  for (auto &[pair, value] : mapToSubInterval) {
    if (first) [[unlikely]] {
      maxHeight = pair.second;
      first = false;
    } else {
      if (pair.second > maxHeight) {
        maxHeight = pair.second;
      } else
        value = 1;
    }
  }

  for (size_t i = 0; i < n; i++)
    std::cout << mapToSubInterval[::intervals[i]] << " ";

  std::cout << "\n";

  return 0;
}
