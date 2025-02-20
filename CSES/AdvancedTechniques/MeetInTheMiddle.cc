#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _MeetInTheMiddle {

auto run() -> void {
  usize n;
  u64 x;
  std::cin >> n >> x;

  std::unique_ptr<u64[]> list(new u64[n]);
  std::memset(list.get(), 0x00, sizeof(u64) * n);

  for (usize i = 0; i < n; i++)
    std::cin >> list[i];

  std::sort(&list[0], &list[n]);

  std::unordered_map<u64, usize> firstSums{};
  firstSums.reserve(1 << (n >> 1));

  for (int i = 0; i < (1 << (n >> 1)); i++) {
    u64 currentSum = 0U;
    for (u32 j = 0; j < (n >> 1); j++) {
      if (i & (1 << j))
        currentSum += list[j];
      if (currentSum > x)
        break;
    }
    if (currentSum <= x)
      firstSums[currentSum]++;
  }

  u64 cnt{};
  for (int i = 0; i < (1 << (n - (n >> 1))); i++) {
    u64 currentSum = 0U;
    for (u32 j = 0; j < (n - (n >> 1)); j++) {
      if (i & (1 << j))
        currentSum += list[j + (n >> 1)];
      if (currentSum > x)
        break;
    }
    if (currentSum <= x)
      cnt += firstSums[x - currentSum];
  }

  std::cout << cnt << "\n";
}

} // namespace _MeetInTheMiddle

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

  while (t-- > 0)
    _MeetInTheMiddle::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
