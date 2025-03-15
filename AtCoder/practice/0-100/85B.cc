#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _85B
{

auto run() -> void
{
  ssize N;
  std::cin >> N;

  std::vector<int> d(N);
  for (ssize i = 0; i < N; i++)
    std::cin >> d[i];

  std::ranges::sort(d, std::ranges::greater());

  int prev{INT_MAX};
  u32 cnt{};
  for (int i = 0; i < N; i++)
  {
    if (d[i] < prev)
    {
      cnt++;
      prev = d[i];
    }
  }

  std::cout << cnt << "\n";
}

} // namespace _85B

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
    _85B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
