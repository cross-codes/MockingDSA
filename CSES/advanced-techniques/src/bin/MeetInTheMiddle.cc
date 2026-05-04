#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <unordered_map>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _MeetInTheMiddle
{

auto run() -> void
{
  int n, x;
  std::cin >> n >> x;

  int al = n >> 1, bl = n - (n >> 1);

  int a[al], b[bl];
  for (int i = 0; i < al; i++)
    std::cin >> a[i];

  for (int i = 0; i < bl; i++)
    std::cin >> b[i];

  std::unordered_map<int64_t, int> sa{};
  sa.reserve(1 << al);

  for (int i = 0; i < (1 << al); i++)
  {
    int64_t suma{};
    for (int j = 0; j < al; j++)
      if (i & (1 << j))
        suma += a[j];

    sa[suma] += 1;
  }

  int64_t res{};
  for (int i = 0; i < (1 << bl); i++)
  {
    int64_t sumb{};
    for (int j = 0; j < bl; j++)
      if (i & (1 << j))
        sumb += b[j];

    res += sa[x - sumb];
  }

  std::cout << res << "\n";
}

} // namespace _MeetInTheMiddle

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
    _MeetInTheMiddle::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
