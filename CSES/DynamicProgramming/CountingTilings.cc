#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _CountingTilings
{

constexpr long double MOD = 1e9 + 7;

auto run() -> void
{
  usize n, m;
  std::cin >> n >> m;

  auto nLim = static_cast<usize>(std::ceil(static_cast<long double>(n) / 2.0)),
       mLim = static_cast<usize>(std::ceil(static_cast<long double>(m) / 2.0));

  long double product{1.0L}, PI = std::numbers::pi_v<long double>;
  for (usize a = 1; a <= nLim; a++)
    for (usize b = 1; b <= mLim; b++)
    {
      product *= 4 * (std::pow(std::cos(PI * a / (n + 1.0L)), 2) +
                      std::pow(std::cos(PI * b / (m + 1.0L)), 2));

      long double rem = std::remainderl(product, MOD);
      if (rem < 0)
        product = rem + MOD;
      else
        product = rem;
    }

  if (product <= 1e-9)
  {
    std::cout << "0\n";
    return;
  }

  std::cout << std::roundl(product) << "\n";
}

} // namespace _CountingTilings

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
    _CountingTilings::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
