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
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::string s;
  std::cin >> s;

  uint32_t len = static_cast<uint32_t>(s.length());

  std::unordered_set<uint32_t> bad{};
  for (uint32_t i = 1; i <= len; i++)
    if (s[i - 1] == '1')
      bad.insert(i);

  bool visited[1 << 19];
  std::memset(visited, false, sizeof visited);

  std::queue<uint32_t> queue;
  queue.push(0U);
  visited[0] = true;

  while (!queue.empty())
  {
    auto curr = queue.front();
    queue.pop();

    for (int i = 0; i < n; i++)
      if (!((curr >> i) & 1))
      {
        uint32_t nxt = curr | (1 << i);
        if (!bad.contains(nxt) && !visited[nxt])
        {
          visited[nxt] = true;
          queue.push(nxt);
        }
      }
  }

  if (visited[(1 << n) - 1])
    std::cout << "Yes\n";
  else
    std::cout << "No\n";
}

} // namespace _C

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
  std::cin >> t;
  while (t-- > 0)
    _C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
