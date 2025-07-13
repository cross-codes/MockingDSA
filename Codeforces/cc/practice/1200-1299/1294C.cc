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

namespace _1294C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> factors{};
  for (int i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      factors.push_back(i);
      if (i * i != n)
        factors.push_back(n / i);
    }
  }

  auto is_prime = [](int n) -> bool {
    if (n < 2)
      return false;

    for (int i = 2; i * i <= n; i++)
      if (n % i == 0)
        return false;

    return true;
  };

  for (int f : factors)
  {
    if (!is_prime(f))
    {
      for (int i = 2; i * i < f; i++)
      {
        if (f % i == 0 && n / f != i && f / i != n / f)
        {
          std::cout << std::format("YES\n{} {} {}\n", i, f / i, n / f);
          return;
        }
      }
    }
  }

  std::cout << "NO\n";
}

} // namespace _1294C

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
  std::cin >> t;
  while (t-- > 0)
    _1294C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
