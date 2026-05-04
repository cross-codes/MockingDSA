#include <algorithm> // IWYU pragma: keep
#include <array>     // IWYU pragma: keep
#include <bit>       // IWYU pragma: keep
#include <cassert>
#include <chrono>
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

namespace _1904C
{

struct HasherFunctor
{
private:
  static std::uint64_t randomAddress()
  {
    char *p = new char;
    delete p;
    return std::uint64_t(p);
  }

  static std::uint32_t hash32(std::uint32_t x)
  {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static std::uint64_t splitmix64(std::uint64_t x)
  {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> std::uint64_t operator()(T x) const
  {
    static const std::uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

auto run() -> void
{
  int n, k;
  std::cin >> n >> k;

  std::vector<int64_t> a(n);
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  if (k >= 3)
    std::cout << "0\n";
  else
  {
    if (k == 1)
    {
      int64_t mn{INT64_MAX};
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
          mn = std::min(mn, std::abs(a[i] - a[j]));

      mn = std::min(mn, *std::min_element(a.begin(), a.end()));

      std::cout << mn << "\n";
    }
    else
    {
      int64_t min1{INT64_MAX};
      std::unordered_set<int64_t, HasherFunctor> diff{};
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
          diff.insert(std::abs(a[i] - a[j]));
          min1 = std::min(std::abs(a[i] - a[j]), min1);
        }

      // mn of all elements
      // mndiff
      // mn of all diff + a
      std::sort(a.begin(), a.end());
      int64_t res = std::min(a[0], min1);

      for (int64_t e : diff)
      {
        auto it = std::lower_bound(a.begin(), a.end(), e);
        res     = std::min(res, std::abs(e - *it));
        if (it != a.begin())
        {
          it  = std::prev(it);
          res = std::min(res, std::abs(e - *it));
        }
      }

      std::cout << res << "\n";
    }
  }
}

} // namespace _1904C

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
    _1904C::run();

  std::cout.flush();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
