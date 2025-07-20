#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
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

namespace _B
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::string S;
  int cur{};
  for (int i = 0; i < n; i++)
  {
    char c;
    int64_t l;
    std::cin >> c >> l;

    if (cur + l > 100)
    {
      std::cout << "Too Long\n";
      return;
    }
    else
    {
      for (int j = 0; j < l; j++)
      {
        S += c;
      }
      cur += l;
    }
  }

  std::cout << S << "\n";
}

} // namespace _B

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
    _B::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
