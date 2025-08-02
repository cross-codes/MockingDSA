#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <set>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1374D
{

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  std::multiset<int> a{};
  for (int i = 0; i < n; i++)
  {
    int x;
    std::cin >> x;
    if (x % k != 0)
      a.insert(x % k);
  }

  int64_t x{};
  while (!a.empty())
  {
    auto it = a.lower_bound(x % k);
    if (it == a.end())
      x = ((x / k) + 1) * k;
    else
    {
      if (*it == x % k)
        a.erase(it);
      else
      {
        x += *it - (x % k);
        a.erase(it);
      }
      x += 1;
    }
  }

  std::cout << x << "\n";
}

} // namespace _1374D

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
    _1374D::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
