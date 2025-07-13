#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath> // IWYU pragma: keep
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _S
{

constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

auto run() -> void
{
  std::string K;
  int D;
  std::cin >> K >> D;

  int64_t lookup[10000][100][2];
  std::memset(lookup, -1, sizeof lookup);

  auto call = [&K, &D, &lookup](auto &&call, int i, int rem,
                                bool equal) -> int64_t {
    if (i == static_cast<int>(K.size()))
      return rem == 0;

    if (lookup[i][rem][equal] != -1)
      return lookup[i][rem][equal];

    int64_t res{};
    for (int d = 0; d < 10; d++)
    {
      if (equal && d > K[i] - '0')
        break;

      res =
          (res + call(call, i + 1, (rem + d) % D, equal && (d == K[i] - '0'))) %
          MOD;
    }

    return lookup[i][rem][equal] = res;
  };

  std::cout << (call(call, 0, 0, true) - 1 + MOD) % MOD << "\n";
}

} // namespace _S

int main()
{
#ifdef ANTUMBRA
  const rlim_t stack_size = 256 * 1024 * 1024;
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
    _S::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
