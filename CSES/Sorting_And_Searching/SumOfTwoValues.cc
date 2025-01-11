#include <chrono>
#include <cstdint>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <iostream>

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

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

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n;
  std::cin >> n;

  int x;
  std::cin >> x;

  __gnu_pbds::gp_hash_table<int, size_t, ::HasherFunctor> map{};
  for (size_t i = 1; i <= n; i++) {
    int num;
    std::cin >> num;

    auto it = map.find(x - num);
    if (it != map.end()) {
      std::cout << i << " " << it->second << "\n";
      return 0;
    } else
      map[num] = i;
  }

  std::cout << "IMPOSSIBLE\n";

  return 0;
}
