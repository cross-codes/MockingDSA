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

namespace _CompanyQueriesI
{

auto run() -> void
{
  int n, q;
  std::cin >> n >> q;

  int lift[n][20];
  for (int i = 1; i <= n - 1; i++)
  {
    int p;
    std::cin >> p;
    lift[i][0] = p - 1;
  }

  for (int i = 0; i < 20; i++)
    lift[0][i] = -1;

  for (int i = 1; i < 20; i++)
    for (int u = 0; u < n; u++)
      if (lift[u][i - 1] == -1)
        lift[u][i] = -1;
      else
        lift[u][i] = lift[lift[u][i - 1]][i - 1];

  while (q-- > 0)
  {
    int u, k;
    std::cin >> u >> k;

    int curr = u - 1;
    while (k != 0)
    {
      int pos = __builtin_ctz(k);
      curr    = lift[curr][pos];
      if (curr == -1)
        break;
      k &= (k - 1);
    }

    if (curr == -1)
      std::cout << curr << "\n";
    else
      std::cout << curr + 1 << "\n";
  }
}

} // namespace _CompanyQueriesI

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
    _CompanyQueriesI::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
