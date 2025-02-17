#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_set>

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

constexpr std::size_t _ = 200000;
u32 ID[_];

struct HasherFunctor {

private:
  static std::uint64_t randomAddress() {
    char *p = new char;
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
  template <typename T> std::uint64_t operator()(T x) const {
    static const std::uint64_t FIXED_RANDOM =
        splitmix64(std::chrono::steady_clock::now().time_since_epoch().count() *
                   (randomAddress() | 1));
    return sizeof(x) <= 4 ? hash32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix64(x ^ FIXED_RANDOM);
  }
};

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  std::size_t n;
  std::cin >> n;

  for (std::size_t i = 0; i < n; i++)
    std::cin >> ID[i];

  std::unordered_set<u32, ::HasherFunctor> unique{};

  std::size_t bestSize = 1U, l = 0, r = 0;
  while (r != n) {
    u32 currentID = ID[r];
    if (unique.contains(currentID)) {
      bestSize = std::max(bestSize, r - l);
      while (l < r) {
        u32 checkID = ID[l++];
        if (checkID == currentID)
          break;
        else
          unique.erase(checkID);
      }
    } else
      unique.insert(currentID);
    r++;
  }

  std::cout << std::max(bestSize, r - l) << "\n";

  return 0;
}
