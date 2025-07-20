#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <numeric>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _CompanyQueriesII
{

auto run() -> void
{
  int n, q;
  std::cin >> n >> q;

  int lift[n][20];
  std::vector<int> adj[n];
  for (int i = 1; i <= n - 1; i++)
  {
    int p;
    std::cin >> p;

    lift[i][0] = p - 1;
    adj[p - 1].push_back(i);
    adj[i].push_back(p - 1);
  }

  for (int i = 0; i < 20; i++)
    lift[0][i] = -1;

  int depth[n];
  depth[0] = 0;

  auto dfs = [&adj, &depth](auto &&dfs, int u, int p) -> void {
    for (const int &v : adj[u])
      if (v != p)
      {
        depth[v] = depth[u] + 1;
        dfs(dfs, v, u);
      }
  };

  dfs(dfs, 0, -1);

  for (int i = 1; i < 20; i++)
    for (int u = 0; u < n; u++)
      if (lift[u][i - 1] == -1)
        lift[u][i] = -1;
      else
        lift[u][i] = lift[lift[u][i - 1]][i - 1];

  auto ancestor = [&lift](int u, int k) {
    int curr = u;
    while (k != 0)
    {
      int pos = __builtin_ctz(k);
      curr    = lift[curr][pos];
      if (curr == -1)
        return 0;

      k &= (k - 1);
    }

    return curr;
  };

  while (q-- > 0)
  {
    int a, b;
    std::cin >> a >> b;
    a -= 1, b -= 1;

    if (depth[a] < depth[b])
      std::swap(a, b);

    a = ancestor(a, depth[a] - depth[b]);
    if (a == b)
      std::cout << a + 1 << "\n";
    else
    {
      for (int j = 19; j >= 0; j--)
        if (lift[a][j] != lift[b][j])
        {
          a = lift[a][j];
          b = lift[b][j];
        }

      std::cout << lift[a][0] + 1 << "\n";
    }
  }
}

} // namespace _CompanyQueriesII

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
    _CompanyQueriesII::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
