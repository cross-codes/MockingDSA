#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <set>
#include <stack>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _TeleportersPath
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  std::multiset<int> adj[n];
  int in_degree[n], out_degree[n];

  std::memset(out_degree, 0x00, sizeof out_degree);
  std::memset(in_degree, 0x00, sizeof in_degree);

  for (int i = 0; i < m; i++)
  {
    int a, b;
    std::cin >> a >> b;
    a -= 1;
    b -= 1;
    adj[a].insert(b);
    in_degree[b] += 1;
    out_degree[a] += 1;
  }

  bool possible = true;
  if (out_degree[0] - in_degree[0] != 1)
    possible = false;
  if (in_degree[n - 1] - out_degree[n - 1] != 1)
    possible = false;

  for (int i = 1; i < n - 1; ++i)
    if (in_degree[i] != out_degree[i])
    {
      possible = false;
      break;
    }

  if (!possible)
  {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  adj[n - 1].insert(0);
  out_degree[n - 1]++;
  in_degree[0]++;

  std::stack<int> current_path;
  std::vector<int> circuit;

  current_path.push(0);
  while (!current_path.empty())
  {
    int u = current_path.top();
    if (adj[u].empty())
    {
      circuit.push_back(u);
      current_path.pop();
    }
    else
    {
      int v = *adj[u].begin();
      current_path.push(v);
      adj[u].erase(adj[u].begin());
    }
  }

  if (circuit.size() != static_cast<size_t>(m + 2))
  {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  std::reverse(circuit.begin(), circuit.end());

  int split_pos{};
  for (int i = 0; i < m + 1; i++)
    if (circuit[i] == n - 1 && circuit[i + 1] == 0)
    {
      split_pos = i;
      break;
    }

  std::vector<int> final_path;
  for (int i = split_pos + 1; i < m + 1; ++i)
    final_path.push_back(circuit[i]);

  for (int i = 0; i <= split_pos; ++i)
    final_path.push_back(circuit[i]);

  for (int node : final_path)
    std::cout << 1 + node << " ";

  std::cout << "\n";
}

} // namespace _TeleportersPath

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
    _TeleportersPath::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
