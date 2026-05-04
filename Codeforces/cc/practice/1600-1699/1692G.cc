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

namespace _1692G
{

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  int a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  int v[n];
  v[0] = 0;
  for (int i = 1; i < n; i++)
    if ((a[i] << 1) > a[i - 1])
      v[i] = 1;
    else
      v[i] = 0;

  int64_t cnt{};
  int l{}, r{1};
  while (r < n)
  {
    if (v[r] != 1)
    {
      cnt += std::max(0, r - (l + k));
      l = r;
    }

    r += 1;
  }

  cnt += std::max(0, n - (l + k));
  std::cout << cnt << "\n";
}

} // namespace _1692G

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
    _1692G::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
