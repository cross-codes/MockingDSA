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

namespace _1561C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  auto PAIR_ORDER = [](const std::array<int64_t, 2> &a,
                       const std::array<int64_t, 2> &b) -> bool {
    int64_t cmp = a[0] - b[0];
    if (cmp == 0)
      return a[1] < b[1];
    else
      return cmp > 0;
  };

  std::priority_queue<std::array<int64_t, 2>,
                      std::vector<std::array<int64_t, 2>>, decltype(PAIR_ORDER)>
      heap{};

  for (int i = 0; i < n; i++)
  {
    std::array<int64_t, 2> elem{};
    std::cin >> elem[1];

    for (int j = 0; j < elem[1]; j++)
    {
      int64_t a;
      std::cin >> a;
      elem[0] = std::max(elem[0], a - j);
    }

    heap.push(elem);
  }

  int64_t base_power{}, cur_power{};
  while (!heap.empty())
  {
    auto cave = heap.top();
    heap.pop();
    int64_t max = cave[0], amt = cave[1];

    if (cur_power <= max)
    {
      base_power += max - cur_power + 1;
      cur_power = max + 1;
    }

    cur_power += amt;
  }

  std::cout << base_power << "\n";
}

} // namespace _1561C

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
    _1561C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
