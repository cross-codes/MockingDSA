#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n, k;
  std::cin >> n >> k;

  std::vector<int> input(n);
  for (std::size_t i = 0; i < n; i++)
    std::cin >> input[i];

  u64 cost = 0U;
  for (std::size_t start = 0; start + k <= n; start++) {
    std::vector<int> subVector(input.begin() + start,
                               input.begin() + start + k);
    std::sort(subVector.begin(), subVector.end());
    int median = subVector[subVector.size() >> 1];

    for (const auto &num : subVector)
      cost += std::abs(num - median);

    std::cout << cost << " ";
    cost = 0U;
  }

  std::cout << "\n";

  return 0;
}
