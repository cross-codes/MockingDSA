#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <unordered_set>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _1846E1
{

int64_t ULIM = static_cast<int64_t>(1e6);

std::unordered_set<int64_t> possible{};
void precompute()
{
  int64_t k = 2;
  while (k * k + (k + 1) <= ULIM)
  {
    int64_t curr = k * k + (k + 1);
    int cnt{3};
    while (curr <= ULIM)
    {
      possible.insert(curr);
      curr += static_cast<int64_t>(std::pow(k, cnt));
      cnt += 1;
    }
    k += 1;
  }
}

auto run() -> void
{
  assert(possible.contains(21));
  int n;
  std::cin >> n;
  if (possible.contains(n))
    std::cout << "YES\n";
  else
    std::cout << "NO\n";
}

} // namespace _1846E1

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
  _1846E1::precompute();
  while (t-- > 0)
    _1846E1::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
