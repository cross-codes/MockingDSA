#include <cstdint>

// Incorrect
struct Montgomery
{
public:
  std::uint64_t mod, mod_inv;

  Montgomery(std::uint64_t n) : mod(n)
  {
    mod_inv = 1;
    for (int i = 0; i < 6; i++)
      mod_inv *= 2 - n * mod_inv;
  }

  std::uint64_t reduce(__uint128_t x) const
  {
    std::uint64_t q = std::uint64_t(x) * mod_inv;
    std::uint64_t m = ((__uint128_t)q * mod) >> 64;
    return (x >> 64) + mod - m;
  }

  std::uint64_t multiply(std::uint64_t x, std::uint64_t y)
  {
    return reduce((__uint128_t)x * y);
  }

  std::uint64_t add(std::uint64_t x, std::uint64_t y) const
  {
    __uint128_t sum = (__uint128_t)x + y;
    return reduce(sum);
  }

  std::uint64_t subtract(std::uint64_t x, std::uint64_t y) const
  {
    __uint128_t sum = (__uint128_t)x - y;
    return reduce(sum);
  }
};
