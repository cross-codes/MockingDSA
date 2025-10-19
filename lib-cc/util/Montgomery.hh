#include <cstdint>

struct MontgomeryRep
{
public:
  std::uint64_t value;

  explicit constexpr MontgomeryRep() : value(0)
  {
  }

private:
  explicit constexpr MontgomeryRep(std::uint64_t v) : value(v)
  {
  }

  friend struct MontgomerySpace;
};

struct MontgomerySpace
{
public:
  std::uint32_t MOD, MODR;
  constexpr explicit MontgomerySpace(std::uint32_t n) : MOD(n), MODR(1)
  {
    for (int i = 0; i < 5; i++)
      MODR *= 2 - n * MODR;
  }

  auto reduce(std::uint64_t x) const noexcept -> std::uint32_t
  {
    std::uint32_t q = static_cast<std::uint32_t>(x) * MODR;
    std::uint64_t m = static_cast<std::uint64_t>(q) * MOD;
    std::uint32_t y = (x - m) >> 32;
    return x < m ? y + MOD : y;
  }

  auto reduce(MontgomeryRep x) const noexcept -> std::uint32_t
  {
    return reduce(x.value);
  }

  auto multiply(MontgomeryRep x, MontgomeryRep y) const noexcept
      -> MontgomeryRep
  {
    return MontgomeryRep(reduce(x.value * y.value));
  }

  auto transform(std::uint64_t x) const noexcept -> MontgomeryRep
  {
    return MontgomeryRep((x << 32) % MOD);
  }

  auto add(MontgomeryRep x, MontgomeryRep y) const noexcept -> MontgomeryRep
  {
    auto res = x.value + y.value;
    if (res >= MOD)
      res -= MOD;
    return MontgomeryRep(res);
  }

  auto mod_pow(MontgomeryRep base, std::uint64_t power) const noexcept
      -> MontgomeryRep
  {
    MontgomeryRep result = transform(1ULL);
    MontgomeryRep j      = base;
    for (std::uint64_t i = 1; i <= power; i <<= 1, j = multiply(j, j))
      if (i & power)
        result = multiply(result, j);

    return result;
  }

  auto mod_pow(std::uint64_t base, std::uint64_t power) const noexcept
      -> MontgomeryRep
  {
    return mod_pow(transform(base), power);
  }

  auto coprime_mod_inv(MontgomeryRep n) const noexcept -> MontgomeryRep
  {
    return mod_pow(n, MOD - 2);
  }
};
