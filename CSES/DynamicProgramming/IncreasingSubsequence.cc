#include <climits>
#include <cstdint>
#include <iostream>
#include <set>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
int nums[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> nums[i];

  std::set<int> sequence{};

  for (std::size_t i = 0; i < n; i++) {
    auto it = sequence.lower_bound(nums[i]);
    if (it == sequence.end())
      sequence.insert(nums[i]);
    else
      sequence.erase(it), sequence.insert(nums[i]);
  }

  std::cout << sequence.size() << "\n";

  return 0;
}
