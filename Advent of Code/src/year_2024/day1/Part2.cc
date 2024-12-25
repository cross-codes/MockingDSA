#include "../../include/BufferedIO.hpp"
#include <chrono>
#include <cstdint>
#include <cstring>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

namespace Part2 {

using i8 = int8_t;
using i16 = int16_t;
using i32 = int32_t;
using i64 = int64_t;

using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using f32 = float;
using f64 = double;

BufferedIO::StandardInputReader in;
BufferedIO::StandardOutputWriter out;

class HasherFunctor {
private:
  static uint64_t random_address() {
    char *p = new char;
    delete p;
    return uint64_t(p);
  }

  static uint32_t hash_32(uint32_t x) {
    x += 0x9e3779b9;
    x = (x ^ (x >> 16)) * 0x85ebca6b;
    x = (x ^ (x >> 13)) * 0xc2b2ae35;
    return x ^ (x >> 16);
  }

  static uint64_t splitmix_64(uint64_t x) {
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

public:
  template <typename T> uint64_t operator()(T x) const {
    static const uint64_t FIXED_RANDOM = splitmix_64(
        std::chrono::steady_clock::now().time_since_epoch().count() *
        (random_address() | 1));
    return sizeof(x) <= 4 ? hash_32(unsigned(x ^ FIXED_RANDOM))
                          : splitmix_64(x ^ FIXED_RANDOM);
  }
};

void run() {
  __gnu_pbds::gp_hash_table<i32, i32, HasherFunctor> int_to_frequency_1{};
  __gnu_pbds::gp_hash_table<i32, i32, HasherFunctor> int_to_frequency_2{};

  i32 x, y;
  while (in.nextInt(x), in.nextInt(y)) {
    int_to_frequency_1[x] += 1;
    int_to_frequency_2[y] += 1;
  }

  i64 similarity_score = 0;
  for (const std::pair<const i32, i32> &entry : int_to_frequency_1) {
    int number = entry.first, occurences_in_first = entry.second;
    int occurences_in_second = int_to_frequency_2[number];
    similarity_score += (number * occurences_in_second) * occurences_in_first;
  }

  out << similarity_score << "\n";
}

} // namespace Part2

int32_t main() {
  Part2::run();
  return 0;
}