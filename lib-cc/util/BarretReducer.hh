#include <cstdint>

class BarrettReducer {
 private:
  uint64_t mod, m;

 public:
  BarrettReducer(uint64_t mod) : mod(mod), m(UINT64_C(-1) / mod) {}

  auto reduce(uint64_t a) -> uint64_t {
    uint64_t v = a - (uint64_t)((__uint128_t(m) * a) >> 64) * mod;
    return v >= mod ? v - mod : v;
  }
};
