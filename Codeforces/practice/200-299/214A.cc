#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _214A
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  int aMax{static_cast<int>(std::floor(std::sqrt(n)))};
  int bMax{static_cast<int>(std::floor(std::sqrt(m)))};

  i64 numPairs{};
  for (int a = 0; a <= aMax; a++)
  {
    for (int b = 0; b <= bMax; b++)
    {
      if ((a * a) + b == n && a + (b * b) == m)
        numPairs++;
    }
  }

  std::println("{}", numPairs);
}

} // namespace _214A

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
    _214A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
