#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1879C
{

constexpr int MOD = 998244353;

int factorials[200001];

auto precompute()
{
  factorials[0] = 1;
  for (int i = 1; i < 200001; i++)
    factorials[i] = (static_cast<int64_t>(factorials[i - 1]) * i) % MOD;
};

auto run() -> void
{
  std::string s;
  std::cin >> s;

  int n = static_cast<int>(s.size());

  std::vector<int> lengths{};
  int cur = s[0], len = 1;
  for (int i = 1; i < n; i++)
  {
    if (s[i] != cur)
    {
      lengths.push_back(len);
      len = 1;
      cur = s[i];
    }
    else
      len += 1;
  }
  lengths.push_back(len);

  int erase = n - static_cast<int>(lengths.size());

  int ways{1};
  for (int e : lengths)
    ways = (static_cast<int64_t>(e) * ways) % MOD;

  ways = (static_cast<int64_t>(ways) * factorials[erase]) % MOD;
  std::cout << std::format("{} {}\n", erase, ways);
}

} // namespace _1879C

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
  _1879C::precompute();
  while (t-- > 0)
    _1879C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
