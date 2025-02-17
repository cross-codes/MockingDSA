#include <chrono>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <unordered_map>

using usize = std::size_t;
using ssize = std::ptrdiff_t;

using i64 = std::int64_t;
using u64 = std::uint64_t;
using u32 = std::uint32_t;
using u128 = unsigned __int128;

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

  ssize n;
  i64 x;
  std::cin >> n >> x;

  std::unique_ptr<int[]> array(new int[n]);
  std::unique_ptr<i64[]> prefix(new i64[n + 1]);

  std::unordered_map<i64, u64, ::HasherFunctor> prefixIndices{};
  prefixIndices.reserve(n + 1);
  prefixIndices[0] = 1U;

  std::memset(array.get(), 0x00, sizeof(int) * n);
  std::memset(prefix.get(), 0x00, sizeof(int) * (n + 1));

  u64 cnt = 0ULL;
  for (ssize i = 1; i <= n; i++) {
    std::cin >> array[i - 1];
    prefix[i] = array[i - 1] + prefix[i - 1];

    auto it = prefixIndices.find(prefix[i] - x);
    if (it != prefixIndices.end())
      cnt += it->second;

    prefixIndices[prefix[i]]++;
  }

  std::cout << cnt << "\n";

  return 0;
}
