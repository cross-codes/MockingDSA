#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _EditDistance
{

auto run() -> void
{
  std::string x, y;
  std::cin >> x >> y;

  auto n = x.size(), m = y.size();

  std::array<std::array<int, 5001>, 5001> d;
  std::iota(d[0].begin(), d[0].begin() + m + 1, 0);
  for (int i = 0; i <= static_cast<int>(n); i++)
    d[i][0] = i;

  for (std::size_t i = 1; i <= n; i++)
    for (std::size_t j = 1; j <= m; j++)
    {
      int cost = (x[i - 1] == y[j - 1]) ? 0 : 1;
      d[i][j]  = std::min(d[i - 1][j] + 1,
                          std::min(d[i][j - 1] + 1, d[i - 1][j - 1] + cost));
    }

  std::cout << d[n][m] << "\n";
}

} // namespace _EditDistance

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
    _EditDistance::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
