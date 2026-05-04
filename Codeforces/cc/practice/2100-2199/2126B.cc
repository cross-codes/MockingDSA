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

namespace _2126B
{

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  int a[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  int cnt{};
  for (int i = 0; i < n; i++)
  {
    bool ok{true};
    int badidx{-1};
    for (int j = i; j < i + k; j++)
    {
      if (j == n)
        goto declare;

      if (a[j] != 0)
      {
        ok     = false;
        badidx = j;
      }
    }

    if (ok)
    {
      cnt += 1;
      i += 1;
      i += k - 1;
    }
    else
      i = badidx;
  }

declare:
  std::cout << cnt << "\n";
}

} // namespace _2126B

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
    _2126B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
