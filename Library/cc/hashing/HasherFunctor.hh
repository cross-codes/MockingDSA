#include <chrono>
#include <cstdint>

struct HasherFunctor {
 private:
  static std::uint64_t random_address() {
    char* p = new char;
    delete p;
    return std::uint64_t(p);
  }

  static std::uint32_t hash_32(std::uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static std::uint64_t splitmix_64(std::uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

 public:
  template <typename T>
  std::uint64_t operator()(T x) const {
    static const std::uint64_t FIXED_RANDOM = splitmix_64(
        std::chrono::steady_clock::now().time_since_epoch().count() *
        (random_address() | 1));
    return sizeof(x) <= 4 ? hash_32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix_64(x ^ FIXED_RANDOM);
  }
};
