#include <algorithm>  // IWYU pragma: keep
#include <array>      // IWYU pragma: keep
#include <bit>        // IWYU pragma: keep
#include <bitset>
#include <cassert>   // IWYU pragma: keep
#include <cmath>     // IWYU pragma: keep
#include <concepts>  // IWYU pragma: keep
#include <cstdint>   // IWYU pragma: keep
#include <cstring>   // IWYU pragma: keep
#include <deque>     // IWYU pragma: keep
#include <functional>
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

namespace _2193E {

template <int N>
class FixedDensePrime {
 private:
  std::array<int, N> minima_, powers_;
  std::bitset<N> parity_, squareFree_;

 public:
  std::vector<int> primes_;

  explicit FixedDensePrime() : minima_{}, powers_{} {
    for (int i = 2; i < (N + 1) >> 1; i++) {
      int minimum, power;
      if (minima_[i] == 0) {
        minimum = i;
        power   = 1;
        parity_.set(i, true);
        squareFree_.set(i, true);
        primes_.push_back(i);
      } else {
        minimum = minima_[i];
        power   = powers_[i];
      }

      for (int e : primes_) {
        int index{e * i};
        if (index < N) {
          minima_[index] = e;
          parity_.set(index, !parity_[i]);
          if (e == minimum) {
            powers_[index] = power + 1;
            break;
          } else {
            powers_[index] = 1;
            squareFree_.set(index, squareFree_[i]);
          }
        } else
          break;
      }
    }

    for (int i = (N + 1) >> 1 | 1; i < N; i += 2) {
      if (minima_[i] == 0) {
        parity_.set(i, true);
        squareFree_.set(i, true);
      }
    }
  }

  auto is_square_free(int n) -> bool { return squareFree_[n]; }
  auto get_parity(int n) -> bool { return parity_[n]; }

  auto totient(int n) -> int {
    int result{1};
    while (minima_[n] != 0) {
      int factor{1};
      for (int i = 1; i < powers_[n]; i++)
        factor *= minima_[n];
      result *= factor * (minima_[n] - 1);
      n /= factor * minima_[n];
    }

    if (n != 1)
      result *= n - 1;

    return result;
  }

  void for_prime_factors(int n, std::function<void(const int&)> consume) {
    while (minima_[n] != 0) {
      consume(minima_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(n);
  }

  void for_powers(int n, std::function<void(const int&)> consume) {
    while (minima_[n] != 0) {
      consume(powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      consume(1);
  }
  void for_prime_factors_and_powers(
      int n,
      std::function<void(const int&, const int&)> biConsume) {
    while (minima_[n] != 0) {
      biConsume(minima_[n], powers_[n]);
      int factor{1};
      for (int i = 0; i < powers_[n]; i++)
        factor *= minima_[n];
      n /= factor;
    }

    if (n != 1)
      biConsume(n, 1);
  }

  void for_factors(int n,
                   bool include1,
                   bool includeN,
                   std::function<void(const int64_t&)> consume) {
    if (n == 1) {
      if (include1 && includeN)
        consume(1);
    } else {
      if (include1)
        consume(1);

      std::vector<int64_t> primeFactors{}, powers{};

      for_prime_factors_and_powers(n, [&primeFactors, &powers](int a, int b) {
        primeFactors.push_back(a), powers.push_back(b);
      });

      std::vector<int64_t> factors = primeFactors;
      std::unique_ptr<int[]> currentPowers(new int[factors.size()]);
      std::ranges::fill(currentPowers.get(),
                        currentPowers.get() + factors.size(), 1);

      int index{};
      while (true) {
        if (currentPowers[index] > powers[index])
          index++;
        else if (factors[index] == n) {
          if (includeN)
            consume(n);
          break;
        } else {
          consume(factors[index]);
          for (int i = 0; i <= index; i++)
            factors[i] = factors[index] * primeFactors[i];

          std::ranges::fill(currentPowers.get(), currentPowers.get() + index,
                            1);

          currentPowers[index]++;
          index = 0;
        }
      }
    }
  }
};

FixedDensePrime<300001> primes{};

auto run() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  std::vector<int> cnt(n + 1, INT_MAX >> 1);
  for (int e : a) {
    cnt[e] = 1;
  }

  for (int x = 1; x <= n; x++) {
    std::vector<int> factors{};
    primes.for_factors(x, true, true,
                       [&factors](int a) { factors.push_back(a); });
    for (int y : factors) {
      cnt[x] = std::min(cnt[x], cnt[y] + cnt[x / y]);
    }
  }

  for (int& e : cnt) {
    if (e == INT_MAX >> 1) {
      e = -1;
    }
  }

  for (int i = 1; i <= n; i++) {
    std::cout << cnt[i] << " ";
  }

  std::cout << "\n";
}

}  // namespace _2193E

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
  std::cin >> t;
  while (t-- > 0)
    _2193E::run();

  std::cout.flush();

  return 0;
}
