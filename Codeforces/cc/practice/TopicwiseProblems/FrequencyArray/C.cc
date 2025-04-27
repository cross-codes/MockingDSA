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
  usize n;
  std::cin >> n;

  std::array<int, 101> freq{};
  for (usize i = 0UZ; i < n; i++)
  {
    int num;
    std::cin >> num;
    freq[num]++;
  }

  u32 numFrames{};
  for (usize i = 0UZ; i < 101; i++)
  {
    for (usize j = i + 1; j < 101; j++)
    {
      if (freq[i] >= 2 && freq[j] >= 2)
      {
        if (freq[i] > freq[j])
        {
          int addAmt = freq[j] >> 1;
          freq[i] -= addAmt << 1;
          numFrames += addAmt;
          freq[j] = 1;
        }
        else
        {
          int addAmt = freq[i] >> 1;
          freq[j] -= addAmt << 1;
          numFrames += addAmt;
          freq[i] = 1;
          break;
        }
      }
    }
  }

  for (u32 i = 0; i < 101; i++)
  {
    if (freq[i] >= 4)
    {
      numFrames += freq[i] >> 2;
    }
  }

  std::println("{}", numFrames);
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
