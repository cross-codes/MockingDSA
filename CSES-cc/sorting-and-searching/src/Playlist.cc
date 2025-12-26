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
#include <unordered_map>
#include <utility>  // IWYU pragma: keep
#include <vector>   // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _Playlist {

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

  std::vector<int> ids(n);
  for (int i = 0; i < n; i++) {
    std::cin >> ids[i];
  }

  std::unordered_map<int, int, HasherFunctor> seen{};
  int mx{}, cur{}, p{};
  for (int r = 0; r < n; r++) {
    if (!seen.contains(ids[r])) {
      cur += 1;
    } else {
      int upto = seen[ids[r]] + 1;
      for (int l = p; l < upto; l++) {
        seen.erase(ids[l]);
      }

      p   = upto;
      cur = static_cast<int>(seen.size()) + 1;
    }

    mx = std::max(mx, cur);
    seen[ids[r]] = r;
  }

  std::cout << mx << "\n";
}

}  // namespace _Playlist

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _Playlist::run();

  std::cout.flush();

  return 0;
}
