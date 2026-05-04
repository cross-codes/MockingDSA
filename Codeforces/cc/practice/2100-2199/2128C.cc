#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <cmath>   // IWYU pragma: keep
#include <cstdint> // IWYU pragma: keep
#include <cstring> // IWYU pragma: keep
#include <deque>
#include <iostream>
#include <string> // IWYU pragma: keep
#include <unistd.h>
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

#ifdef ANTUMBRA
#include <sys/resource.h>
#endif

namespace _2128C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  std::deque<int> p{};
  for (int i = 0; i < n; i++)
  {
    int e;
    std::cin >> e;
    p.push_back(e);
  }

  bool odd{};
  while (!p.empty())
  {
    int front = p.front(), back = p.back();
    if (odd)
    {
      if (front < back)
      {
        std::cout << "L";
        p.pop_front();
      }
      else
      {
        std::cout << "R";
        p.pop_back();
      }
    }
    else
    {
      if (front < back)
      {
        std::cout << "R";
        p.pop_back();
      }
      else
      {
        std::cout << "L";
        p.pop_front();
      }
    }

    odd = !odd;
  }

  std::cout << "\n";
}

} // namespace _2128C

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
    _2128C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
