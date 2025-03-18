#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _B
{

auto run() -> void
{
  std::string s;
  std::cin >> s;

  usize n = s.size();
  usize toAdd{};

  bool I = true;
  for (usize i = 0; i < n; i++)
  {
    if (I)
    {
      if (s[i] != 'i')
      {
        toAdd++;
        I = !I;
      }
    }
    else
    {
      if (s[i] != 'o')
      {
        toAdd++;
        I = !I;
      }
    }

    I = !I;
  }

  if ((toAdd + n) & 1)
    toAdd++;

  std::cout << toAdd << "\n";
}

} // namespace _B

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
    _B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
