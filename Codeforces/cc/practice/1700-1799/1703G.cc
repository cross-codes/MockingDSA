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

namespace _1703G
{

auto run() -> void
{
  int64_t n, k;
  std::cin >> n >> k;

  int64_t a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  int64_t mxc[n + 1][33];
  for (int i = 0; i < 33; i++)
    mxc[0][i] = 0;

  int64_t sum{};
  for (int i = 1; i <= n; i++)
  {
    sum += a[i - 1];
    mxc[i][0] = sum - k * i;
  }

  for (int i = 1; i <= n; i++)
    for (int j = 1; j < 33; j++)
    {
      int64_t op1 = mxc[i - 1][j - 1] + a[i - 1] / (1LL << j);
      int64_t op2 = mxc[i - 1][j] - k + a[i - 1] / (1LL << j);
      mxc[i][j]   = std::max(op1, op2);
    }

  int64_t mx{INT64_MIN};
  for (int i = 0; i <= n; i++)
    for (int j = 0; j < 33; j++)
      mx = std::max(mx, mxc[i][j]);

  std::cout << mx << "\n";
}

} // namespace _1703G

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
    _1703G::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
