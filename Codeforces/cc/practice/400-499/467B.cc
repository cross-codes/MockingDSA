#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _467B
{

auto numberOfDifferingBits(u32, u32) -> usize;

auto run() -> void
{
  usize n, m, k;
  std::cin >> n >> m >> k;

  std::unique_ptr<int[]> x(new int[m + 1]);

  for (usize i = 0UZ; i < m + 1; i++)
    std::cin >> x[i];

  u32 cnt{};
  for (usize i = 0UZ; i < m; i++)
    if (numberOfDifferingBits(x[i], x[m]) <= k)
      cnt++;

  std::println("{}", cnt);
}

auto numberOfDifferingBits(u32 a, u32 b) -> usize
{
  usize res{};
  u32 ptr{1U};
  if ((ptr & a) != (ptr & b))
    res++;

  for (int i = 1; i < 32; i++)
  {
    ptr <<= 1;
    if ((ptr & a) != (ptr & b))
      res++;
  }

  return res;
}

} // namespace _467B

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
    _467B::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
