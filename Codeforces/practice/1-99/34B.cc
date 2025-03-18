#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _34B
{

auto run() -> void
{
  usize n, m;
  std::cin >> n >> m;

  std::unique_ptr<int[]> a(new int[n]);
  for (usize i = 0UZ; i < n; i++)
    std::cin >> a[i];

  std::sort(a.get(), a.get() + n);

  usize amtToCarry{};
  i64 maxMoney{};
  for (usize i = 0UZ; i < n; i++)
  {
    if (amtToCarry == m || a[i] >= 0)
      break;

    maxMoney += std::abs(a[i]);
    amtToCarry++;
  }

  std::println("{}", maxMoney);
}

} // namespace _34B

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
    _34B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
