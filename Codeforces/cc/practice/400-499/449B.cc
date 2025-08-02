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

namespace _449B
{

auto run() -> void
{
  int n, m, k;
  std::cin >> n >> m >> k;

  std::vector<std::pair<int, int>> adj[n];
  std::vector<std::tuple<int, int, int>> edges, del{};
  for (int i = 0; i < m; i++)
  {
    int u, v, x;
    std::cin >> u >> v >> x;
    adj[u - 1].emplace_back(v - 1, x);
    adj[v - 1].emplace_back(u - 1, x);
    edges.emplace_back(u - 1, v - 1, x);
  }

  for (int i = 0; i < k; i++)
  {
    int s, y;
    std::cin >> s >> y;
    adj[0].emplace_back(s - 1, y);
    adj[s - 1].emplace_back(0, y);
    edges.emplace_back(0, s - 1, y);
    del.emplace_back(0, s - 1, y);
  }

  bool processed[n];
  std::memset(processed, false, sizeof processed);

  int dist1[n];
  std::memset(dist1, 0x3f, sizeof dist1);
  dist1[0] = 0;

  std::priority_queue<std::pair<int, int>> queue{};
  queue.emplace(0, 0);
  while (!queue.empty())
  {
    int a = queue.top().second;
    queue.pop();

    if (processed[a])
      continue;

    processed[a] = true;
    for (const auto &[b, w] : adj[a])
      if (dist1[b] > dist1[a] + w)
      {
        dist1[b] = dist1[a] + w;
        queue.emplace(-dist1[b], b);
      }
  }

  std::vector<std::pair<int, int>> new_adj[n];
  int indegree[n];
  for (const auto &[u, v, w] : edges)
    if (dist1[u] + w == dist1[v])
    {
      new_adj[u].emplace_back(v, w);
      new_adj[v].emplace_back(u, w);
      indegree[v] += 1;
    }

  int cnt{};
  for (const auto &[u, v, w] : del)
  {
    if (dist1[v] < w)
      cnt += 1;
    else if (indegree[v] > 1)
    {
      cnt += 1;
      indegree[v] -= 1;
    }
  }

  std::cout << cnt << "\n";
}

} // namespace _449B

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
    _449B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
