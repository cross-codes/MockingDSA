#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _D
{

constexpr int N = 1000001;

auto run() -> void
{

  i64 n;
  std::cin >> n;

  std::unordered_map<i64, i64> cubes{};
  cubes.reserve(N);

  for (i64 i = 1LL; i <= N; i++)
  {
    i64 cube = i * i * i;
    cubes.insert({cube, i});
    auto it = cubes.find(cube - n);
    if (it != cubes.end())
    {
      std::cout << i << " " << it->second << "\n";
      return;
    }
  }

  std::cout << "-1\n";
}

} // namespace _D

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
    _D::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
