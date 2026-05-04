#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <cassert>
#include <cstring>
#include <iostream>
#include <string>  // IWYU pragma: keep
#include <utility> // IWYU pragma: keep
#include <vector>  // IWYU pragma: keep

namespace _411A
{

auto run() -> void
{
  std::string p;
  std::cin >> p;

  size_t l;
  std::cin >> l;

  if (p.length() >= l)
    std::cout << "Yes\n";
  else
    std::cout << "No\n";
}

} // namespace _411A

int main()
{
#ifdef ANTUMBRA

  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }

#endif
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int t{1};
  while (t-- > 0)
    _411A::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
