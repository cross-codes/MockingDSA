#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _339B
{

auto run() -> void
{
  ssize n, m;
  std::cin >> n >> m;

  ssize currentPos{1Z};
  i64 totalTime{};
  for (ssize i = 0Z; i < m; i++)
  {
    int housePos;
    std::cin >> housePos;
    if (housePos >= currentPos)
      totalTime += housePos - currentPos;
    else
      totalTime += n - currentPos + housePos;

    currentPos = housePos;
  }

  std::println("{}", totalTime);
}

} // namespace _339B

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
    _339B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
