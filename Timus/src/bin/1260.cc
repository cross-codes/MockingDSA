#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <map>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1260
{

auto run() -> void
{
  uint64_t N;
  std::cin >> N;

  std::map<std::array<uint64_t, 3>, int64_t> lookup{};

  auto dfs = [&N, &lookup](auto &&dfs, uint64_t set, uint64_t i,
                           uint64_t prev) -> int64_t {
    if (i == N)
      return 1;

    std::array<uint64_t, 3> params = {set, i, prev};
    auto it                        = lookup.find(params);
    if (it != lookup.end())
      return lookup[params];

    int64_t res{};

    if (prev <= N - 1 && !(set & (1ULL << (prev + 1))))
    {
      uint64_t nxt = set | (1ULL << (prev + 1));
      res += dfs(dfs, nxt, i + 1, prev + 1);
    }

    if (prev <= N - 2 && !(set & (1ULL << (prev + 2))))
    {
      uint64_t nxt = set | (1ULL << (prev + 2));
      res += dfs(dfs, nxt, i + 1, prev + 2);
    }

    if (prev > 2 && !(set & (1ULL << (prev - 2))))
    {
      uint64_t nxt = set | (1ULL << (prev - 2));
      res += dfs(dfs, nxt, i + 1, prev - 2);
    }

    if (prev > 1 && !(set & (1ULL << (prev - 1))))
    {
      uint64_t nxt = set | (1ULL << (prev - 1));
      res += dfs(dfs, nxt, i + 1, prev - 1);
    }

    return lookup[params] = res;
  };

  std::cout << dfs(dfs, 2ULL, 2, 1) << "\n";
}

} // namespace _1260

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
    _1260::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
