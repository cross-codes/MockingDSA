#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _43A
{

auto run() -> void
{
  usize n;
  std::cin >> n;

  int score1{1}, score2{};
  std::string team1{}, team2{};
  std::cin >> team1;
  for (usize i = 1UZ; i < n; i++)
  {
    std::string team;
    std::cin >> team;

    if (team == team1)
      score1++;
    else if (team2.empty())
    {
      score2++;
      team2 = team;
    }
    else
      score2++;
  }

  std::println("{}", score1 > score2 ? team1 : team2);
}

} // namespace _43A

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
    _43A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
