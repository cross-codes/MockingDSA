#include <bits/stdc++.h>

#pragma GCC target("popcnt")

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _HammingDistance
{

auto run() -> void
{
  usize n, k;
  std::cin >> n >> k;

  std::unique_ptr<u32[]> nums(new u32[n]);

  for (usize i = 0; i < n; i++)
  {
    std::string bitString;
    std::cin >> bitString;
    nums[i] = static_cast<u32>(std::bitset<30>(bitString).to_ulong());
  }

  int minHammingDistance{INT_MAX};
  for (usize i = 0; i < n; i++)
  {
    for (usize j = i + 1; j < n; j++)
      minHammingDistance =
          std::min(minHammingDistance, std::popcount(nums[i] ^ nums[j]));
  }

  std::cout << minHammingDistance << "\n";
}

} // namespace _HammingDistance

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
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
    _HammingDistance::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
