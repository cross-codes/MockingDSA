#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _579A
{

auto run() -> void
{
  int x;
  std::cin >> x;

  if (x <= 0)
    __builtin_unreachable();

  if (x == 1)
  {
    std::println("1");
    return;
  }

  std::println("{}",
               (x & 1) ? __builtin_popcount(x - 1) + 1 : __builtin_popcount(x));
}

} // namespace _579A

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
    _579A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
