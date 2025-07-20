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
#include <unordered_map>
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _GiantPizza
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  std::unordered_map<int, std::vector<int>> adj{}, adjT{};
  for (int i = 0; i < n; i++)
  {
    char include1, include2;
    int u, v;
    std::cin >> include1 >> u >> include2 >> v;
    if (include1 == '+' && include2 == '+')
    {
      adj[-u].push_back(v);
      adj[-v].push_back(u);

      adjT[v].push_back(-u);
      adjT[u].push_back(-v);
    }
    else if (include1 == '+' && include2 == '-')
    {
      adj[-u].push_back(-v);
      adj[v].push_back(u);

      adjT[-v].push_back(-u);
      adjT[u].push_back(v);
    }
    else if (include1 == '-' && include2 == '+')
    {
      adj[u].push_back(v);
      adj[-v].push_back(-u);

      adjT[v].push_back(u);
      adjT[-u].push_back(-v);
    }
    else
    {
      adj[u].push_back(-v);
      adj[v].push_back(-u);

      adjT[-v].push_back(u);
      adjT[-u].push_back(v);
    }
  }

  std::unordered_set<int> visited{};
  std::vector<int> order{};

  auto dfs = [&visited, &order, &adj](auto &&dfs, int u) -> void {
    visited.insert(u);
    for (const int &v : adj[u])
      if (!visited.contains(v))
        dfs(dfs, v);

    order.push_back(u);
  };

  for (int i = 1; i <= m; i++)
  {
    if (!visited.contains(i))
      dfs(dfs, i);
    if (!visited.contains(-i))
      dfs(dfs, -i);
  }

  std::reverse(order.begin(), order.end());

  std::unordered_map<int, int> components{};
  std::unordered_set<int> visitedT{};
  auto dfsR = [&visitedT, &components, &adjT](auto &&dfsR, int u,
                                              int cc) -> void {
    visitedT.insert(u);
    components[u] = cc;
    for (const int &v : adjT[u])
      if (!visitedT.contains(v))
        dfsR(dfsR, v, cc);
  };

  int cc{};
  for (int u : order)
    if (!visitedT.contains(u))
    {
      dfsR(dfsR, u, cc);
      cc += 1;
    }

  std::vector<char> res{};
  for (int i = 1; i <= m; i++)
  {
    assert(components.contains(i));
    if (components[i] == components[-i])
    {
      std::cout << "IMPOSSIBLE\n";
      return;
    }

    if (components[i] < components[-i])
      res.push_back('-');
    else
      res.push_back('+');
  }

  for (char c : res)
    std::cout << c << " ";

  std::cout << "\n";
}

} // namespace _GiantPizza

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
    _GiantPizza::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
