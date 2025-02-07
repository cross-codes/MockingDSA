#include <bits/stdc++.h>

#ifdef CROSS
#include "util/Debug.hh"
#else
#define dbg(...) 249
#endif

using usize = size_t;
using ssize = ptrdiff_t;

using i64 = int64_t;
using u64 = uint64_t;
using u32 = uint32_t;
using u128 = unsigned __int128;

struct Algebra {

  /*
   * Author: Akshaj Rao (cross-codes)
   */

private:
  Algebra();
  inline static const double EPSILON_ = 1E-6;
  inline static const int SIEVE_30_ =
      ~((1 << 1) | (1 << 7) | (1 << 11) | (1 << 13) | (1 << 17) | (1 << 19) |
        (1 << 23) | (1 << 29));
  inline static const int64_t FLOOR_SQRT_MAX_ = 3037000499LL;

  inline static const std::vector<std::vector<int64_t>> millerRabinBaseSets = {
      {291830, 126401071349994536LL},
      {885594168, 725270293939359937LL, 3569819667048198375LL},
      {273919523040LL, 15, 7363882082LL, 992620450144556LL},
      {47636622961200LL, 2, 2570940, 211991001, 3749873356LL},
      {7999252175582850LL, 2, 4130806001517LL, 149795463772692060LL,
       186635894390467037LL, 3967304179347715805LL},
      {585226005592931976LL, 2, 123635709730000LL, 9233062284813009LL,
       43835965440333360LL, 761179012939631437LL, 1263739024124850375LL},
      {INT64_MAX, 2, 325, 9375, 28178, 450775, 9780504, 1795265022}};

  inline static int64_t flip(int64_t a) { return a ^ INT64_MIN; }
  inline static int compare(int64_t a, int64_t b) {
    int64_t flippedA = flip(a), flippedB = flip(b);

    if (flippedA < flippedB)
      return -1;
    else if (flippedA > flippedB)
      return 1;
    else
      return 0;
  }

  inline static int64_t smallMulMod(int64_t a, int64_t b, int64_t m) {
    return (a * b) % m;
  }

  inline static int64_t smallSquareMod(int64_t a, int64_t m) {
    return (a * a) % m;
  }

  inline static int64_t smallPowMod(int64_t a, int64_t p, int64_t m) {
    int64_t res = 1;
    for (; p != 0; p >>= 1) {
      if ((p & 1) != 0) {
        res = smallMulMod(res, a, m);
      }
      a = smallSquareMod(a, m);
    }
    return res;
  }

  inline static int64_t largePlusMod(int64_t a, int64_t b, int64_t m) {
    return (a >= m - b) ? (a + b - m) : (a + b);
  }

  inline static int64_t largeTimes2ToThe32Mod(int64_t a, int64_t m) {
    int remainingPowersOf2 = 32;
    do {
      int shift = std::min(remainingPowersOf2, __builtin_clzll(a));
      a = remainder(a << shift, m);
      remainingPowersOf2 -= shift;
    } while (remainingPowersOf2 > 0);
    return a;
  }

  inline static int64_t largeMulMod(int64_t a, int64_t b, int64_t m) {
    int64_t aHi = a >> 32;
    int64_t bHi = b >> 32;
    int64_t aLo = a & 0xFFFFFFFFLL;
    int64_t bLo = b & 0xFFFFFFFFLL;
    int64_t result = largeTimes2ToThe32Mod(aHi * bHi, m);
    result += aHi * bLo;
    if (result < 0) {
      result = remainder(result, m);
    }
    result += aLo * bHi;
    result = largeTimes2ToThe32Mod(result, m);
    return largePlusMod(result, remainder(aLo * bLo, m), m);
  }

  inline static int64_t largeSquareMod(int64_t a, int64_t m) {
    int64_t aHi = a >> 32;
    int64_t aLo = a & 0xFFFFFFFFLL;
    int64_t result = largeTimes2ToThe32Mod(aHi * aHi /* < 2^62 */, m);
    int64_t hiLo = aHi * aLo * 2;
    if (hiLo < 0) {
      hiLo = remainder(hiLo, m);
    }
    result += hiLo;
    result = largeTimes2ToThe32Mod(result, m);
    return largePlusMod(result, remainder(aLo * aLo, m), m);
  }

  inline static int64_t largePowMod(int64_t a, int64_t p, int64_t m) {
    int64_t res = 1;
    for (; p != 0; p >>= 1) {
      if (p & 1)
        res = largeMulMod(res, a, m);
      a = largeSquareMod(a, m);
    }

    return res;
  }

  inline static bool testWitness(int64_t base, int64_t n) {
    int r = __builtin_ctzll(n - 1);
    int64_t d = (n - 1) >> r;
    base %= n;
    if (base == 0)
      return true;

    if (n <= FLOOR_SQRT_MAX_) {
      int64_t a = smallPowMod(base, d, n);
      if (a == 1)
        return true;
      int j = 0;
      while (a != n - 1) {
        if (++j == r)
          return false;
        a = smallSquareMod(a, n);
      }

      return true;
    } else {
      int64_t a = largePowMod(base, d, n);
      if (a == 1)
        return true;
      int j = 0;
      while (a != n - 1) {
        if (++j == r)
          return false;
        a = largeSquareMod(a, n);
      }

      return true;
    }
  }

public:
  inline static int modPow(int n, int p, int m) {
    int64_t result = 1;
    for (int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m) {
      if (i & p)
        result = result * j % m;
    }

    return static_cast<int>(result);
  }

  inline static int modInverse(int n, int p) { return modPow(n, p - 2, p); }

  inline static int log2(int64_t n) { return 63 - __builtin_clzll(n); }
  inline static int ceilLog2(int64_t n) { return 64 - __builtin_clzll(n); }
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
      size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
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

  inline static int64_t remainder(int64_t dividend, int64_t divisor) {
    if (divisor < 0) {
      if (compare(dividend, divisor) < 0) {
        return dividend;
      } else {
        return dividend - divisor;
      }
    }

    if (dividend >= 0) {
      return dividend % divisor;
    }
    int64_t quotient = ((dividend >> 1) / divisor) << 1;
    int64_t rem = dividend - quotient * divisor;
    return rem - (compare(rem, divisor) >= 0 ? divisor : 0);
  }

  inline static bool isPrime(int64_t n) {
    if (n < 2)
      return false;

    if (n < 66) {
      int64_t mask = (1LL << (2 - 2)) | (1LL << (3 - 2)) | (1LL << (5 - 2)) |
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

    for (std::vector<int64_t> baseSet : millerRabinBaseSets) {
      if (n <= baseSet[0]) {
        for (size_t i = 1; i < baseSet.size(); i++) {
          if (!testWitness(baseSet[i], n))
            return false;
        }
      }

      return true;
    }

    throw new std::runtime_error("Assertion failed");
  }
};

auto run() -> void {
  i64 n;
  std::cin >> n;
  bool found = false;
  if (n & 1) {
    i64 bridge = n;
    if (Algebra::isPrime(bridge + 2LL)) {
      for (i64 i = n - 1LL; i > 2LL; i -= 2LL) {
        if (!Algebra::isPrime(bridge + i)) {
          for (i64 j = 1LL; j <= n; j += 2LL)
            std::print("{} ", j);
          std::print("{} ", i);
          for (i64 j = 2LL; j <= n - 1LL; j += 2LL) {
            if (j == i)
              continue;
            std::print("{} ", j);
          }
          found = true;
          break;
        }
      }
    } else {
      for (i64 i = 1LL; i <= n; i += 2LL)
        std::print("{} ", i);
      for (i64 i = 2LL; i <= n - 1LL; i += 2LL)
        std::print("{}{}", i, (i == n - 1LL) ? "" : " ");
      found = true;
    }
  } else {
    i64 bridge = n - 1LL;
    if (Algebra::isPrime(bridge + 2LL)) {
      for (i64 i = n; i > 2LL; i -= 2LL) {
        if (!Algebra::isPrime(bridge + i)) {
          for (i64 j = 1LL; j <= n - 1L; j += 2LL)
            std::print("{} ", j);
          std::print("{} ", i);
          for (i64 j = 2LL; j <= n; j += 2LL) {
            if (j == i)
              continue;
            std::print("{} ", j);
          }
          found = true;
          break;
        }
      }
    } else {
      for (i64 i = 1LL; i <= n - 1LL; i += 2LL)
        std::print("{} ", i);
      for (i64 i = 2LL; i <= n; i += 2LL)
        std::print("{}{}", i, (i == n) ? "" : " ");
      found = true;
    }
  }

  if (!found)
    std::print("{}", -1);

  std::print("{}", "\n");
}

int main() {
#ifdef CROSS
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::println(stderr, "{}", "Input file not found");
    __builtin_trap();
  }
#else
  std::cin.tie(nullptr)->sync_with_stdio(false);
#endif

  int t;
  std::cin >> t;

  while (t-- > 0)
    run();

#ifdef CROSS
  std::fclose(stdin);
#endif

  return 0;
}
