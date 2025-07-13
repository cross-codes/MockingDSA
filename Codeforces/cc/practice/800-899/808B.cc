#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iomanip>
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _808B
{

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  int a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  __int128_t win_sum{}, tot{};
  for (int i = 0; i < k; i++)
    win_sum += a[i];

  tot = win_sum;

  int window_start{};
  for (int i = k; i < n; i++)
  {
    win_sum += a[i];
    win_sum -= a[window_start];
    window_start += 1;
    tot += win_sum;
  }

  std::cout << std::fixed << std::setprecision(10)
            << (static_cast<long double>(tot) / (n - k + 1)) << "\n";
}

} // namespace _808B

int main()
{
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
  while (t-- > 0)
    _808B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
