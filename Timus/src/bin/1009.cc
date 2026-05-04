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

namespace _1009
{

auto run() -> void
{
  int N, K;
  std::cin >> N >> K;

  int64_t lookup[20][10];
  std::memset(lookup, -1, sizeof lookup);

  auto call = [&N, &K, &lookup](auto &&call, int pos, int prev) -> int64_t {
    if (pos == N)
      return 1;

    if (lookup[pos][prev] != -1)
      return lookup[pos][prev];

    int64_t res{};
    for (int d = 0; d < K; d++)
    {
      if (d == 0 && prev == 0)
        continue;

      res += call(call, pos + 1, d);
    }

    return lookup[pos][prev] = res;
  };

  int64_t res{};
  for (int i = 1; i < K; i++)
    res += call(call, 1, i);

  std::cout << res << "\n";
}

} // namespace _1009

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
    _1009::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
