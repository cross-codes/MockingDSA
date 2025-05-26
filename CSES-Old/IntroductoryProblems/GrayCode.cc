#include <bitset>
#include <cstdint>
#include <iostream>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr int n_max = 16;

int
main ()
{
  std::cin.tie (nullptr)->sync_with_stdio (false);

  int n, numEntries;
  std::cin >> n, numEntries = 1 << n;

  for (int i = 0; i < numEntries; i++)
    std::cout
        << std::bitset<n_max> (i ^ (i >> 1)).to_string ().substr (n_max - n)
        << "\n";

  return 0;
}
