#include <cstdint>

class BarrettReducer {
 public:
  BarrettReducer(uint64_t mod) : m_mod(mod), m_m(UINT64_C(-1) / mod) {}

  auto reduce(uint64_t a) -> uint64_t {
    uint64_t v = a - (uint64_t)((__uint128_t(m_m) * a) >> 64) * m_mod;
    return v >= m_mod ? v - m_mod : v;
  }

 private:
  uint64_t m_mod, m_m;
};
