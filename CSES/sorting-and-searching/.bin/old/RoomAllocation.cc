#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <map>
#include <queue>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _RoomAllocation
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::array<int, 3> events[n << 1];
  for (int i = 0, ptr = 0; i < n; i++, ptr += 2)
  {
    int s, e;
    std::cin >> s >> e;
    std::array<int, 3> start_t = {s, 1, i}, end_t = {e, -1, i};
    events[ptr]     = start_t;
    events[ptr + 1] = end_t;
  }

  auto INTERVAL_ORDER = [](const std::array<int, 3> &a,
                           const std::array<int, 3> &b) -> bool {
    int cmp = a[0] - b[0];
    if (cmp == 0)
      return a[1] > b[1];
    else
      return cmp < 0;
  };

  std::sort(events, events + (n << 1), INTERVAL_ORDER);

  std::map<int, int> rooms{};
  int cnt{1};
  std::priority_queue<int, std::vector<int>, std::greater<>> heap{};
  for (const auto &[time, type, index] : events)
  {
    if (type == 1)
    {
      if (heap.empty())
        rooms[index] = cnt++;
      else
      {
        int top = heap.top();
        heap.pop();
        rooms[index] = top;
      }
    }
    else
      heap.push(rooms[index]);
  }

  std::cout << cnt - 1 << "\n";
  for (const auto [_, e] : rooms)
    std::cout << e << " ";

  std::cout << "\n";
}

} // namespace _RoomAllocation

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
    _RoomAllocation::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
