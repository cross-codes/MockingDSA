#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <cassert>    // IWYU pragma: keep
#include <chrono>
#include <cmath>     // IWYU pragma: keep
#include <cstdint>   // IWYU pragma: keep
#include <cstring>   // IWYU pragma: keep
#include <iostream>  // IWYU pragma: keep
#include <string>    // IWYU pragma: keep
#include <unordered_set>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef AZURELIGHT
#include <sys/resource.h>
#endif

namespace _DistinctNumbers {

struct HasherFunctor {
 private:
  static std::uint64_t randomAddress() {
    char* p = new char;
    delete p;
    return std::uint64_t(p);
  }

  static std::uint32_t hash32(std::uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static std::uint64_t splitmix64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

 public:
  template <typename T>
  std::uint64_t operator()(T x) const {
    static const std::uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

auto run() -> void {
  int n;
  std::cin >> n;

  std::unordered_set<int, HasherFunctor> distinct{};
  for (int i = 0, x; i < n; i++) {
    std::cin >> x;
    distinct.insert(x);
  }

  std::cout << distinct.size() << "\n";
}

}  // namespace _DistinctNumbers

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef AZURELIGHT
  const rlim_t stack_size = 268435456;
  struct rlimit rl;

  int result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0 && rl.rlim_cur < stack_size) {
    rl.rlim_cur = stack_size;
    result      = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0)
      std::cerr << "WARN: setrlimit failed\n";
  }

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _DistinctNumbers::run();

  std::cout.flush();

#ifdef AZURELIGHT
  std::fclose(stdin);
#endif

  return 0;
}
