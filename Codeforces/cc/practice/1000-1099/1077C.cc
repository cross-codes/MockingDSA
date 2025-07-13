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

namespace _1077C
{

auto run() -> void
{
  int n;
  std::cin >> n;

  int a[n];
  int64_t sum{};
  std::unordered_map<int64_t, int> freq{};
  for (int i = 0; i < n; i++)
  {
    std::cin >> a[i];
    sum += a[i];
    freq[a[i]] += 1;
  }

  std::vector<int> idx{};
  for (int i = 0; i < n; i++)
  {
    int e        = a[i];
    int64_t left = sum - e;
    freq[e] -= 1;
    if (freq[e] == 0)
      freq.erase(e);

    if (!(left & 1) && freq.contains(left >> 1))
      idx.push_back(i + 1);

    freq[e] += 1;
  }

  std::cout << idx.size() << "\n";
  for (int e : idx)
    std::cout << e << " ";

  std::cout << "\n";
}

} // namespace _1077C

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
    _1077C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
