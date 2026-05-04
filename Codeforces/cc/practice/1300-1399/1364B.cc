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

namespace _1364B
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int p[n];
  for (int i = 0; i < n; i++)
    std::cin >> p[i];

  std::vector<int> subseq{};
  subseq.push_back(p[0]);
  for (int i = 1; i < n - 1; i++)
    if (p[i - 1] < p[i] && p[i] < p[i + 1])
      continue;
    else if (p[i - 1] > p[i] && p[i] > p[i + 1])
      continue;
    else
      subseq.push_back(p[i]);

  subseq.push_back(p[n - 1]);

  std::cout << subseq.size() << "\n";
  for (int e : subseq)
    std::cout << e << " ";

  std::cout << "\n";
}

} // namespace _1364B

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
    _1364B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
