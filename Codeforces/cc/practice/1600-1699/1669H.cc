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

namespace _1669H
{

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  uint32_t a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  std::array<int, 31> unset;
  std::fill(unset.begin(), unset.end(), n);

  uint32_t res = a[0];
  for (int j = 0; j < 31; j++)
    if (a[0] & (1U << j))
      unset[j] -= 1;

  for (int i = 1; i < n; i++)
  {
    for (int j = 0; j < 31; j++)
      if (a[i] & (1U << j))
        unset[j] -= 1;

    res &= a[i];
  }

  for (int i = 30; i >= 0; i--)
  {
    if (unset[i] <= k)
    {
      res |= (1U << i);
      k -= unset[i];
    }
  }

  std::cout << res << "\n";
}

} // namespace _1669H

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
    _1669H::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
