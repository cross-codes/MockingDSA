#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _320A
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int numDigits = static_cast<int>(std::floor(std::log10(n))) + 1;
  std::array<std::string, 3> numbers{"1", "14", "144"};

  int xLim{numDigits}, yLim{numDigits / 2}, zLim{numDigits / 3};

  for (int x = 0; x <= xLim; x++)
  {
    for (int y = 0; y <= yLim; y++)
    {
      for (int z = 0; z <= zLim; z++)
      {
        if (x + (2 * y) + (3 * z) <= numDigits)
        {
          std::vector<std::string> strComp;
          for (int i = 0; i < x; i++)
            strComp.push_back(numbers[0]);
          for (int i = 0; i < y; i++)
            strComp.push_back(numbers[1]);
          for (int i = 0; i < z; i++)
            strComp.push_back(numbers[2]);

          do
          {
            int num{};
            std::string str = std::accumulate(strComp.begin(), strComp.end(),
                                              std::string(""));

            auto [ptr, ec] =
                std::from_chars(str.data(), str.data() + str.size(), num);

            if (ec == std::errc::result_out_of_range)
              break;

            if (num == n)
            {
              std::println("YES");
              return;
            }
          } while (std::next_permutation(strComp.begin(), strComp.end()));
        }
      }
    }
  }

  std::println("NO");
}

} // namespace _320A

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
    _320A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
