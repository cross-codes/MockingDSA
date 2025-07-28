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

namespace _1215B
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int a[n];
  for (int i = 0; i < n; i++)
  {
    int x;
    std::cin >> x;
    if (x > 0)
      a[i] = 1;
    else
      a[i] = -1;
  }

  int prefix[n + 1];
  prefix[0] = 1;
  for (int i = 1; i <= n; i++)
    prefix[i] = prefix[i - 1] * a[i - 1];

  int pos{}, neg{};
  int64_t res1{};
  for (int i = 1; i <= n; i++)
  {
    if (prefix[i] > 0)
      pos += 1;
    else
    {
      res1 += 1;
      neg += 1;
    }

    if (prefix[i] > 0)
      res1 += neg;
    else
      res1 += pos;
  }

  int64_t tot = (1LL * n * (n + 1)) >> 1;

  std::cout << res1 << " " << tot - res1 << "\n";
}

} // namespace _1215B

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
  while (t-- > 0)
    _1215B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
