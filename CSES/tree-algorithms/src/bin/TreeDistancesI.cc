#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <queue>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _TreeDistancesI
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::vector<int> adj[n];
  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    std::cin >> u >> v;

    adj[u - 1].push_back(v - 1);
    adj[v - 1].push_back(u - 1);
  }

  bool visited[n];
  std::memset(visited, false, sizeof visited);

  int dist[n], dista[n], distb[n];
  std::memset(dist, 0x3f, sizeof dist);

  std::queue<int> queue{};
  queue.push(0);
  dist[0] = 0;

  int mxv{}, mxd{};
  while (!queue.empty())
  {
    int u = queue.front();
    queue.pop();

    visited[u] = true;
    for (const int &v : adj[u])
    {
      if (!visited[v])
      {
        dist[v] = dist[u] + 1;
        if (dist[v] > mxd)
        {
          mxd = dist[v];
          mxv = v;
        }
        queue.push(v);
      }
    }
  }

  int mxvb{}, mxbd{};
  std::memset(visited, false, sizeof visited);
  dista[mxv] = 0;
  queue.emplace(mxv);
  while (!queue.empty())
  {
    int u = queue.front();
    queue.pop();

    visited[u] = true;
    for (const int &v : adj[u])
    {
      if (!visited[v])
      {
        dista[v] = dista[u] + 1;
        if (dista[v] > mxbd)
        {
          mxvb = v;
          mxbd = dista[v];
        }
        queue.push(v);
      }
    }
  }

  std::memset(visited, false, sizeof visited);
  distb[mxvb] = 0;
  queue.emplace(mxvb);
  while (!queue.empty())
  {
    int u = queue.front();
    queue.pop();

    visited[u] = true;
    for (const int &v : adj[u])
    {
      if (!visited[v])
      {
        distb[v] = distb[u] + 1;
        queue.push(v);
      }
    }
  }

  for (int i = 0; i < n; i++)
    std::cout << std::max(dista[i], distb[i]) << " ";

  std::cout << "\n";
}

} // namespace _TreeDistancesI

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
    _TreeDistancesI::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
