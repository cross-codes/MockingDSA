#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <set>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _2128A
{

auto run() -> void
{
  int n, c;
  std::cin >> n >> c;

  std::multiset<int64_t> a;
  for (int i = 0; i < n; i++)
  {
    int64_t x;
    std::cin >> x;
    a.insert(x);
  }

  auto rep = [&a]() -> void {
    std::multiset<int64_t> next{};
    for (int64_t e : a)
      next.insert(e << 1);

    a.swap(next);
  };

  int res{};
  while (!a.empty())
  {
    auto it = a.lower_bound(c);
    if (it == a.end())
    {
      it = std::prev(it);
      a.erase(it);
    }

    else if (*it <= c)
      a.erase(it);
    else
    {
      if (it != a.begin())
      {
        it = std::prev(it);
        a.erase(it);
      }
      else
      {
        res += 1;
        a.erase(it);
      }
    }

    rep();
  }

  std::cout << res << "\n";
}

} // namespace _2128A

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
    _2128A::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
