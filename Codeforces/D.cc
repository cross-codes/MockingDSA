#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "{}", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _D {

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::unique_ptr<int[]> a(new int[n]);

  for (ssize i = 0Z; i < n; i++)
    std::cin >> a[i];

  i64 maxNegDiff = INT64_MAX;
  ssize bestStartIdx = 0Z;
  for (ssize i = 0Z; i < n; i++) {
    ssize numG{0Z}, numLe{0Z};
    for (ssize j = i + 1; j < n; j++) {
      if (a[i] >= a[j])
        numLe++;
      else if (a[i] < a[j])
        numG++;
    }

    if (numG - numLe < maxNegDiff) {
      maxNegDiff = numG - numLe;
      bestStartIdx = i;
    }
  }

  if (maxNegDiff == INT64_MAX) {
    std::println("1 1");
    return;
  }

  int bestNum = a[bestStartIdx], curScore = 0, bestScore = INT_MIN;
  ssize bestEndIdx = 0Z;
  std::vector<int> numsInSwapRange{};
  for (ssize i = bestStartIdx + 1; i < n; i++) {
    if (a[i] < bestNum)
      curScore++;
    else if (a[i] > bestNum)
      curScore--;

    int test = curScore;
    for (const int &e : numsInSwapRange) {
      if (e < a[i])
        test--;
    }

    numsInSwapRange.push_back(a[i]);
    if (test >= bestScore) {
      bestEndIdx = i;
      bestScore = test;
    }
  }

  if (bestScore == INT_MIN) {
    std::println("1 1");
    return;
  }

  std::println("{} {}", bestStartIdx + 1, bestEndIdx + 1);
}

} // namespace _D

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};
  std::cin >> t;

  while (t-- > 0)
    _D::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
