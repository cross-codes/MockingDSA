#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _149A
{

auto run() -> void
{
  int k;
  std::cin >> k;

  std::array<int, 12> growth{};
  for (usize i = 0UZ; i < 12UZ; i++)
    std::cin >> growth[i];

  if (k == 0) [[unlikely]]
  {
    std::println("0");
    return;
  }

  std::ranges::sort(growth);

  int offset{};
  for (ssize i = 11Z; i >= 0Z; i--)
  {
    offset += growth[i];
    if (offset >= k)
    {
      std::println("{}", growth.size() - i);
      return;
    }
  }

  std::println("-1");
}

} // namespace _149A

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
    _149A::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
