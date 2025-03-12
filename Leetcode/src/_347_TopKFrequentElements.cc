#include <algorithm>
#include <array>
#include <ranges>
#include <vector>

class Solution {
 private:
  inline static auto INVERSE_PAIR_ORDER =
      [](const std::pair<int, std::size_t>& a,
         const std::pair<int, std::size_t>& b) -> bool {
    return a.second > b.second;
  };

 public:
  std::vector<int> topKFrequent(std::vector<int>& nums, int k) {
    std::array<std::pair<int, std::size_t>, 2001> freq = {};
    for (int i = -1000; i <= 1000; i++)
      freq[i + 1000].first = i;

    for (const auto& num : nums)
      freq[num + 1000].second++;

    std::sort(freq.begin(), freq.end(), Solution::INVERSE_PAIR_ORDER);

    return freq | std::views::take(k) |
           std::views::transform(
               [](std::pair<int, std::size_t> a) { return a.first; }) |
           std::ranges::to<std::vector>();
  }
};
