#include <algorithm>      // IWYU pragma: keep
#include <array>          // IWYU pragma: keep
#include <bit>            // IWYU pragma: keep
#include <cassert>        // IWYU pragma: keep
#include <cmath>          // IWYU pragma: keep
#include <concepts>       // IWYU pragma: keep
#include <cstdint>        // IWYU pragma: keep
#include <cstring>        // IWYU pragma: keep
#include <deque>          // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <map>            // IWYU pragma: keep
#include <memory>         // IWYU pragma: keep
#include <set>            // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <utility>        // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep

#ifdef EVERMORE
#include <pthread/qos.h>
#include <sys/qos.h>
#endif

namespace _CreatingStringsII {

template <typename T>
concept Predicate = requires(T t, int64_t x) {
  { t(x) } -> std::convertible_to<bool>;
};

class Algebra {
 private:
  Algebra();
  constexpr inline static double EPSILON_{1E-6};

  constexpr inline static std::uint64_t MOD{
      static_cast<std::uint64_t>(1e9 + 7)};

  constexpr inline static auto ex_GCD_(int a, int b, int& x, int& y) -> int {
    if (b == 0) {
      x = 1;
      y = 0;
      return a;
    }

    int x1, y1;
    int d = ex_GCD_(b, a % b, x1, y1);
    x     = y1;
    y     = x1 - y1 * (a / b);
    return d;
  }

 public:
  constexpr inline static auto flip(std::int64_t a) -> std::int64_t {
    return a ^ INT64_MIN;
  }

  constexpr inline static auto mod_pow(int n, int p, int m) -> int {
    std::int64_t result{1LL};
    for (std::int64_t i = 1, j = n; i <= p; i <<= 1, j = j * j % m)
      if (i & p)
        result = result * j % m;

    return static_cast<int>(result);
  }

  constexpr inline static auto coprime_mod_inv(int n, int m) -> int {
    return mod_pow(n, m - 2, m);
  }

  inline static auto log2(std::uint64_t n) -> std::uint64_t {
    return std::bit_width(n) - 1;
  }

  constexpr inline static auto ceil_log2(std::uint64_t n) -> int {
    if (n <= 1)
      return 0;
    return std::bit_width(n - 1);
  }

  constexpr inline static auto is_prime(int64_t n) -> bool {
    if (n < 2)
      return false;

    int64_t x{2LL};
    while (x * x <= n) {
      if (n % x == 0)
        return false;
      x++;
    }

    return true;
  }

  constexpr inline static auto equal(double a, double b) -> bool {
    return std::abs(a - b) < EPSILON_;
  }

  constexpr inline static auto equal0(double a) -> bool {
    return std::abs(a) < EPSILON_;
  }

  inline static auto solve_linear(double a,
                                  double b,
                                  double c,
                                  double d,
                                  double e,
                                  double f) -> double* {
    double D{a * e - b * d};
    double Dx{c * e - b * f};
    double Dy{a * f - c * d};

    if (equal0(D)) {
      std::size_t size = equal0(Dx) && equal0(Dy) ? 1 : 0;
      double* result   = new double[size];
      std::memset(result, 0x00, sizeof(int) * size);
      return result;
    } else {
      double* result = new double[2];
      result[0] = Dx / D, result[1] = Dy / D;
      return result;
    }
  }

  inline static auto solve_quadratic(double a, double b, double c) -> double* {
    double delta{b * b - 4 * a * c};
    if (equal0(delta)) {
      double* result = new double[1];
      result[0]      = -b / (a * 2);
      return result;
    } else if (delta < 0) {
      double* result = new double[1];
      result[0]      = 0;
      return 0;
    } else {
      double a2{a * 2};
      double x{(-b / a2)};
      double y{std::sqrt(delta) / a2};

      double* result = new double[2];
      result[0] = x + y, result[1] = x - y;

      return result;
    }
  }

  constexpr inline static auto solve_diophantine(int a,
                                                 int b,
                                                 int c,
                                                 int& x,
                                                 int& y,
                                                 int& g) -> bool {
    g = ex_GCD_(std::abs(a), std::abs(b), x, y);
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

constexpr int MOD = 1000000007;

auto run() -> void {
  std::string s;
  std::cin >> s;

  std::array<int, 1000001> factorial{}, inverse_factorial{};
  factorial[0] = inverse_factorial[0] = 1;

  for (int i = 1; i < 1000001; i++) {
    factorial[i]         = (static_cast<int64_t>(i) * factorial[i - 1]) % MOD;
    inverse_factorial[i] = Algebra::coprime_mod_inv(factorial[i], MOD);
  }

  int n = static_cast<int>(s.size());
  std::array<int, 26> freq{};
  for (char c : s) {
    freq[c - 'a'] += 1;
  }

  int res = factorial[n];
  for (int f : freq) {
    res = (static_cast<int64_t>(res) * inverse_factorial[f]) % MOD;
  }

  std::cout << res << "\n";
}

}  // namespace _CreatingStringsII

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

#ifdef EVERMORE
  pthread_set_qos_class_self_np(QOS_CLASS_USER_INTERACTIVE, 0);

  FILE* stream = std::freopen("input.txt", "r", stdin);
  if (stream == nullptr) {
    std::cerr << "Input file not found\n";
    __builtin_trap();
  }
#endif

  int t{1};
  while (t-- > 0)
    _CreatingStringsII::run();

  std::cout.flush();

  return 0;
}
