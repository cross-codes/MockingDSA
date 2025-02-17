#include <bits/stdc++.h>

#ifdef CROSS
#include "extras/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

namespace _2064B {

struct HasherFunctor {

private:
  static uint64_t randomAddress() {
    char *p = new char;
    delete p;
    return uint64_t(p);
  }

  static uint32_t hash32(uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static uint64_t splitmix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> uint64_t operator()(T x) const {
    static const uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

auto run() -> void {
  ssize n;
  std::cin >> n;

  std::unique_ptr<int[]> a(new int[n]);
  std::unordered_map<int, usize, HasherFunctor> freq{};

  for (ssize i = 0; i < n; i++) {
    std::cin >> a[i];
    freq[a[i]]++;
  }

  ssize lmax = 0, rmax = 0, lcur = 0, winMax = -1;
  bool inWindow = false, foundWindow = false;
  for (ssize i = 0; i < n; i++) {
    if (inWindow) {
      if (freq[a[i]] > 1) {
        if (i - lcur > winMax) {
          lmax = lcur;
          rmax = i - 1;
          winMax = i - lcur;
        }
        lcur = i;
        inWindow = false;
      }
    } else {
      if (freq[a[i]] == 1) {
        inWindow = true;
        foundWindow = true;
      }
      lcur = i;
    }
  }

  if (!foundWindow) {
    std::println("0");
  } else {
    if (n - lcur > winMax) {
      lmax = lcur;
      rmax = n - 1;
    }
    std::println("{} {}", lmax + 1, rmax + 1);
  }
}

} // namespace _2064B

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t;
  std::cin >> t;

  while (t-- > 0)
    _2064B::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
