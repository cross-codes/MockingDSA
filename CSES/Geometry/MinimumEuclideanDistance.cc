#ifdef CROSS
#define _GLIBCXX_DEBUG 1
#define _GLIBCXX_DEBUG_PEDANTIC 1
#define _GLIBCXX_SANITIZE_VECTOR 1
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

constexpr size_t _ = 200001;

std::pair<i64, i64> points[_];
i64 minSquareDistance = INT64_MAX;
bool isLeft[_];

auto square(i64 x) -> i64;

auto distance(const std::pair<i64, i64> &, const std::pair<i64, i64> &) -> i64;

void solve(std::vector<int>, std::vector<int>);

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  std::vector<int> sortedXIndices{}, sortedYIndices{};

  for (int i = 0; i < static_cast<int>(n); i++) {
    int x, y;
    std::cin >> x >> y;
    ::points[i] = {x, y};
    sortedXIndices.push_back(i), sortedYIndices.push_back(i);
  }

  std::sort(sortedXIndices.begin(), sortedXIndices.end(),
            [](int A, int B) { return ::points[A].first < ::points[B].first; });

  std::sort(sortedYIndices.begin(), sortedYIndices.end(), [](int A, int B) {
    return ::points[A].second < ::points[B].second;
  });

  solve(sortedXIndices, sortedYIndices);

  std::cout << ::minSquareDistance << "\n";

  return 0;
}

auto square(i64 x) -> i64 { return x * x; }

auto distance(const std::pair<i64, i64> &a, const std::pair<i64, i64> &b)
    -> i64 {
  i64 dx = a.first - b.first, dy = a.second - b.second;
  return square(dx) + square(dy);
}

void solve(std::vector<int> sortedXIndices, std::vector<int> sortedYIndices) {
  size_t len = sortedXIndices.size();
  if (len == 1U)
    return;

  std::vector<int> leftX{}, leftY{}, rightX{}, rightY{};
  for (size_t i = 0; i < len; i++) {
    if (i < len >> 1) {
      leftX.push_back(sortedXIndices[i]);
      ::isLeft[sortedXIndices[i]] = true;
    } else {
      rightX.push_back(sortedXIndices[i]);
      ::isLeft[sortedXIndices[i]] = false;
    }
  }

  for (int idx : sortedYIndices) {
    if (::isLeft[idx])
      leftY.push_back(idx);
    else
      rightY.push_back(idx);
  }

  solve(leftX, leftY);
  solve(rightX, rightY);

  i64 midX = ::points[leftX.back()].first;
  std::vector<int> strip;
  for (int idx : sortedYIndices)
    if (::square(::points[idx].first - midX) < minSquareDistance)
      strip.push_back(idx);

  for (size_t i = 0; i < strip.size(); i++)
    for (size_t j = i + 1;
         j < strip.size() &&
         square(::points[strip[i]].second - ::points[strip[j]].second) <
             minSquareDistance;
         j++)
      minSquareDistance =
          std::min(minSquareDistance,
                   ::distance(::points[strip[i]], ::points[strip[j]]));
}
