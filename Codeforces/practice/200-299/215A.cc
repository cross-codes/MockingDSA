#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _215A
{

auto run() -> void
{
  usize n, m;
  std::cin >> n;

  std::unique_ptr<int[]> a(new int[n]);
  for (usize i = 0UZ; i < n; i++)
    std::cin >> a[i];

  std::cin >> m;
  std::unique_ptr<int[]> b(new int[m]);
  for (usize i = 0UZ; i < m; i++)
    std::cin >> b[i];

  std::map<int, int> gearRatio{};
  for (usize i = 0UZ; i < n; i++)
    for (usize j = 0UZ; j < m; j++)
    {
      if (b[j] % a[i] == 0)
        gearRatio[b[j] / a[i]]++;
    }

  std::println("{}", (--gearRatio.end())->second);
}

} // namespace _215A

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
    _215A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
