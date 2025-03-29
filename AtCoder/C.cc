#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _C
{

auto run() -> void
{
  usize N;
  std::cin >> N;

  std::map<int, usize> freq{};
  std::unordered_set<int> blacklist{};
  for (usize i = 1; i < N + 1; i++)
  {
    int num;
    std::cin >> num;
    if (freq.contains(num) || blacklist.contains(num))
    {
      blacklist.insert(num);
      freq.erase(num);
    }
    else
      freq[num] = i;
  }

  if (freq.empty())
    std::cout << "-1\n";
  else
    std::cout << freq.rbegin()->second << "\n";
}

} // namespace _C

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
    _C::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
