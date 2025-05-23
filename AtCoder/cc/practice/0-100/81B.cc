#include <bits/stdc++.h>

#pragma GCC target("popcnt")

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _81B
{

auto run() -> void
{
  usize n;
  std::cin >> n;

  int num, min{INT_MAX};
  for (usize i = 0; i < n; i++)
  {
    std::cin >> num;
    min = std::min(min, __builtin_ctz(num));
  }

  std::cout << min << "\n";
}

} // namespace _81B

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
    _81B::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
