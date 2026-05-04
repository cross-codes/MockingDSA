#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1881D
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int64_t a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  std::sort(a, a + n, std::greater<>());

  if (a[0] == a[n - 1])
  {
    std::cout << "YES\n";
    return;
  }

  auto perfect_square = [](int64_t n) -> bool {
    int sqrt = static_cast<int>(std::sqrt(n));
    return sqrt * sqrt == n;
  };

  std::vector<int64_t> candidates{};
  for (int i = 2; i < n; i++)
    if (a[0] % a[i] == 0 && (perfect_square(a[0] / a[i])))
    {
      int64_t factor = static_cast<int64_t>(std::sqrt(a[0] / a[i]));
      if (a[0] % factor == 0)
        candidates.push_back(static_cast<int64_t>(std::sqrt(a[0] * a[i])));
    }

  for (auto e : candidates)
    std::cout << e << "\n";

  int64_t a_cpy[n];
  for (int64_t c : candidates)
  {
    std::memcpy(a_cpy, a, sizeof a);
    // make every number a != c -> c
    // check if c is a factor of a (a / c = x)
    // check if some other b != c exists where b * x = c
    for (int i = 0; i < n; i++)
    {
      if (a_cpy[i] != c)
      {
        if (a_cpy[i] > c && a_cpy[i] % c == 0)
        {
          int64_t x = a_cpy[i] / c;
          bool ok{};
          for (int j = i + 1; j < n; j++)
          {
            if (a_cpy[j] < c && a_cpy[j] * x == c)
            {
              a_cpy[j] *= x;
              ok = true;
              break;
            }
          }
          if (!ok)
            break;
          else
            a_cpy[i] /= x;
        }
      }
    }

    if (std::all_of(a_cpy, a_cpy + n,
                    [&c](int64_t a) -> bool { return a == c; }))
    {
      std::cout << "YES\n";
      return;
    }
  }

  std::cout << "NO\n";
}

} // namespace _1881D

int main()
{
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef ANTUMBRA
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size)
  {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  std::cin >> t;
  while (t-- > 0)
    _1881D::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
