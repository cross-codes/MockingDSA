#include <bits/stdc++.h>

#if __cplusplus >= 202302L
#define dbg(a) std::println(stderr, "{}", a);
#else
#define dbg(a) std::cerr << a << "\n";
#endif

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using u128 = unsigned __int128;

namespace _StaticRangeMinimumQueries {

struct Algebra {

  /*
   * Author: github.com/cross-codes
   */

private:
  Algebra();
  inline static constexpr double EPSILON_ = 1E-6;
  inline static constexpr int SIEVE_30_ =
      ~((1 << 1) | (1 << 7) | (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19) |
        (1 << 23) | (1 << 29));
  inline static constexpr std::int64_t FLOOR_SQRT_MAX_ = 3037000499LL;

  inline static const std::vector<std::vector<std::int64_t>>
      millerRabinBaseSets = {
          {291830, 126401071349994536LL},
          {885594168, 725270293939359937LL, 3569819667048198375LL},
          {273919523040LL, 15, 7363882082LL, 992620450144556LL},
          {47636622961200LL, 2, 2570940, 211991001, 3749873356LL},
          {7999252175582850LL, 2, 4130806001517LL, 149795463772692060LL,
           186635894390467037LL, 3967304179347715805LL},
          {585226005592931976LL, 2, 123635709730000LL, 9233062284813009LL,
           43835965440333360LL, 761179012939631437LL, 1263739024124850375LL},
          {INT64_MAX, 2, 325, 9375, 28178, 450775, 9780504, 1795265022}};

  inline static std::int64_t flip_(std::int64_t a) { return a ^ INT64_MIN; }
  inline static int compare_(std::int64_t a, std::int64_t b) {
    std::int64_t flippedA = flip_(a), flippedB = flip_(b);

    if (flippedA < flippedB)
      return -1;
    else if (flippedA > flippedB)
      return 1;
    else
      return 0;
  }

  inline static std::int64_t smallMulMod_(std::int64_t a, std::int64_t b,
                                          std::int64_t m) {
    return (a * b) % m;
  }

  inline static std::int64_t smallSquareMod_(std::int64_t a, std::int64_t m) {
    return (a * a) % m;
  }

  inline static std::int64_t smallPowMod_(std::int64_t a, std::int64_t p,
                                          std::int64_t m) {
    std::int64_t res = 1;
    for (; p != 0; p >>= 1) {
      if ((p & 1) != 0) {
        res = smallMulMod_(res, a, m);
      }
      a = smallSquareMod_(a, m);
    }
    return res;
  }

  inline static std::int64_t largePlusMod_(std::int64_t a, std::int64_t b,
                                           std::int64_t m) {
    return (a >= m - b) ? (a + b - m) : (a + b);
  }

  inline static std::int64_t largeTimes2ToThe32Mod_(std::int64_t a,
                                                    std::int64_t m) {
    int remainingPowersOf2 = 32;
    do {
      int shift = std::min(remainingPowersOf2, __builtin_clzll(a));
      a = remainder(a << shift, m);
      remainingPowersOf2 -= shift;
    } while (remainingPowersOf2 > 0);
    return a;
  }

  inline static std::int64_t largeMulMod_(std::int64_t a, std::int64_t b,
                                          std::int64_t m) {
    std::int64_t aHi = a >> 32;
    std::int64_t bHi = b >> 32;
    std::int64_t aLo = a & 0xFFFFFFFFLL;
    std::int64_t bLo = b & 0xFFFFFFFFLL;
    std::int64_t result = largeTimes2ToThe32Mod_(aHi * bHi, m);
    result += aHi * bLo;
    if (result < 0) {
      result = remainder(result, m);
    }
    result += aLo * bHi;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * bLo, m), m);
  }

  inline static std::int64_t largeSquareMod_(std::int64_t a, std::int64_t m) {
    std::int64_t aHi = a >> 32;
    std::int64_t aLo = a & 0xFFFFFFFFLL;
    std::int64_t result = largeTimes2ToThe32Mod_(aHi * aHi /* < 2^62 */, m);
    std::int64_t hiLo = aHi * aLo * 2;
    if (hiLo < 0) {
      hiLo = remainder(hiLo, m);
    }
    result += hiLo;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * aLo, m), m);
  }

  inline static std::int64_t largePowMod_(std::int64_t a, std::int64_t p,
                                          std::int64_t m) {
    std::int64_t res = 1;
    for (; p != 0; p >>= 1) {
      if (p & 1)
        res = largeMulMod_(res, a, m);
      a = largeSquareMod_(a, m);
    }

    return res;
  }

  inline static bool testWitnessSmall_(std::int64_t base, std::int64_t n) {
    int r = __builtin_ctzll(n - 1);
    std::int64_t d = (n - 1) >> r;
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = smallPowMod_(base, d, n);
    if (a == 1)
      return true;
    int j = 0;
    while (a != n - 1) {
      if (++j == r)
        return false;
      a = smallSquareMod_(a, n);
    }

    return true;
  }

  inline static bool testWitnessLarge_(std::int64_t base, std::int64_t n) {
    int r = __builtin_ctzll(n - 1);
    std::int64_t d = (n - 1) >> r;
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = largePowMod_(base, d, n);
    if (a == 1)
      return true;
    int j = 0;
    while (a != n - 1) {
      if (++j == r)
        return false;
      a = largeSquareMod_(a, n);
    }

    return true;
  }

public:
  inline static int modPow(int n, int p, int m) {
    std::int64_t result = 1;
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m) {
      if (i & p)
        result = result * j % m;
    }

    return static_cast<int>(result);
  }

  inline static int modInverse(int n, int p) { return modPow(n, p - 2, p); }

  inline static int log2(std::int64_t n) {
    return (n == 0) ? 0 : 63 - __builtin_clzll(n);
  }

  inline static int ceilLog2(std::int64_t n) {
    return (n == 0) ? 0 : 64 - __builtin_clzll(n);
  }

  inline static bool equal(double a, double b) {
    return std::abs(a - b) < EPSILON_;
  }

  inline static bool equal0(double a) { return std::abs(a) < EPSILON_; }

  static std::unique_ptr<double[]> solveLinear(double a, double b, double c,
                                               double d, double e, double f) {
    double D = a * e - b * d;
    double Dx = c * e - b * f;
    double Dy = a * f - c * d;

    if (equal0(D)) {
      std::size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
      std::unique_ptr<double[]> result(new double[size]);
      std::memset(result.get(), 0x00, sizeof(int) * size);
      return result;
    } else {
      std::unique_ptr<double[]> result(new double[2]);
      result[0] = Dx / D, result[1] = Dy / D;
      return result;
    }
  }

  static std::unique_ptr<double[]> solveQuadratic(double a, double b,
                                                  double c) {
    double delta = b * b - 4 * a * c;
    if (equal0(delta)) {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = -b / (a * 2);
      return result;
    } else if (delta < 0) {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = 0;
      return 0;
    } else {
      double a2 = a * 2;
      double x = (-b / a2);
      double y = std::sqrt(delta) / a2;

      std::unique_ptr<double[]> result(new double[2]);
      result[0] = x + y, result[1] = x - y;

      return result;
    }
  }

  inline static std::int64_t remainder(std::int64_t dividend,
                                       std::int64_t divisor) {
    if (divisor < 0) {
      if (compare_(dividend, divisor) < 0) {
        return dividend;
      } else {
        return dividend - divisor;
      }
    }

    if (dividend >= 0) {
      return dividend % divisor;
    }
    std::int64_t quotient = ((dividend >> 1) / divisor) << 1;
    std::int64_t rem = dividend - quotient * divisor;
    return rem - (compare_(rem, divisor) >= 0 ? divisor : 0);
  }

  inline static bool isPrime(std::int64_t n) {
    if (n < 2)
      return false;

    if (n < 66) {
      constexpr std::int64_t mask =
          (1LL << (2 - 2)) | (1LL << (3 - 2)) | (1LL << (5 - 2)) |
          (1LL << (7 - 2)) | (1LL << (11 - 2)) | (1LL << (13 - 2)) |
          (1LL << (17 - 2)) | (1LL << (19 - 2)) | (1LL << (23 - 2)) |
          (1LL << (29 - 2)) | (1LL << (31 - 2)) | (1LL << (37 - 2)) |
          (1LL << (41 - 2)) | (1LL << (43 - 2)) | (1LL << (47 - 2)) |
          (1LL << (53 - 2)) | (1LL << (59 - 2)) | (1LL << (61 - 2));
      return ((mask >> (static_cast<int>(n) - 2)) & 1) != 0;
    }

    if (SIEVE_30_ & (1 << (n % 30)))
      return false;

    if (n % 7 == 0 || n % 11 == 0 || n % 13 == 0)
      return false;

    if (n < 17 * 17)
      return true;

    for (std::vector<std::int64_t> baseSet : millerRabinBaseSets) {
      if (n <= baseSet[0]) {
        bool small = n <= FLOOR_SQRT_MAX_;
        if (small) {
          for (std::size_t i = 1; i < baseSet.size(); i++) {
            if (!testWitnessSmall_(baseSet[i], n))
              return false;
          }
        } else {
          for (std::size_t i = 1; i < baseSet.size(); i++) {
            if (!testWitnessLarge_(baseSet[i], n))
              return false;
          }
        }
      }

      return true;
    }

    throw new std::runtime_error("Assertion failed");
  }
};

template <typename T>
struct IdempotentSparseTable {

  /*
   * Author: github.com/cross-codes
   */

private:
  std::function<T(const T &, const T &)> function;
  std::vector<std::vector<T>> table;

public:
  IdempotentSparseTable(std::function<T(const T &, const T &)> func,
                        std::unique_ptr<T[]> &array, std::size_t n)
      : function(func) {
    std::uint32_t K = Algebra::log2(n);

    table.resize(K + 1, std::vector<T>(n));
    std::copy(&array[0], &array[n], table[0].begin());

    for (std::size_t y = 1; y < table.size(); y++) {
      for (std::size_t x = 0, k = 1 << (y - 1); x <= n - (1 << y); x++, k++) {
        table[y][x] = function(table[y - 1][x], table[y - 1][k]);
      }
    }
  }

  T queryRange(std::size_t L, std::size_t R) {
    std::size_t log2 = Algebra::log2(R - L);
    return function(table[log2][L], table[log2][R - (1 << log2)]);
  }
};

auto run() -> void {
  ssize n, q;
  std::cin >> n >> q;

  std::unique_ptr<int[]> array(new int[n]);
  for (ssize i = 0; i < n; i++)
    std::cin >> array[i];

  auto MIN_SELECT = [&](const int &a, const int &b) { return std::min(a, b); };

  auto table = IdempotentSparseTable<int>(MIN_SELECT, array, n);

  while (q-- > 0) {
    usize a, b;
    std::cin >> a >> b;
    std::cout << table.queryRange(--a, b) << "\n";
  }
}

} // namespace _StaticRangeMinimumQueries

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
#if __cplusplus >= 202302L
    std::println(stderr, "Input file not found");
#else
    std::cerr << "Input file not found\n";
#endif
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t{1};

  while (t-- > 0)
    _StaticRangeMinimumQueries::run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
