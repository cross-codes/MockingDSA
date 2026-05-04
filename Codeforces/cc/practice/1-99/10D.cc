#include <bits/stdc++.h>

using usize = std::size_t;
using ssize = std::ptrdiff_t;
using i64   = std::int64_t;
using u32   = std::uint32_t;
using u64   = std::uint64_t;
using u128  = unsigned __int128;

namespace _10D
{

struct Algebra
{
  /*
   * Author: github.com/cross-codes
   */

private:
  Algebra();
  constexpr inline static double EPSILON_{1E-6};
  constexpr inline static int SIEVE_30_{~((1 << 1) | (1 << 7) | (1 << 11) |
                                          (1 << 13) | (1 << 17) | (1 << 19) |
                                          (1 << 23) | (1 << 29))};
  constexpr inline static std::int64_t FLOOR_SQRT_MAX_{3037000499LL};
  constexpr inline static std::uint64_t MOD{
      static_cast<std::uint64_t>(1e9 + 7)};

  inline static const std::vector<std::vector<std::int64_t>>
      millerRabinBaseSets_ = {
          {291830, 126401071349994536LL},
          {885594168, 725270293939359937LL, 3569819667048198375LL},
          {273919523040LL, 15, 7363882082LL, 992620450144556LL},
          {47636622961200LL, 2, 2570940, 211991001, 3749873356LL},
          {7999252175582850LL, 2, 4130806001517LL, 149795463772692060LL,
           186635894390467037LL, 3967304179347715805LL},
          {585226005592931976LL, 2, 123635709730000LL, 9233062284813009LL,
           43835965440333360LL, 761179012939631437LL, 1263739024124850375LL},
          {INT64_MAX, 2, 325, 9375, 28178, 450775, 9780504, 1795265022}};

  constexpr inline static int compare_(std::int64_t a, std::int64_t b)
  {
    std::int64_t flippedA{flip(a)}, flippedB{flip(b)};

    if (flippedA < flippedB)
      return -1;
    else if (flippedA > flippedB)
      return 1;
    else
      return 0;
  }

  constexpr inline static std::int64_t smallMulMod_(std::int64_t a,
                                                    std::int64_t b,
                                                    std::int64_t m)
  {
    return (a * b) % m;
  }

  constexpr inline static std::int64_t smallSquareMod_(std::int64_t a,
                                                       std::int64_t m)
  {
    return (a * a) % m;
  }

  constexpr inline static std::int64_t smallPowMod_(std::int64_t a,
                                                    std::int64_t p,
                                                    std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if ((p & 1) != 0)
      {
        res = smallMulMod_(res, a, m);
      }
      a = smallSquareMod_(a, m);
    }
    return res;
  }

  constexpr inline static std::int64_t largePlusMod_(std::int64_t a,
                                                     std::int64_t b,
                                                     std::int64_t m)
  {
    return (a >= m - b) ? (a + b - m) : (a + b);
  }

  constexpr inline static std::int64_t largeTimes2ToThe32Mod_(std::int64_t a,
                                                              std::int64_t m)
  {
    int remainingPowersOf2{32};
    do
    {
      int shift{std::min(remainingPowersOf2, __builtin_clzll(a))};
      a = remainder(a << shift, m);
      remainingPowersOf2 -= shift;
    } while (remainingPowersOf2 > 0);
    return a;
  }

  constexpr inline static std::int64_t largeMulMod_(std::int64_t a,
                                                    std::int64_t b,
                                                    std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t bHi{b >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t bLo{b & 0xFFFFFFFFLL};
    std::int64_t result{largeTimes2ToThe32Mod_(aHi * bHi, m)};
    result += aHi * bLo;
    if (result < 0)
    {
      result = remainder(result, m);
    }
    result += aLo * bHi;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * bLo, m), m);
  }

  constexpr inline static std::int64_t largeSquareMod_(std::int64_t a,
                                                       std::int64_t m)
  {
    std::int64_t aHi{a >> 32};
    std::int64_t aLo{a & 0xFFFFFFFFLL};
    std::int64_t result{largeTimes2ToThe32Mod_(aHi * aHi, m)};
    std::int64_t hiLo{aHi * aLo * 2};
    if (hiLo < 0)
      hiLo = remainder(hiLo, m);
    result += hiLo;
    result = largeTimes2ToThe32Mod_(result, m);
    return largePlusMod_(result, remainder(aLo * aLo, m), m);
  }

  constexpr inline static std::int64_t largePowMod_(std::int64_t a,
                                                    std::int64_t p,
                                                    std::int64_t m)
  {
    std::int64_t res{1LL};
    for (; p != 0; p >>= 1)
    {
      if (p & 1)
        res = largeMulMod_(res, a, m);
      a = largeSquareMod_(a, m);
    }

    return res;
  }

  inline static bool testWitnessSmall_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = smallPowMod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = smallSquareMod_(a, n);
    }

    return true;
  }

  inline static bool testWitnessLarge_(std::int64_t base, std::int64_t n)
  {
    int r{__builtin_ctzll(n - 1)};
    std::int64_t d{(n - 1) >> r};
    base %= n;
    if (base == 0)
      return true;

    std::int64_t a = largePowMod_(base, d, n);
    if (a == 1)
      return true;
    int j{};
    while (a != n - 1)
    {
      if (++j == r)
        return false;
      a = largeSquareMod_(a, n);
    }

    return true;
  }

  constexpr inline static auto exGCD_(int a, int b, int &x, int &y) -> int
  {
    if (b == 0)
    {
      x = 1;
      y = 0;
      return a;
    }

    int x1, y1;
    int d = exGCD_(b, a % b, x1, y1);
    x     = y1;
    y     = x1 - y1 * (a / b);
    return d;
  }

public:
  constexpr inline static std::int64_t flip(std::int64_t a)
  {
    return a ^ INT64_MIN;
  }

  constexpr inline static int mulMod(int a, int b, int m)
  {
    return static_cast<int>(smallMulMod_(a, b, m));
  }

  constexpr inline static int modPow(int n, int p, int m)
  {
    std::int64_t result{1LL};
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
    {
      if (i & p)
        result = result * j % m;
    }

    return static_cast<int>(result);
  }

  constexpr inline static int coprimeModInv(int n, int m)
  {
    return modPow(n, m - 2, m);
  }

  inline static int log2(std::int64_t n)
  {
    return (n == 0) ? 0 : 63 - __builtin_clzll(n);
  }

  constexpr inline static int ceilLog2(std::int64_t n)
  {
    return (n == 1) ? 1 : 64 - __builtin_clzll(n - 1);
  }

  constexpr inline static bool equal(double a, double b)
  {
    return std::abs(a - b) < EPSILON_;
  }

  constexpr inline static bool equal0(double a)
  {
    return std::abs(a) < EPSILON_;
  }

  static std::unique_ptr<double[]> solveLinear(double a, double b, double c,
                                               double d, double e, double f)
  {
    double D{a * e - b * d};
    double Dx{c * e - b * f};
    double Dy{a * f - c * d};

    if (equal0(D))
    {
      std::size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
      std::unique_ptr<double[]> result(new double[size]);
      std::memset(result.get(), 0x00, sizeof(int) * size);
      return result;
    }
    else
    {
      std::unique_ptr<double[]> result(new double[2]);
      result[0] = Dx / D, result[1] = Dy / D;
      return result;
    }
  }

  inline static std::unique_ptr<double[]> solveQuadratic(double a, double b,
                                                         double c)
  {
    double delta{b * b - 4 * a * c};
    if (equal0(delta))
    {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = -b / (a * 2);
      return result;
    }
    else if (delta < 0)
    {
      std::unique_ptr<double[]> result(new double[1]);
      result[0] = 0;
      return 0;
    }
    else
    {
      double a2{a * 2};
      double x{(-b / a2)};
      double y{std::sqrt(delta) / a2};

      std::unique_ptr<double[]> result(new double[2]);
      result[0] = x + y, result[1] = x - y;

      return result;
    }
  }

  constexpr inline static std::int64_t remainder(std::int64_t dividend,
                                                 std::int64_t divisor)
  {
    if (divisor < 0)
    {
      if (compare_(dividend, divisor) < 0)
        return dividend;
      else
        return dividend - divisor;
    }

    if (dividend >= 0)
      return dividend % divisor;

    std::int64_t quotient{((dividend >> 1) / divisor) << 1};
    std::int64_t rem{dividend - quotient * divisor};
    return rem - (compare_(rem, divisor) >= 0 ? divisor : 0);
  }

  inline static bool isPrime(std::int64_t n)
  {
    if (n < 2)
      return false;

    if (n < 66)
    {
      constexpr std::int64_t mask{
          (1LL << (2 - 2)) | (1LL << (3 - 2)) | (1LL << (5 - 2)) |
          (1LL << (7 - 2)) | (1LL << (11 - 2)) | (1LL << (13 - 2)) |
          (1LL << (17 - 2)) | (1LL << (19 - 2)) | (1LL << (23 - 2)) |
          (1LL << (29 - 2)) | (1LL << (31 - 2)) | (1LL << (37 - 2)) |
          (1LL << (41 - 2)) | (1LL << (43 - 2)) | (1LL << (47 - 2)) |
          (1LL << (53 - 2)) | (1LL << (59 - 2)) | (1LL << (61 - 2))};
      return ((mask >> (static_cast<int>(n) - 2)) & 1) != 0;
    }

    if (SIEVE_30_ & (1 << (n % 30)))
      return false;

    if (n % 7 == 0 || n % 11 == 0 || n % 13 == 0)
      return false;

    if (n < 17 * 17)
      return true;

    for (std::vector<std::int64_t> baseSet : millerRabinBaseSets_)
    {
      if (n <= baseSet[0])
      {
        bool small = n <= FLOOR_SQRT_MAX_;
        if (small)
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!testWitnessSmall_(baseSet[i], n))
              return false;
          }
        }
        else
        {
          for (std::size_t i = 1; i < baseSet.size(); i++)
          {
            if (!testWitnessLarge_(baseSet[i], n))
              return false;
          }
        }
      }

      return true;
    }

    throw new std::runtime_error("Assertion failed");
  }

  constexpr inline static std::uint64_t fibonnaciNumber(
      std::uint64_t n, std::uint64_t modulus = MOD)
  {
    if (n == 1)
      return 1ULL;

    std::uint64_t a{1U}, b{0U}, p{0U}, q{1U};
    std::uint64_t aq, qq;
    while (n > 0)
    {
      if (n & 1)
      {
        aq = (a * q) % modulus;
        a  = ((((b * q) % modulus + aq) % modulus) + (a * p) % modulus) %
            modulus;
        b = ((b * p) % modulus + aq) % modulus;
        n--;
      }
      else
      {
        qq = (q * q) % modulus;
        q  = ((2 * p * q) % modulus + qq) % modulus;
        p  = ((p * p) % modulus + qq) % modulus;
        n /= 2;
      }
    }

    return b % modulus;
  }

  constexpr inline static auto solveDiophantine(int a, int b, int c, int &x,
                                                int &y, int &g) -> bool
  {
    g = exGCD_(std::abs(a), std::abs(b), x, y);
    if (c % g)
      return false;

    x *= c / g;
    y *= c / g;
    if (a < 0)
      x = -x;
    if (b < 0)
      y = -y;

    return true;
  }
};

template <typename T> struct SegmentTree
{
  /*
   * Author: github.com/cross-codes
   */

private:
  std::size_t offset_;
  std::unique_ptr<T[]> tree_;

  std::function<T(const T &, const T &)> function_;
  T defaultValue_;

public:
  SegmentTree(const std::unique_ptr<T[]> &array, std::size_t n, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceilLog2(n)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(&array[0], &array[n], &tree_[offset_]);

    std::size_t i = offset_;
    while (i != 1)
    {
      std::size_t j = i;
      while (j < i << 1)
      {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  template <std::size_t N>
  SegmentTree(const std::array<T, N> &array, T defaultValue,
              std::function<T(const T &, const T &)> function)
      : offset_(1LL << Algebra::ceilLog2(N)),
        tree_(std::make_unique<T[]>(offset_ << 1)), function_(function),
        defaultValue_(defaultValue)
  {
    std::copy(array.begin(), array.end(), &tree_[offset_]);

    std::size_t i = offset_;
    while (i != 1)
    {
      std::size_t j = i;
      while (j < i << 1)
      {
        tree_[j >> 1] = function_(tree_[j], tree_[j + 1]);
        j += 2;
      }
      i >>= 1;
    }
  }

  void setAtIndex(std::size_t index, T value)
  {
    index += offset_;
    tree_[index] = value;

    while (index != 1)
    {
      tree_[index >> 1] = function_(tree_[index], tree_[index ^ 1]);
      index >>= 1;
    }
  }

  T queryRange(std::size_t fromIdx, std::size_t pastEndIdx)
  {
    fromIdx += offset_, pastEndIdx += offset_;

    T result{defaultValue_};
    while (fromIdx < pastEndIdx)
    {
      if (fromIdx & 1)
        result = function_(result, tree_[fromIdx++]);
      if (pastEndIdx & 1)
        result = function_(result, tree_[--pastEndIdx]);

      fromIdx >>= 1, pastEndIdx >>= 1;
    }

    return result;
  }
};

template <typename T> struct IndexCompress
{
private:
  std::vector<T> compressedValues;

public:
  explicit IndexCompress(std::vector<T> &&vec)
      : compressedValues(std::move(vec))
  {
    std::ranges::sort(compressedValues);
    compressedValues.erase(
        std::unique(compressedValues.begin(), compressedValues.end()),
        compressedValues.end());
  }

  std::size_t getCompressedIndex(T value)
  {
    return std::lower_bound(compressedValues.begin(), compressedValues.end(),
                            value) -
           compressedValues.begin();
  }

  std::size_t getMaxRange()
  {
    return compressedValues.size() - 1;
  }
};

auto run() -> void
{
  usize n, m;
  std::cin >> n;

  std::unordered_set<int> a{};
  for (usize i = 0UZ; i < n; i++)
  {
    int num;
    std::cin >> num;
    a.insert(num);
  }

  std::cin >> m;
  std::vector<int> b{};
  for (usize i = 0UZ; i < m; i++)
  {
    int num;
    std::cin >> num;
    if (a.contains(num))
      b.push_back(num);
  }

  IndexCompress ic = IndexCompress<int>(std::move(b));
  usize maxRange{ic.getMaxRange() + 1};

  std::unique_ptr<int[]> empty(new int[maxRange]);
  std::memset(empty.get(), 0x00, sizeof(int) * maxRange);

  auto MAX_SELECT = [&](const int &a, const int &b) { return std::max(a, b); };
  SegmentTree segmentTree = SegmentTree<int>(empty, maxRange, 0, MAX_SELECT);

  std::unique_ptr<int[]> d(new int[b.size()]);
  d[0] = 1;
  segmentTree.setAtIndex(ic.getCompressedIndex(b[0]), d[0]);

  for (usize i = 1UZ; i < b.size(); i++)
  {
    d[i] =
        std::max(1, segmentTree.queryRange(0, ic.getCompressedIndex(b[i])) + 1);
    segmentTree.setAtIndex(ic.getCompressedIndex(b[i]), d[i]);
  }

  int maxLength{};
  for (usize i = 0UZ; i < b.size(); i++)
    maxLength = std::max(maxLength, d[i]);

  std::println("{}", maxLength);
}

} // namespace _10D

int main()
{
#ifdef ANTUMBRA
  FILE *stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr)
  {
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
    _10D::run();

#ifdef ANTUMBRA
  std::fclose(stdin);
#endif

  return 0;
}
