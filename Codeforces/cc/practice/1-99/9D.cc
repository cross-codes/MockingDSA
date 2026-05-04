#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _9D
{

auto run() -> void
{
  std::array<std::array<i64, 36>, 36> t{};
  t[0][0] = 1LL;

  for (int n = 1; n <= 35; n++)
  {
    for (int h = 1; h <= 35; h++)
    {
      i64 sum{};
      for (int m = 1; m <= n; m++)
      {
        i64 leftSum{}, rightSum{};

        for (int i = 0; i <= h - 1; i++)
          leftSum += t[n - m][i];

        sum += t[m - 1][h - 1] * leftSum;

        for (int i = 0; i <= h - 2; i++)
          rightSum += t[m - 1][i];

        sum += t[n - m][h - 1] * rightSum;
      }

      t[n][h] = sum;
    }
  }

  int N, H;
  std::cin >> N >> H;

  i64 res{};
  for (int i = H; i <= N; i++)
    res += t[N][i];

  std::println("{}", res);
}

} // namespace _9D

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
    _9D::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
