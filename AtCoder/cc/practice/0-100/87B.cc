#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _87B
{

auto run() -> void
{
  std::array<int, 3> coins{500, 100, 50};
  std::array<int, 3> cnt;

  for (int i = 0; i < 3; i++)
    std::cin >> cnt[i];

  int X;
  std::cin >> X;

  u64 res{};
  for (int i = 0; i <= cnt[0]; i++)
  {
    for (int j = 0; j <= cnt[1]; j++)
    {
      for (int k = 0; k <= cnt[2]; k++)
      {
        if (coins[0] * i + coins[1] * j + coins[2] * k == X)
          res++;
      }
    }
  }

  std::cout << res << "\n";
}

} // namespace _87B

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
    _87B::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
