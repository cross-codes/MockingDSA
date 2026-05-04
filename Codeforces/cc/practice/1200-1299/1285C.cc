#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
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

namespace _1285C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int64_t a[n], sum{};
  for (int i = 0; i < n; i++)
  {
    std::cin >> a[i];
    sum += a[i];
  }

  int64_t best{INT64_MIN}, curr{};
  for (int i = 0; i < n; i++)
  {
    curr = std::max(curr + a[i], a[i]);
    best = std::max(best, curr);
  }

  if (best == sum)
  {
    int64_t fcurr{}, fbest{INT64_MIN};
    for (int i = 0; i < n; i++)
    {
      if (fbest == best)
      {
        std::cout << "NO\n";
        return;
      }

      fcurr = std::max(fcurr + a[i], a[i]);
      fbest = std::max(fbest, fcurr);
    }

    fcurr = 0, fbest = INT64_MIN;
    std::reverse(a, a + n);
    for (int i = 0; i < n; i++)
    {
      if (fbest == best)
      {
        std::cout << "NO\n";
        return;
      }

      fcurr = std::max(fcurr + a[i], a[i]);
      fbest = std::max(fbest, fcurr);
    }

    std::cout << "YES\n";
    return;
  }

  if (best < sum)
    std::cout << "YES\n";
  else
    std::cout << "NO\n";
}

} // namespace _1285C

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
    _1285C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
