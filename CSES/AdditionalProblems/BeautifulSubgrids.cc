#include <bits/stdc++.h>

#pragma GCC target("popcnt")

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _BeautifulSubgrids
{

auto run() -> void
{
  usize n;
  std::cin >> n;

  std::array<std::array<u32, 100>, 3000> grid{};

  for (usize y = 0; y < n; y++)
  {
    std::string row;
    std::cin >> row;

    usize x{};
    while (x != row.size())
    {
      if (row[x] == '1')
        grid[y][x / 30] |= (1U << (x % 30));
      x++;
    }
  }

  i64 subGrids{};
  for (usize ya = 0; ya < 3000; ya++)
  {
    for (usize yb = ya + 1; yb < 3000; yb++)
    {
      i64 count{};
      for (usize k = 0; k < 100; k++)
        count += std::popcount(grid[ya][k] & grid[yb][k]);
      subGrids += (count * (count - 1)) >> 1;
    }
  }

  std::cout << subGrids << "\n";
}

} // namespace _BeautifulSubgrids

int main()
{
#ifdef CROSS
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
    _BeautifulSubgrids::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
