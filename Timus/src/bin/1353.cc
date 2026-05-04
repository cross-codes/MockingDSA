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

namespace _1353
{

auto run() -> void
{
  int S;
  std::cin >> S;

  const std::string N = "1000000000";

  std::map<std::array<int, 3>, int64_t> lookup{};
  auto call = [&S, &N, &lookup](auto &&call, int i, bool equal,
                                int sum) -> int64_t {
    if (i == 10)
      return sum == S;

    std::array<int, 3> params = {i, equal, sum};
    auto it                   = lookup.find(params);
    if (it != lookup.end())
      return it->second;

    int64_t res{};
    for (int d = 0; d < 10; d++)
    {
      if (equal && d > N[i] - '0')
        break;

      res += call(call, i + 1, equal && (d == N[i] - '0'), sum + d);
    }

    return lookup[params] = res;
  };

  std::cout << call(call, 0, true, 0) << "\n";
}

} // namespace _1353

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
    _1353::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
