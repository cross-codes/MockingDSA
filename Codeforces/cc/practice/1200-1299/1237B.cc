#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <map>
#include <set>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <unordered_map>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1237B
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int a[n], b[n];
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  for (int i = 0; i < n; i++)
    std::cin >> b[i];

  std::reverse(a, a + n);
  std::reverse(b, b + n);

  std::unordered_map<int, int> idx{};
  for (int i = 0; i < n; i++)
    idx[b[i]] = i;

  int cnt{};
  std::set<int> prev{};
  for (int i = 0; i < n; i++)
  {
    int c   = idx[a[i]];
    auto it = prev.upper_bound(c);
    cnt += std::distance(it, prev.end());
    prev.erase(it, prev.end());
    prev.insert(idx[a[i]]);
  }

  std::cout << cnt << "\n";
}

} // namespace _1237B

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
    _1237B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
