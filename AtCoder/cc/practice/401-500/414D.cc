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

namespace _414D
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  int64_t x[n];
  for (int i = 0; i < n; i++)
    std::cin >> x[i];

  std::sort(x, x + n);

  std::vector<int64_t> gaps{};
  for (int i = 0; i < n - 1; i++)
    gaps.push_back(x[i + 1] - x[i]);

  std::sort(gaps.begin(), gaps.end());
  std::reverse(gaps.begin(), gaps.end());

  int64_t res = x[n - 1] - x[0];
  for (int i = 0; i < m - 1; i++)
    res -= gaps[i];

  std::cout << res << "\n";
}

} // namespace _414D

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
    _414D::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
