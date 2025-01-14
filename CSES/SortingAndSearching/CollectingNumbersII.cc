#include <chrono>
#include <cstdint>
#include <iostream>
#include <unordered_map>

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

constexpr size_t _ = 200001;
u32 sequence[_];

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  size_t n, m;
  std::cin >> n >> m;

  std::unordered_map<u32, size_t, ::HasherFunctor> seenNumbers{};
  u32 numberOfPasses = 1U;
  for (size_t i = 0; i < n; i++) {
    u32 num;
    std::cin >> num;
    if (seenNumbers.contains(num + 1))
      numberOfPasses++;
    seenNumbers.insert({num, i + 1}), sequence[i + 1] = num;
  }

  while (m-- > 0) {
    size_t pos1, pos2;
    std::cin >> pos1 >> pos2;

    u32 num1 = sequence[pos1], num2 = sequence[pos2];
    if (num1 > num2) {
      auto it = seenNumbers.find(num1 + 1);
      if (it != seenNumbers.end()) {
        size_t nextPos = it->second;
        if (nextPos < pos2)
          std::cout << numberOfPasses << "\n";
        else
          std::cout << numberOfPasses - 1 << "\n";
      } else
        std::cout << numberOfPasses - 1 << "\n";
    } else {
      auto it = seenNumbers.find(num2 + 1);
      if (it != seenNumbers.end()) {
        size_t nextPos = it->second;
        if (nextPos > pos1)
          std::cout << numberOfPasses << "\n";
        else
          std::cout << numberOfPasses + 1 << "\n";
      } else
        std::cout << numberOfPasses + 1 << "\n";
    }
  }

  return 0;
}
