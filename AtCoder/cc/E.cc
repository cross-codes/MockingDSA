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

namespace _E
{

auto run() -> void
{

  int64_t N;
  std::cin >> N;

  // b + 1 ... 2b - 1, 2b + 1..3b - 1 .... N
  // bmax = N - 1. After that a == c (TLE)

  int64_t cnt{};
  for (int b = 2; b < N; b++)
  {
    int64_t K =
        static_cast<int64_t>(std::ceil((N - 1) / static_cast<long double>(b)));

    cnt += (b - 1) * (K - 2) + (N - ((K - 1) * b + 1) + 1);
    if (N % b == 0)
      cnt -= 1;
  }

  std::cout << cnt << "\n";
}

} // namespace _E

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
    _E::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
