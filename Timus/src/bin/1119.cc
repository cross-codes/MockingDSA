#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <bitset>
#include <cassert>
#include <climits>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <queue>
#include <set>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1119
{

const double DIAG = std::sqrt(2) * 100.0;

auto run() -> void
{
  int N, M;
  std::cin >> N >> M;

  int K;
  std::cin >> K;

  auto get_idx = [&N](int y, int x) -> int { return (N + 1) * y + x; };

  std::set<std::pair<int, int>> diag{};
  for (int i = 0; i < K; i++)
  {
    int x, y;
    std::cin >> x >> y;

    diag.emplace(y, x);
  }

  double dist1[(N + 1) * (M + 1)];
  std::fill(dist1, dist1 + ((N + 1) * (M + 1)), INT_MAX);

  std::bitset<1002001> processed{};
  std::priority_queue<std::pair<double, std::pair<int, int>>> queue{};

  queue.emplace(0.00, std::make_pair(0, 0));
  dist1[0] = 0.00;
  while (!queue.empty())
  {
    auto [y, x] = queue.top().second;
    int a       = get_idx(y, x);
    queue.pop();

    if (processed[a])
      continue;

    processed[get_idx(y, x)] = true;

    if (y + 1 <= M)
    {
      int b = get_idx(y + 1, x);
      if (dist1[b] > dist1[a] + 100.0)
      {
        dist1[b] = dist1[a] + 100.0;
        queue.emplace(-dist1[b], std::make_pair(y + 1, x));
      }
    }

    if (x + 1 <= N)
    {
      int b = get_idx(y, x + 1);
      if (dist1[b] > dist1[a] + 100.0)
      {
        dist1[b] = dist1[a] + 100.0;
        queue.emplace(-dist1[b], std::make_pair(y, x + 1));
      }
    }

    auto it = diag.find({y + 1, x + 1});
    if (it != diag.end())
    {
      int b = get_idx(y + 1, x + 1);
      if (dist1[b] > dist1[a] + DIAG)
      {
        dist1[b] = dist1[a] + DIAG;
        queue.emplace(-dist1[b], std::make_pair(y + 1, x + 1));
      }
    }
  }

  std::cout << std::round(dist1[get_idx(M, N)]) << "\n";
}

} // namespace _1119

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
    _1119::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
