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

namespace _416D
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  int a[n], b[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  for (int i = 0; i < n; i++)
    std::cin >> b[i];

  int64_t tot{};
  for (int i = 0; i < n; i++)
    tot += a[i] + b[i];

  // tot - cm c = num ai + bi > m
  std::multiset<int64_t, std::greater<>> set1(a, a + n);
  std::multiset<int64_t> set2(b, b + n);

  int64_t c{};
  for (int64_t e : set1)
  {
    auto it = set2.lower_bound(m - e);
    if (it != set2.end())
    {
      set2.erase(it);
      c += 1;
    }
  }

  std::cout << tot - (c * m) << "\n";
}

} // namespace _416D

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
    _416D::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
