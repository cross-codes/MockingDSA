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

namespace _2018
{

constexpr int64_t MOD = static_cast<int64_t>(1e9 + 7);

auto run() -> void
{
  int n, a, b;
  std::cin >> n >> a >> b;

  int64_t num[n + 1][2];
  std::memset(num, 0x00, sizeof num);
  num[0][0] = num[0][1] = 1;

  for (int i = 0; i < n; i++)
  {
    for (int j = 1; j <= a && i + j <= n; j++)
      num[i + j][0] = (num[i + j][0] + num[i][1]) % MOD;

    for (int j = 1; j <= b && i + j <= n; j++)
      num[i + j][1] = (num[i + j][1] + num[i][0]) % MOD;
  }

  std::cout << (num[n][0] + num[n][1]) % MOD << "\n";
}

} // namespace _2018

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
    _2018::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
