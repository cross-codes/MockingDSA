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

namespace _MailDelivery
{

auto run() -> void
{
  int n, m;
  std::cin >> n >> m;

  std::multiset<int> adj[n];
  int degree[n];
  std::memset(degree, 0x00, sizeof degree);

  for (int i = 0; i < m; i++)
  {
    int a, b;
    std::cin >> a >> b;
    a -= 1;
    b -= 1;
    adj[a].insert(b);
    adj[b].insert(a);
    degree[a]++;
    degree[b]++;
  }

  for (int i = 0; i < n; ++i)
    if (degree[i] % 2 != 0)
    {
      std::cout << "IMPOSSIBLE\n";
      return;
    }

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
      adj[v].erase(adj[v].find(u));
    }
  }

  if (circuit.size() != static_cast<size_t>(m + 1))
  {
    std::cout << "IMPOSSIBLE\n";
    return;
  }

  std::reverse(circuit.begin(), circuit.end());
  for (int e : circuit)
    std::cout << 1 + e << " ";

  std::cout << "\n";
}

} // namespace _MailDelivery

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
    _MailDelivery::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
