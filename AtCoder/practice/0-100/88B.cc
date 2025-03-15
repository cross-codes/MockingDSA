#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _88B
{

auto run() -> void
{
  int N;
  std::cin >> N;

  std::unique_ptr<int[]> a(new int[N]);
  for (int i = 0; i < N; i++)
    std::cin >> a[i];

  std::sort(a.get(), a.get() + N);

  int sum1{}, sum2{};
  bool first = true;
  for (int i = N - 1; i >= 0; i--)
  {
    if (first)
      sum1 += a[i];
    else
      sum2 += a[i];
    first = !first;
  }

  std::cout << sum1 - sum2 << "\n";
}

} // namespace _88B

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
    _88B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
